#include "main.h"

/**
 * _getenv - yank the the corresponding env value based on the name
 * @name: environment variable
 *
 * Return: corresponding value,
 * or NULL
 */
char *_getenv(const char *name)
{
	int i = 0, name_len = 0;
	char *val = 0;

	if (!name)
		return (0);

	name_len = _strlen((char *)name);

	for (i = 0; environ[i]; i++)
	{
		if (!_strncmp(environ[i], (char *)name, name_len))
		{
			val = (environ[i]);
			_strtok(val, "=");
			val = _strtok(0, "=");
			break;
		}
	}

	return (val);
}

