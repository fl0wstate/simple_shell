#include "main.h"

/**
 * main - simple shell
 * @ac: arguments count
 * @av: arguments vector
 * @env: enviroment variables
 *
 * Return: 0 as exit status
 */
int main(__attribute__((unused))int ac, char **av, char **env)
{
	ssize_t bytes;
	size_t n = 0;
	ui cmd_count = 0, mode_stat, i = 0, j = 0, k = 0;
	char **tokens = 0, **cmd_toks = 0;
	char *line = 0, *path = 0;
	m_args mode_args;
	list_t *list_path = path_list(&mode_args);

	mode_args.cmd_toks = &cmd_toks;
	mode_args.tokens = &tokens;
	mode_args.env = &env;
	mode_args.av = av;
	mode_args.path = &path;
	mode_args.line = &line;
	mode_args.cmd_count = &cmd_count;
	mode_args.list_path = &list_path;
	mode_args.free = 0;
	mode_args._errno = 0;
	mode_args.ppid = getpid();
	while (-1)
	{
		mode_stat = isatty(STDIN_FILENO);
		if (mode_stat)
			_dprintf(STDOUT_FILENO, "($) ");
		bytes = _getline(&line, &n, stdin);
		if (bytes == EOF)
			EOF_handler(&mode_args, list_path);
		line[bytes - 1] = 0;
		cmd_count++;
		for (j = 0, k = 0; line && line[j]; j++)
		{
			if (line[j] == '&')
			{
				/*printf("AND\n");*/
				mode_args.logcials[k++] = AND;
				j++;
				continue;
			}
			if (line[j] == '|')
			{
				/*printf("OR\n");*/
				mode_args.logcials[k++] = OR;
				j++;
				continue;
			}
		}
		mode_args.logcials[k] = 0;
		/*TODO: tokenize the line base on (';', '&&', '||')*/
		cmd_toks = tokenize_line(line, ";&|");
		if (!**mode_args.cmd_toks)
		{
			free_safe(&mode_args);
			continue;
		}
		for (i = 0; cmd_toks && cmd_toks[i]; i++)
		{
			if (!i || !k)
			{
				tokens = tokenize_line(cmd_toks[i], " ");
				path = _which(tokens[0], list_path);
				mode(mode_stat)(&mode_args);
				free_buf(&tokens, 0, 1);
				free_buf(0, &path, 0);
			}
			else
			{
				if (mode_args.logcials[i - 1])
				{
					/*printf("-------> Logical is: %c\n", mode_args.logcials[i - 1]);*/
					switch (mode_args.logcials[i - 1])
					{
						case '&':
							if (!mode_args._errno)
							{
								tokens = tokenize_line(cmd_toks[i], " ");
								path = _which(tokens[0], list_path);
								mode(mode_stat)(&mode_args);
								free_buf(&tokens, 0, 1);
								free_buf(0, &path, 0);
							}
							break;
						case '|':
							if (mode_args._errno)
							{
								tokens = tokenize_line(cmd_toks[i], " ");
								path = _which(tokens[0], list_path);
								mode(mode_stat)(&mode_args);
								free_buf(&tokens, 0, 1);
								free_buf(0, &path, 0);
							}
							break;
					}
				}
			}
		}
		free_safe(&mode_args);
	}
	return (0);
}
