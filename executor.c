#include "main.h"

/**
 * executor - execute command/s based on existance of logicals
 * @logical_count: number of logicals
 * @mode_stat: mode status (non/interactive)
 * @mode_args: struct (read main.h)
 */
void executor(int logical_count, int mode_stat, m_args *mode_args)
{
	int i = 0;

	for (i = 0; mode_args->cmd_toks && mode_args->cmd_toks[i]; i++)
	{
		if (!i || !logical_count)
			run(mode_stat, i, mode_args);
		else if (mode_args->logcials[i - 1])

			switch (mode_args->logcials[i - 1])
			{
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
	mode_args->tokens = tokenize_line(mode_args->cmd_toks[idx], " ");
	mode_args->path = _which(mode_args->tokens[0], *mode_args->list_path);
	mode(mode_stat)(mode_args);
	free_buf(&mode_args->tokens, 0, 1);
	free_buf(0, &mode_args->path, 0);
}
