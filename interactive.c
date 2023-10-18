#include "main.h"

/**
 * interactive - hanlder interactive mode
 * @mode_args: struct of mode_arguments
 */
void interactive(m_args *mode_args)
{
	int status;
	pid_t fk_id;

	if (!builtin_handler(mode_args))
		return;
	if (!*mode_args->path)
	{
		/*TODO: print should be on stderr */
		_dprintf(STDERR_FILENO, "%s: %u: %s: not found\n",
				*mode_args->av, *mode_args->cmd_count, **mode_args->tokens);
		mode_args->_errno = 127;
		free_safe(mode_args);
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
			execve(*mode_args->path, *mode_args->tokens, environ);
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
			free_safe(mode_args);
		}
	}
}
