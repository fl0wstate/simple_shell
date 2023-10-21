#include "main.h"

/**
 * free_safe - free savely w/out errors
 * @mode_args: struct (check main.h for further details)
 */
void free_safe(m_args *mode_args)
{
	free_buf(&mode_args->cmd_toks, 0, 1);
	free_buf(&mode_args->tokens, 0, 1);
	free_buf(0, &mode_args->line, 0);
	free_buf(0, &mode_args->path, 0);
}

