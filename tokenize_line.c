#include "main.h"

/**
 * tokenize_line - tokenize the line from stream
 * @line: line read from stream
 * @delim: delimiter on which to tokenize
 *
 * Return: array of string
 */
char **tokenize_line(char *line, char *delim)
{
	int i = 0;
	char *tok = 0;
	char **args = malloc(sizeof(*args) * (count_tokens(line, delim) + 1));

	if (!args)
	{
		perror("malloc");
		free(line);
		exit(1);
	}
	for (i = 0, tok = _strtok(line, delim); tok; i++, tok = _strtok(0, delim))
		args[i] = tok;
	args[i] = 0;

	return (args);
}
