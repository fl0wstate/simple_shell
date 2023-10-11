#include "main.h"

/**
 * _which - search for a command in PATH environment variable
 * @cmd: command
 * @env: enviroment variable
 *
 * Return: absolute path to the command on success,
 * NULL on failure
 */
char *_which(char *cmd, char **env)
{
	int i = 0;
	char *delim = "PATH=:", *tok = 0, *path = 0, *dir = 0;
	struct stat st;

	if (!cmd)
		return (0);
	if (_strpbrk(cmd, "~/"))
		return (_strdup(cmd));
	for (i = 0; env[i]; i++)
	{
		if (!_strncmp(env[i], "PATH", 4))
		{
			tok = _strtok(env[i], delim);
			while (tok)
			{
				dir = str_concat(tok, "/");
				path = str_concat(dir, cmd);
				if (!stat(path, &st))
				{
					free(dir);
					return (path);
				}
				free(dir);
				free(path);
				tok = _strtok(0, delim);
			}
			break;
		}
	}

	return (0);
}

