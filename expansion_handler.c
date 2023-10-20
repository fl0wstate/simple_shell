#include "main.h"

/**
 * expansion_handler - handles variable replacement
 * @str: string pointer contains the expanded variable
 * @mode_args: struct (read main.h)
 *
 * Return: array of string represent arguments to `execve` syscall
 */
char **expansion_handler(char *str, m_args *mode_args)
{
	switch (str[1])
	{
		case '$':
			mode_args->args[0] = (*mode_args->tokens)[0];
			mode_args->args[1] = utoa(mode_args->ppid);
			mode_args->args[2] = 0;
			break;
		case '?':
			mode_args->args[0] = (*mode_args->tokens)[0];
			mode_args->args[1] = utoa(mode_args->_errno);
			mode_args->args[2] = 0;
			break;
		default:
			mode_args->args[0] = (*mode_args->tokens)[0];
			mode_args->args[1] = _strdup(_getenv(str + 1));
			mode_args->args[2] = 0;
	}

	return (mode_args->args);
}
