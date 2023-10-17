#include "main.h"

/**
 * _unsetenv - deletes the variable name from the environment.
 * @name: environ name
 *
 * Return: 0 on success
 * -1 on failure
 */
int _unsetenv(const char *name)
{
	int i = 0, j = 0, ignore;
	static int count;
	char **cpy;
	env_config env;

	env.name = name;
	env.free = &count;

	ignore = set_envconfig(&env);

	if (ignore)/*TODO: handle errno here */
		return (-1);

	cpy = malloc(sizeof(environ) * env.len);
	for (j = 0; environ[i]; i++)
		if (i != env.idx)
			cpy[j++] = _strdup(environ[i]);
	cpy[j] = 0;

	count++;

	if (*env.free >= 2)
		free_envcpy(&environ);

	environ = cpy;

	return (0);
}
