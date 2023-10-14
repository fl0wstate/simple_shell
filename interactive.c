#include "main.h"

/**
 * interactive - hanlder interactive mode
 * @mode_args: struct of mode_arguments
 */
void interactive(m_args *mode_args)
{
	int status;
	pid_t fk_id;

	if (!*mode_args->path)
	{
		execve(**mode_args->tokens, *mode_args->tokens, *mode_args->env);
		_printf("%s: %u: %s: not found\n",
		_getenv("_"), *mode_args->cmd_count, **mode_args->tokens);
		free_buf(0, mode_args->path, 0);
		free_buf(mode_args->tokens, 0, 1);
	}
	else
	{
		fk_id = fork();
		if (fk_id < 0)
		{
			perror("fork");
			free_buf(0, mode_args->line, 0);
			exit(1);
		}

		if (!fk_id)/* child */
		{
			environ = *mode_args->env;
			execve(*mode_args->path, *mode_args->tokens, *mode_args->env);
			perror("execve");
			free_buf(mode_args->tokens, 0, 1);
			free_buf(0, mode_args->path, 0);
			free_buf(0, mode_args->line, 0);
			exit(1);
		}
		else/* parent */
		{
			wait(&status);
			free_buf(0, mode_args->path, 0);
			free_buf(mode_args->tokens, 0, 1);
			free_buf(0, mode_args->line, 0);
		}
	}
}
