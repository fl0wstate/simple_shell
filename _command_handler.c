#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int execute_commands(char *path, char **cmd, char **envp);
/**
 * command_separator_handler - does an execution for each command
 *
 * @line: the command line input
 *
 * Return: void
 */

void command_separator_handler(char **line)
{
	int i = 0;
	int d = 0;
	char **new_tokens_arry = {NULL};
	char *token = NULL;

	new_tokens_arry = malloc(sizeof(char *) *
			count_commands(*line) + 1);

	printf("command count -> %d\n", count_commands(*line));
	malloc_check_prev_double(new_tokens_arry, *line);

	for (i = 0, token = _strtok(*line, ";"); token; i++, token = _strtok(0, ";"))
	{
		d = _strspn(token, " ");
		token += d;
		new_tokens_arry[i] = token;
		printf("commands -> %s\n", new_tokens_arry[i]);


	}
	new_tokens_arry[i] = NULL;
	/* free me dwang!! */
}

/**
 * count_commands - count number of words in a string
 * @str: string pointer
 *
 * Return: number of words,
 * 0 on failure
 */
int count_commands(char *str)
{
	int len = 0, count = 0;

	if (!str)
		return (0);
	for (; str[len]; len++)
	{
		if (str[len] == 59)
			continue;
		if (str[len + 1] == 59)
			count++;
	}
	if (!len)
		return (0);
	if (str[len - 1] != 59)
		count++;
	if (count == 0)
		return (0);

	return (count);
}

#if 0
void execute_command(const char *cmd)
{
	token = strtok(strdup(cmd), " ");
	int i = 0;
	while (token != NULL)
	{
		args[i++] = token;
		token = strtok(NULL, " ");
	}
	args[i] = NULL;

	if (execvp(args[0], args) == -1)
	{
		perror("execvp");
		exit(EXIT_FAILURE);
	}
}
#endif
