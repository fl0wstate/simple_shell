#include "main.h"

/**
 * interactive - hanlder interactive mode
 * @mode_args: struct of mode_arguments
 */
void interactive(m_args *mode_args)
{
	int status, i = 0,
	is_replacement = (*mode_args->tokens)[1] &&
		    _strcmp((*mode_args->tokens)[1], "echo") &&
		    (*mode_args->tokens)[1][0] == '$';
	pid_t fk_id;

	if (!builtin_handler(mode_args))
		return;
	if (!*mode_args->path)
	{
		/*TODO: print should be on stderr */
		_dprintf(STDERR_FILENO, "%s: %u: %s: not found\n",
				*mode_args->av, *mode_args->cmd_count, **mode_args->tokens);
		mode_args->_errno = 127;
	}
	else
	{
		fk_id = fork();
		if (fk_id < 0)
		{
			perror("fork");
			free_safe(mode_args);
			/*TODO: revisit exit status */
			exit(errno);
		}
		if (!fk_id)/* child */
		{
			/*TODO: execve doesn't handle which command!!!! */
			if (is_replacement)
			{
				expansion_handler((*mode_args->tokens)[1], mode_args);
				for (i = 0; mode_args->args[i]; i++)
					printf("args[%d] = %s\n", i, mode_args->args[i]);
			}
#if 0
			execve(*mode_args->path,
					!is_replacement ? *mode_args->tokens : mode_args->args, environ);
#endif
			execve(*mode_args->path,
					*mode_args->tokens, environ);
			perror("execve");
			free_safe(mode_args);
			mode_args->_errno = 2;
			exit(mode_args->_errno);
		}
		else/* parent */
		{
			wait(&status);
			errno = WEXITSTATUS(status);
			mode_args->_errno = errno;
		}
	}
}


