#include "shell2.h"
#include <endian.h>
#include <signal.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void _handler(int num)
{
	sig = num;
}
/**
 * prompt - prompt the user once he enters the shell
 * Return: void
 */
void prompt(void)
{
	_printf("$ ");
}
/**
 * start_shell - reads the user inputs in shell
 * Return: char pointer to the string of chars
 * entered by the user
 */
char *start_shell(void)
{
	char *buf = NULL;
	size_t get = 0;
	ssize_t reads = 0;

	prompt();
	while ((reads = getline(&buf, &get, stdin)) == -1)
	{
		free(buf);
		exit(EXIT_FAILURE);
	}
	buf[reads - 1] = '\0';
	return (buf);
}

/**
 * tokenize_command - simple function that tokenizes a string of chars
 * @cmd: pointer to the string of char
 * Return: pointer to an array of arrays with tokens
 */
char **tokenize_command(char *cmd)
{
	int count = 0; /*len = 0;*/
	char **tokens;
	char *token;
	char *delim = " ";

	count = count_words(cmd);
	if (count == 0)
	{
		perror("count");
		free(cmd);
		exit(EXIT_FAILURE);
	}
	tokens = malloc(sizeof(tokens) * (count + 1));
	malloc_check_prev_double(tokens, cmd);
	/* check me out ^^ */

	token = strtok(cmd, delim);
	count = 0;
	while (token)
	{
		tokens[count] = token;
		count++;
		token = strtok(NULL, delim);
	}
	tokens[count] = NULL;
	count = 0;
	return (tokens);
}
/**
 * execute_command - executes the tokenized command entered
 * by the user
 *
 * @tokens: pointer to pointers in an array
 * @cmd: commands passed
 * @argv: not
 * @s: not
 * @count: not
 *
 * Return: nothing on success, -1 on failure
 */
int execute_command(char **tokens, char *cmd, char **argv, int count, char *s)
{
	pid_t frk_id;
	int status, i = 0;

	frk_id = fork();
	if (frk_id == 0)
	{
		if (execve(tokens[i], tokens, NULL) == -1)
		{
			_printf("%s : %u: %s: not a command\n",
					argv[0], count, s);
			free(cmd);
			free(tokens);
			exit(EXIT_FAILURE);
		}
	}
	else if (frk_id < 0)
		perror("forking");
	else
	{
		wait(&status);
		free(cmd);
		free(tokens);
	}
	/* back to the parent */
	return (1); /* if all is good then return 1 */
}
/**
 * main - starting point of our shell
 *
 * @ac: argument count
 * @av: argument vector
 * @envp: environment variables
 *
 * Return: 1 failure, 0 success
 */
int main(int ac __attribute__((unused)),
		char **av, char **envp)
{
	int check = 1;
	static int cn;

	cn = 1;
	while (check)
	{
		char *cmd;
		char **tokens;

		if (isatty(STDIN_FILENO))
		{
			cmd = start_shell();
			tokens = tokenize_command(cmd);
			check = execute_command(tokens, cmd, av, cn, cmd);

			signal(SIGINT, _handler);
			if (SIGINT == (const int)sig)
			{
				free(cmd);
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			size_t size = 0;

			while (getline(&cmd, &size, stdin) != -1)
			{
				cmd[strlen(cmd) - 1] = '\0';
				tokens = tokenize_command(cmd);
				check = execute_command(tokens, cmd, av, cn, cmd);
			}
			free(cmd);
			free(tokens);
			exit(EXIT_SUCCESS);
		}
		cn++;
	}
}
