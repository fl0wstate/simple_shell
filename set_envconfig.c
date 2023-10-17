#include "main.h"

/**
 * set_envconfig - set environ configuration
 * Description: configuration is simply
 * index at which to update environ,
 * environ length,
 * environ name to update.
 * @envconf: pointer to env_config struct
 *
 * Return: 0 if there's a valid name to update,
 * -1 on failure,
 * -2 when there's no name match in environ
 */
int set_envconfig(env_config *envconf)
{
	int i = 0, name_len = 0, flag = 0;

	if (!envconf->name)
		return (-1);
	name_len = _strlen((char *)envconf->name);

	/* TODO: should set errno here */
	if (!envconf->name || !name_len || _strchr((char *)envconf->name, '='))
		return (-1);

	for (i = 0; environ[i]; i++)
	{
		if (!_strncmp(environ[i], (char *)envconf->name, name_len)
				&& environ[i][name_len] == '=')
		{
			flag = 1;
			envconf->idx = i;
		}
	}
	if (!flag)
		envconf->idx = -1;
	envconf->len = i;

	return (flag ? 0 : -2);
}
