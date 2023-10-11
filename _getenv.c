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
	int i = 0;

	if (!name)
		return (0);
	for (i = 0; environ[i]; i++)
	{
		if (!_strncmp(environ[i], name, _strlen(name)))
		{
			_strtok(environ[i], "=");
			return (_strtok(0, "="));
		}
	}
	return (0);
}
