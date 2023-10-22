#include "main.h"

/**
 * _which - search for a command in PATH environment variable
 * @cmd: command
 * @list_path: a linkedlist for the PATH direcotries
 *
 * Return: absolute path to the command on success,
 * NULL on failure
 */
char *_which(char *cmd, list_t *list_path)
{
	char *path = 0, *dir = 0;
	struct stat st;
	list_t *head = 0;

	if (!cmd)
		return (0);
	if (_strpbrk(cmd, "~/."))
	{
		path = _strdup(cmd);
		if (!stat(path, &st))
			return (path);
		free_buf(0, &path, 0);
		return (0);
	}

	head = list_path;

	while (head)
	{
		dir = str_concat(head->str, "/");
		path = str_concat(dir, cmd);
		/*if (!stat(path, &st))*/
		if (!stat(path, &st))
		{
			free_buf(0, &dir, 0);
			if (st.st_mode & S_IXUSR)
				return (path);
		}
		free_buf(0, &dir, 0);
		free_buf(0, &path, 0);
		head = head->next;
	}
	return (0);
}
#if 0
char *_which(char *cmd, list_t *list_path)
{
	char *delim = "PATH=:", *tok = 0, *path = 0, *dir = 0;
	struct stat st;
	(void)list_path;

	if (!cmd)
		return (0);
	if (_strpbrk(cmd, "~/"))
	{
		if (!stat(cmd, &st))
			return (cmd);
		return (0);
	}
	tok = _strtok(_getenv("PATH"), delim);
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

	return (0);
}
#endif
