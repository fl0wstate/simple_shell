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
	int idx = 0;
	env_config env;

	env.idx = 0;
	env.len = 0;
	env.name = name;

	if (!name || !_strlen((char *)name) || _strchr((char *)name, '='))
		return (-1);

	idx = set_envconfig(&env);

	if (!idx)
		return (adjust(name, value, overwrite, env.idx));
	return (add_new(name, value, env.len));
}

/**
 * adjust - update existing env name.
 * @name: env name
 * @value: env value
 * @overwrite: non-zero to overwrite, no-op otherwise
 * @idx: index at which to udpate environ
 *
 * Return: 0 on success
 * -1 on failure
 */
int adjust(const char *name, const char *value, int overwrite, int idx)
{
	int size = 0, j = 0, k = 0, m = 0, n = 0;
	char *eq = "=";

	size = _strlen((char *)name) + _strlen((char *)value) + 2;

	if (overwrite)
	{
		environ[idx] = malloc(size);
		for (j = 0; j < size; j++)
		{
			environ[idx][j] = name[k]
				? name[k++] : eq[n]
				? eq[n++] : value[m]
				? value[m++] : 0;
		}
	}

	return (0);
}

/**
 * add_new - add new environ variable by copying the old one, then append.
 * @name: env name
 * @value: env value
 * @overwrite: non-zero to overwrite, no-op otherwise
 * @len: length of environ
 *
 * Return: 0 on success
 * -1 on failure
 */
int add_new(const char *name, const char *value, int len)
{
	int i = 0, j = 0, k = 0, m = 0, n = 0, size;
	char *eq = "=";
	char **cpy = malloc(sizeof(environ) * (len + 2));

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
	environ = cpy;

	return (0);
}
