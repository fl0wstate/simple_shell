#include "main.h"

char **expansion_handler(char *str, m_args *mode_args)
{
	switch (str[1])
	{
		case '$':
			mode_args->args[0] = utoa(mode_args->ppid);
			mode_args->args[1] = 0;
			break;
		case '?':
			mode_args->args[0] = utoa(mode_args->_errno);
			mode_args->args[1] = 0;
			break;
		default:
			mode_args->args[0] = _strdup(_getenv(str + 1));
			mode_args->args[1] = 0;
	}

	return (mode_args->args);
}
