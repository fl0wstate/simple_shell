#include "main.h"

/**
 * non_interactive - hanlde non-interactive mode
 * @mode_args: struct of mode_arguments.
 */
void non_interactive(m_args *mode_args)
{
	char *path = *mode_args->path;

	/*TODO: non-interactive sucks actually */
	if (!path)
		printf("%s: %u: %s: not found\n",
				*mode_args->av, *mode_args->cmd_count, **mode_args->tokens);
	else
		execve(path, *mode_args->tokens, *mode_args->env);
}
