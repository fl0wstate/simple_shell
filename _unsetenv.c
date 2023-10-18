#include "main.h"

/**
 * _unsetenv - deletes the variable name from the environment.
 * @envconf: struct of `env_config` see main.h
 *
 * Return: 0 on success
 * -1 on failure
 */
int _unsetenv(env_config *envconf)
{
	int i = 0, j = 0;
	char **cpy;

	if (envconf->idx < 0)
		return (0);

	cpy = malloc(sizeof(environ) * envconf->len);
	if (!cpy)
		return (-1);

	for (j = 0; environ[i]; i++)
		if (i != envconf->idx)
			cpy[j++] = _strdup(environ[i]);
	cpy[j] = 0;

	if (*envconf->free >= 2)
		free_envcpy(&environ);

	environ = cpy;

	return (0);
}
