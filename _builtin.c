#include "main.h"

/**
 * change_directory - move to another directory
 *
 * @mode_args: list of tokenized word
 *
 * Return: void
 */
void change_directory(m_args *mode_args)
{
	char *_current_wd = malloc(PATH_MAX);

	if ((mode_args->tokens)[1] == NULL)
	{
		mode_args->free = 1;

		getcwd(_current_wd, PATH_MAX);

		_setenv("OLDPWD", _current_wd, 1);

		(_getenv("HOME")) ? chdir(_getenv("HOME")) : chdir(_getenv("PWD"));

		getcwd(_current_wd, PATH_MAX);

		_setenv("PWD", _current_wd, 1);
	}
	else if (!_strcmp((mode_args->tokens)[1], "-"))
	{
		if (_getenv("OLDPWD"))
		{
			mode_args->free = 1;
			chdir(_getenv("OLDPWD"));
			getcwd(_current_wd, PATH_MAX);
			_setenv("PWD", _current_wd, 1);
		}
		else
			_dprintf(STDERR_FILENO, "%s: %s: OLDPWD not set\n",
					*mode_args->av, (mode_args->tokens)[0]);
	}
	else if (chdir(((mode_args->tokens)[1])) != 0)
	{
		_dprintf(STDERR_FILENO, "%s: %u: %s: can't cd to %s\n",
					*mode_args->av, *mode_args->cmd_count,
					*mode_args->tokens, (mode_args->tokens)[1]);
	}
	free(_current_wd);
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
	ui i = 0, is_err = 0, status = 0;

	if ((mode_args->tokens)[1])
	{
		for (i = 0; (mode_args->tokens)[1][i]; i++)
			if (!_isdigit((mode_args->tokens)[1][i]))
			{
				is_err = 1;
				_dprintf(STDERR_FILENO, "%s: %u: %s: Illegal number: %s\n",
						*mode_args->av, *mode_args->cmd_count,
						(mode_args->tokens)[0], (mode_args->tokens)[1]);
				mode_args->_errno = 2;
				break;
			}
		if (!is_err)
			status = _atoi((mode_args->tokens)[1]);
	}
	if (!is_err)
	{
		free_safe(mode_args);
		free_aliases(mode_args->alias);
		free_list(*mode_args->list_path);
		if (mode_args->free)
			free_envcpy(&environ);
		exit(status ? status : mode_args->_errno);
	}
}

/**
 * setenv_builtin - setenv handler
 *
 * @mode_args: pointer to `mode_arguments` struct
 *
 */
void setenv_builtin(m_args *mode_args)
{
	int status;

	if (!(mode_args->tokens)[1] || !(mode_args->tokens)[2])
		return;
	mode_args->free = 1;
	status = _setenv((mode_args->tokens)[1], (mode_args->tokens)[2], 1);
	if (status < 0)
	{
		_dprintf(STDERR_FILENO, "%s: %u: %s: bad variable name\n",
				*mode_args->av, *mode_args->cmd_count, (mode_args->tokens)[0]);
		mode_args->_errno = 2;
	}
}

/**
 * unsetenv_builtin - unsetenv handler
 *
 * @mode_args: pointer to `mode_arguments` struct
 *
 */
void unsetenv_builtin(m_args *mode_args)
{
	int status;

	if (!(mode_args->tokens)[1] || !_getenv(mode_args->tokens[1]))
		return;
	mode_args->free = 1;
	status = _setenv((mode_args->tokens)[1], 0, 1);
	if (status < 0)
	{
		_dprintf(STDERR_FILENO, "%s: %u: %s: bad variable name\n",
				*mode_args->av, *mode_args->cmd_count, (mode_args->tokens)[0]);
		mode_args->_errno = 2;
	}
}

/**
 * env_builtin - env handler
 *
 * @mode_args: pointer to `mode_arguments` struct
 *
 */
void env_builtin(m_args *mode_args)
{
	int i = 0;
	(void)mode_args;

	for (i = 0; environ[i]; i++)
		_dprintf(STDOUT_FILENO, "%s\n", environ[i]);
}

