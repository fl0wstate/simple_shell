#include "main.h"
#include <linux/limits.h>
#include <stdio.h>
#include <unistd.h>
/**
 * change_directory - move to another directory
 *
 * @mode_args: list of tokenized word
 *
 * Return: void
 */
void change_directory(m_args *mode_args)
{
	char *_cwd_buf = malloc(PATH_MAX);

	if ((*mode_args->tokens)[1] == NULL)
	{
		/* collect the current working directory */
		getcwd(_cwd_buf, PATH_MAX);
		setenv("OLDPWD", _cwd_buf, 1);
		chdir((_getenv("HOME")));
		/* update the PWD */
		getcwd(_cwd_buf, PATH_MAX);
		setenv("PWD", _cwd_buf, 1);
	}
	else if (!_strcmp((*mode_args->tokens)[1], "-"))
	{
		if (_getenv("OLDPWD"))
		{
			chdir(_getenv("OLDPWD"));
			getcwd(_cwd_buf, PATH_MAX);
			setenv("PWD", _cwd_buf, 1);
		}
		else
			printf("%s: %s: OLDPWD not set\n", *mode_args->av, (*mode_args->tokens)[0]);
	}
	else if (chdir(((*mode_args->tokens)[1])) != 0)
	{
		_printf("%s: %u: %s: can't cd to %s\n",
					*mode_args->av, *mode_args->cmd_count,
					**mode_args->tokens, (*mode_args->tokens)[1]);
	}
	free(_cwd_buf);
}
/**
 * exit_builtin - exits the shell
 *
 * @mode_args: pointer to a struct containing
 * all needed values
 *
 * Return: 0 to stop the loop
 */
void exit_builtin(m_args *mode_args)
{
	int status = 0;

	/* exit 98 */
	status = _atoi((*mode_args->tokens)[1]);
	free_buf(mode_args->tokens, NULL, 1);
	free_buf(NULL, mode_args->line, 0);
	free_buf(NULL, mode_args->path, 0);
	free_list(*mode_args->list_path);
	exit(status < 0 ? 0 : status);
}

/**
 * _get_cwd - custom function to get the current dir
 * @mode_args: store the current working dir inside the path list
 * Return: void
 */
void _get_cwd(m_args *mode_args)
{
	(void)mode_args;
	char *buf = NULL;

	buf = malloc(PATH_MAX);
	getcwd(buf, PATH_MAX);

	_printf("%s\n", buf);
	free_buf(NULL, &buf, 0);
}
