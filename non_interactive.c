#include "main.h"

/**
 * non_interactive - hanlde non-interactive mode
* @mode_args: struct of mode_arguments.
 */
void non_interactive(m_args *mode_args)
{
	char *path = *mode_args->path;
	pid_t fk_id;
	/*TODO: non-interactive sucks actually */


	if (!path)
		printf("%s: %u: %s: not found\n",
				*mode_args->av, *mode_args->cmd_count, **mode_args->tokens);
	else
	{
		fk_id = fork();
		if (fk_id == -1)
		{
			/* fork error */
			perror("fork");
		}
		if (!fk_id)
		{
			execve(path, *mode_args->tokens, *mode_args->env);
		}
		else
		{
			/* parent */
			wait(0);
			free_safe(mode_args);
			free_list(*mode_args->list_path);
			/*exit(EXIT_SUCCESS);*/
		}
	}

#if 0
	free_buf(0, mode_args->path, 0);
	free_buf(0, mode_args->line, 0);
	free_buf(mode_args->tokens, 0, 1);
	exit(0);
#endif
}
