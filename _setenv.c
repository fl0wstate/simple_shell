#include "main.h"

/**
 * _setenv - set environment variable by update or add new one.
 * @name: env name
 * @value: env value
 * @overwrite: non-zero to overwrite, no-op otherwise
 *
 * Return: 0 on success
 * -1 on failure
 */
int _setenv(const char *name, const char *value, int overwrite)
{
	int ignore = 0;
	static int count;
	env_config env;

	env.name = name;
	env.free = &count;

	if (!name || !_strlen((char *)name) || _strchr((char *)name, '='))
		return (-1);
	ignore = set_envconfig(&env);
	count++;

	/*TODO: handle freeing of previously allocated enviorn */
	if (!value)
		return (_unsetenv(&env));

	if (!ignore)
		return (adjust(name, value, overwrite, env));
	return (add_new(name, value, env));
}

/**
 * adjust - update existing env name.
 * @name: env name
 * @value: env value
 * @overwrite: non-zero to overwrite, no-op otherwise
 * @envconfig: struct of env_config, read that struct on main.h,
 * to obtain much details.
 *
 * Return: 0 on success
 * -1 on failure
 */
int adjust(const char *name, const char *value, int overwrite,
		env_config envconfig)
{
	int size = 0, i = 0, j = 0, k = 0, m = 0, n = 0;
	char *eq = "=";
	char **cpy;

	size = _strlen((char *)name) + _strlen((char *)value) + 2;

	if (overwrite)
	{
		cpy = malloc(sizeof(environ) * (envconfig.len + 1));
		if (!cpy)
		{
			perror("malloc");
			return (-1);
		}
		for (i = 0; environ[i]; i++)
		{
			if (i != envconfig.idx)
				cpy[i] = _strdup(environ[i]);
			else
			{
				cpy[envconfig.idx] = malloc(size);
				for (j = 0; j < size; j++)
				{
					cpy[envconfig.idx][j] = name[k]
						? name[k++] : eq[n]
						? eq[n++] : value[m]
						? value[m++] : 0;
				}
			}
		}
		cpy[i] = 0;
	}
	if (*envconfig.free >= 2)
		free_envcpy(&environ);
	environ = cpy;

	return (0);
}

/**
 * add_new - add new environ variable by copying the old one, then append.
 * @name: env name
 * @value: env value
 * @envconf: struct of env_config, read that struct on main.h,
 * to obtain much details.
 *
 * Return: 0 on success
 * -1 on failure
 */
int add_new(const char *name, const char *value, env_config envconf)
{
	int i = 0, j = 0, k = 0, m = 0, n = 0, size;
	char *eq = "=";
	char **cpy = malloc(sizeof(environ) * (envconf.len + 2));

	if (!cpy)
	{
		perror("malloc");
		return (-1);
	}

	size = _strlen((char *)name) + _strlen((char *)value) + 2;
	for (i = 0; environ[i]; i++)
		cpy[i] = _strdup(environ[i]);
	cpy[i] = malloc(size);
	for (j = 0; j < size; j++)
	{
		cpy[i][j] = name[k]
			? name[k++] : eq[n]
			? eq[n++] : value[m]
			? value[m++] : 0;
	}
	cpy[i + 1] = 0;

	if (*envconf.free >= 2)
		free_envcpy(&environ);
	environ = cpy;

	return (0);
}
