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
		_printf("%s: %u: %s: not found\n",
				*mode_args->av, *mode_args->cmd_count, **mode_args->tokens);
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
			exit(1);
		}

		if (!fk_id)/* child */
		{
			/*TODO: which command doesn't work */
			execve(*mode_args->path, *mode_args->tokens, *mode_args->env);
			perror("execve");
			free_safe(mode_args);
			exit(2);
		}
		else/* parent */
		{
			wait(&status);
			free_safe(mode_args);
		}
	}
}

