#include "main.h"
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void command_separator_handler(char **line);
void command_AND_handler(char **line);
void command_OR_handler(char **line);

/**
 * signal_handler - avoids signal interrupt
 * @this_sig: signal recieved
 * Return: void
 */
void signal_handler(int this_sig)
{
	if (this_sig == SIGINT)
	{
		printf("[%s]   ", _getenv("LOGNAME"));
	}
}
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
	ui cmd_count = 0;
	char **tokens = 0, *line = 0, *path = 0;
	list_t *list_path = path_list();
	m_args mode_args;

	signal(SIGINT, &signal_handler);
	while (-1)
	{
		if (isatty(STDIN_FILENO))
		{
			printf("[%s]   ", _getenv("LOGNAME"));
		}
		bytes = getline(&line, &n, stdin);
		if (bytes == -1)
		{
			free_buf(0, &line, 0);
			free_list(list_path);
			exit(1);
		}
		else if (bytes == 0)
		{
			fflush(STDIN_FILENO);
			printf("[%s]   ", _getenv("LOGNAME"));
		}
		line[bytes - 1] = 0;
		cmd_count++;
		tokens = tokenize_line(line);
		path = _which(tokens[0], list_path);
		mode_args.tokens = &tokens;
		mode_args.env = &env;
		mode_args.av = av;
		mode_args.path = &path;
		mode_args.line = &line;
		mode_args.cmd_count = &cmd_count;
		mode_args.list_path = &list_path;

		mode(STDIN_FILENO)(&mode_args);
	}
	return (0);
}
#if 0
/**
 * command_separator_checker - which kind of logic
 * are we supposed to execute
 * @line: command entered by the user
 * Return: void
 */
void command_separator_checker(char **line)
{
	const char *or_operator = "||";
	const char *and_operator = "&&";

	char *and_found = strstr(*line, and_operator);
	char *or_found = strstr(*line, or_operator);

	if (and_found && (!or_found || and_found < or_found))
	{
		printf("Found &&\n");
		/* case of && */
	}
	else if (or_found && (!and_found || or_found < and_found))
	{
		printf("Found ||\n");
	}
	else
	{
		printf("No special operator found\n");

		printf("Continuing with the rest of the code...\n");
	}
}
#endif
