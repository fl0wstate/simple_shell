#include "main.h"
#include <stdio.h>

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
#if 0
		if (!_strcmp(**mode_args->tokens, "exit"))
		{
			free_list(*mode_args->list_path);
			free_buf(0, mode_args->line, 0);
			free_buf(mode_args->tokens, 0, 1);
			exit(0);
		}
#endif
		/*execve(**mode_args->tokens, *mode_args->tokens, *mode_args->env);*/
		printf("%s: %u: %s: not found\n",
				*mode_args->av, *mode_args->cmd_count, **mode_args->tokens);
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
			/*environ = *mode_args->env;*/
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
