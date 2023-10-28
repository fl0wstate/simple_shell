#include "main.h"

/**
 * main - simple shell
 * @ac: arguments count
 * @av: arguments vector
 * @env: enviroment variables
 *
 * Return: 0 as exit status
 */
int main(__attribute__((unused))int ac, char **av,
		__attribute__((unused))char **env)
{
	ssize_t bytes;
	size_t n = 0;
	ui cmd_count = 0, mode_stat;
	m_args mode_args;
	list_t *list_path = path_list(&mode_args);

	/* mode_args initialization */
	mode_args.cmd_toks = 0;
	mode_args.tokens = 0;
	mode_args.av = av;
	mode_args.path = 0;
	mode_args.line = 0;
	mode_args.cmd_count = &cmd_count;
	mode_args.logical_count = 0;
	mode_args.list_path = &list_path;
	mode_args.alias = 0;
	mode_args.free = 0;
	mode_args._errno = 0;
	mode_args.ppid = getpid();

	while (-1)
	{
		mode_stat = isatty(STDIN_FILENO);
		if (mode_stat)
			_dprintf(STDOUT_FILENO, "($) ");
		bytes = _getline(&mode_args.line, &n, stdin);
		if (bytes == EOF)
			EOF_handler(&mode_args);
		mode_args.line[bytes - 1] = 0;
		cmd_count++;
		mode_args.logical_count = set_logicals(&mode_args);
		mode_args.cmd_toks = tokenize_line(mode_args.line, ";&|");
		executor(mode_stat, &mode_args);
		free_safe(&mode_args);
	}
	return (0);
}


