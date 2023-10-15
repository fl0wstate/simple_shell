#include "main.h"
/**
 * builtin_handler - handles all the builtin commands
 *
 * @mode_args: pointer to a struct
 *
 * Return: void
 */
void builtin_handler(m_args *mode_args)
{
	int i = 0;

	builtin_t builtins[] = {
		{"exit", exit_builtin},
		{"cd", change_directory},
		{NULL, NULL}
	};

	while (builtins[i].cmd)
	{
		if (!_strcmp((char *)builtins[i].cmd,
					(char *)(*mode_args->tokens)[0]))
		{
			builtins[i].builtin(mode_args);
			break;
		}
		i++;
	}
	if (!builtins[0].cmd)
		_printf("%s: %u: %s: not found\n",
				*mode_args->av, *mode_args->cmd_count, **mode_args->tokens);
}
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
		builtin_handler(mode_args);
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

