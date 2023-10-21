#include "main.h"

/**
 * interactive - hanlder interactive mode
 * @mode_args: struct of mode_arguments
 */
void interactive(m_args *mode_args)
{
	pid_t fk_id;
	int status, is_replacement = (mode_args->tokens)[1] &&
		_strcmp((mode_args->tokens)[1], "echo") && (mode_args->tokens)[1][0] == '$';
	char *alias = get_alias(*mode_args->tokens, mode_args);

	if (!builtin_handler(mode_args))
		return;
	if (!mode_args->path && !alias)
	{
		_dprintf(STDERR_FILENO, "%s: %u: %s: not found\n",
				*mode_args->av, *mode_args->cmd_count, *mode_args->tokens);
		mode_args->_errno = 127;
	}
	else
	{
		fk_id = fork();
		if (fk_id < 0)
		{
			perror("fork");
			free_safe(mode_args);
			exit(errno);
		}
		if (!fk_id)/* child */
		{
			if (is_replacement)
				expansion_handler((mode_args->tokens)[1], mode_args);
			execve(!alias ? mode_args->path : _which(alias, *mode_args->list_path),
					!is_replacement ? mode_args->tokens : mode_args->args, environ);
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

