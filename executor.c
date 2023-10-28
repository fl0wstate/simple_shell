#include "main.h"

/**
 * executor - execute command/s based on existance of logicals
 * @mode_stat: mode status (non/interactive)
 * @mode_args: struct (read main.h)
 */
void executor(int mode_stat, m_args *mode_args)
{
	int i = 0;

	for (i = 0; mode_args->cmd_toks && mode_args->cmd_toks[i]; i++)
	{
		if (!i)
			run(mode_stat, i, mode_args);
		else if (mode_args->logicals[i - 1])
			switch (mode_args->logicals[i - 1])
			{
				case ';':
					run(mode_stat, i, mode_args);
					break;
				case '&':
					if (!mode_args->_errno)
						run(mode_stat, i, mode_args);
					break;
				case '|':
					if (mode_args->_errno)
						run(mode_stat, i, mode_args);
					break;
			}
	}
}

/**
 * run - command runner
 * @mode_stat: mode status (non/interactive)
 * @mode_args: struct (read main.h)
 * @idx: index of command to run
 */
void run(int mode_stat, int idx, m_args *mode_args)
{
	mode_args->tokens = mode_args->cmd_toks;
	mode_args->tokens = tokenize_line(mode_args->cmd_toks[idx], "\t\x20");
	if (!mode_args->tokens[0])
	{
		free_buf(&mode_args->tokens, 0, 1);
		return;
	}
	mode_args->path = _which(mode_args->tokens[0], *mode_args->list_path);

	mode(mode_stat)(mode_args);
	free_buf(0, &mode_args->path, 0);
	free_buf(&mode_args->tokens, 0, 1);
}
