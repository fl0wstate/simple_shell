#include "main.h"

/**
 * non_interactive - hanlde non-interactive mode
* @mode_args: struct of mode_arguments.
 */
void non_interactive(m_args *mode_args)
{
	char *path = *mode_args->path;

	execve(path ? path : **mode_args->tokens,
			*mode_args->tokens, *mode_args->env);
	_printf("%s: %u: %s: not found\n",
	*mode_args->av, *mode_args->cmd_count, **mode_args->tokens);
	free_buf(0, mode_args->path, 0);
	free_buf(0, mode_args->line, 0);
	free_buf(mode_args->tokens, 0, 1);
	free_list(*mode_args->list_path);
	exit(1);
}
