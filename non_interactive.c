#include "main.h"

/**
 * non_interactive - hanlde non-interactive mode
* @mode_args: struct of mode_arguments.
 */
void non_interactive(m_args *mode_args)
{
	char *path = mode_args->path;
	int fk_id, wstat;


	if (!builtin_handler(mode_args))
		return;
	if (!path)
	{
		_dprintf(STDERR_FILENO, "%s: %u: %s: not found\n",
				*mode_args->av, *mode_args->cmd_count, *mode_args->tokens);
		mode_args->_errno = 127;
	}
	else
	{
		fk_id = fork();
		if (!fk_id)
		{
			execve(path, mode_args->tokens, *mode_args->env);
			mode_args->_errno = 2;
			perror("execve");
			exit(mode_args->_errno);
		}
		else
		{
			wait(&wstat);
			free_safe(mode_args);
			/* normal termination */
			mode_args->_errno = WEXITSTATUS(wstat);
		}
	}
}
