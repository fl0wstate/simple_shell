#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/cdefs.h>
#include <sys/wait.h>
#include <unistd.h>

int count_words(char *str);

/**
 * main - simple shell
 * @ac: arguments count
 * @av: arguments vector
 * @env: enviroment variables
 *
 * Return: 0 as exit status
 */
int main(int ac, char **av, char **env)
{
	ssize_t bytes;
	size_t n = 0;
	char *line = 0;
	pid_t fk_id;
	int status, i = 0;
	char **args = 0;
	char *tok = 0, *delim = " ";
	(void)ac;
	(void)av;

	while (-1)
	{
		printf("$ ");
		bytes = getline(&line, &n, stdin);
		if (bytes == EOF)
			free(line), exit(1);

		line[bytes - 1] = 0;
		args = malloc(sizeof(*args) * (count_words(line) + 1));
		if (!args)
			perror("malloc"), free(line), exit(1);
		for (i = 0, tok = strtok(line, delim); tok; i++, tok = strtok(0, delim))
		{
			args[i] = malloc(strlen(tok) + 1);
			if (!args[i])
			{
				while (i--)
					free(args[i]);
				free(args);
				free(line);
				perror("malloc");
				exit(1);
			}
			strcpy(args[i], tok);
		}
		args[i] = 0;
		fk_id = fork();
		if (fk_id < 0)
			perror("fork"), free(line), exit(1);

		if (!fk_id)
		{
			/* child */
			execve(args[0], args, env);
			/* if it fails; then below lines will be reachable */
			perror("execve");
			while (i--)
				free(args[i]);
			free(args);
			free(line);
			exit(1);
		}
		else
		{
			/* parent */
			wait(&status);
			free(line);
			while (i--)
				free(args[i]);
			free(args);
			line = 0;
		}
	}

	return (0);
}

/**
 * count_words - count number of words in a string
 * @str: string pointer
 *
 * Return: number of words,
 * 0 on failure
 */
int count_words(char *str)
{
	int len = 0, count = 0;

	if (!str)
		return (0);
	for (; str[len]; len++)
	{
		if (str[len] == 32)
			continue;
		if (str[len + 1] == 32)
			count++;
	}
	if (!len)
		return (0);
	if (str[len - 1] != 32)
		count++;
	if (count == 0)
		return (0);

	return (count);
}
