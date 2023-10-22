#include "main.h"

/**
 * expansion_handler - handles variable replacement
 * @mode_args: struct (read main.h)
 *
 * Return: array of string represent arguments to `execve` syscall
 */
char **expansion_handler(m_args *mode_args)
{
	int i;
	char *str;

	mode_args->args[0] = mode_args->tokens[0];
	for (i = 1; mode_args->tokens[i]; i++)
	{
		str = mode_args->tokens[i];

		/* escape 1st back-slash */
		if (str[0] == '\\')
			str++;
		if (str[0] == '\\' || !str[1])
		{
			mode_args->args[i] = str;
			continue;
		}
		switch (str[1])
		{
			case '$':
				mode_args->args[i] = utoa(mode_args->ppid);
				break;
			case '?':
				mode_args->args[i] = utoa(mode_args->_errno);
				break;
			default:
				mode_args->args[i] = _getenv(str + 1);
		}
	}
	mode_args->args[i] = 0;

	return (mode_args->args);
}
