#include "main.h"
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
	if ((*mode_args->tokens)[1] == NULL)
	{
		chdir((_getenv("HOME")));
	}
	else if (chdir(((*mode_args->tokens)[1])) != 0)
	{
		_printf("%s: %u: %s: can't cd to %s\n",
					*mode_args->av, *mode_args->cmd_count,
					**mode_args->tokens, (*mode_args->tokens)[1]);
	}
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
