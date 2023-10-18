#include "main.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int execute_commands(char *path, char **cmd, char **envp);
int count_commands(char *str);
/**
 * executes_command - making a child process;
 *
 * @mode_args: pointer to a sturct
 *
 * Return: 1 on failure 0 on success
 */
int executes_command(m_args *mode_args)
{
	interactive(mode_args);
	return (0);
#if 0
	pid_t child_pid = fork();
	if (child_pid == 0)
	{
		execve(*mode_args->path, *mode_args->tokens, *mode_args->env);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	else
	{
		wait(NULL);
	}
	return (1);
#endif
}
/**
 * command_separator_handler - does an execution for each command
 * @mode_args: struct containing all the command line input
 * Return: void
 */
void command_separator_handler(m_args *mode_args)
{
	int i = 0, j = 0, d = 0, status = 0;
	char **new_tokens_arry = {NULL};
	char *token = NULL;

	new_tokens_arry = malloc(sizeof(char *) *
			count_tokens(*mode_args->line, ';') + 1);

	_dprintf(STDOUT_FILENO,
			"command count -> %u\n", count_tokens(*mode_args->line, ';'));
	/*:TODO: should i fork each separator command or not after beign invoked?? */
	for (i = 0, token = _strtok(*mode_args->line, ";");
			token; i++, token = _strtok(0, ";"))
	{
		d = _strspn(token, " ");
		token += d;
		new_tokens_arry[i] = token;
		printf("command [%d] -> %s\n", i, new_tokens_arry[i]);
	}
	/*:TODO: invalid read errror */
	for (j = 0; new_tokens_arry[j]; j++)
	{
		*mode_args->tokens = tokenize_line(new_tokens_arry[j]);
		*mode_args->path = _which(new_tokens_arry[j], *mode_args->list_path);
		status = executes_command(mode_args);
		if (status)
			printf("check exit status here >[for AND && OR]<\n");
	}
	free(new_tokens_arry);
	free_safe(mode_args);
	/* don't forget to free me dwang!! */
}
#if 0
/**
 * command_separator_handler - does an execution for each command
 * @mode_args: struct containing all the command line input
 * Return: void
 */
void command_semicolon_handler(m_args *mode_args)
{
	for (; new_tokens_arry[j]; j++)
	{
		*mode_args->tokens = tokenize_line(new_tokens_arry[j]);
		*mode_args->path = _which(new_tokens_arry[0], *mode_args->list_path);
		status = executes_command(mode_args);
		if (status)
			printf("check exit status here >[for AND && OR]<\n");
	}
	free(new_tokens_arry);
	free_safe(mode_args);
	/* don't forget to free me dwang!! */
}
#endif
#if 0
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
#endif
/**
 * command_handler_checker - checks for the right command execution to happen
 * @mode_args: struct containing command line input
 * Return: void
 */
void command_handler_checker(m_args *mode_args)
{
	char *delims = ";&|";
	char *found_separator = _strpbrk(*mode_args->line, delims);

	if (found_separator)
	{
		switch (*found_separator)
		{
			case ';':
				command_separator_handler(mode_args);
				break;
			case '&':
				command_AND_handler(mode_args);
				break;
			case '|':
				command_OR_handler(mode_args);
				break;
			default:
				printf("No such command separator\n");
				break;
		}
	}
}
/**
 * command_OR_handler - handle when an or separator works or not
 * @mode_args: pointer to a struct visit
 * [main.h] to get more details
 * Return: void
 */
void command_OR_handler(m_args *mode_args)
{
	(void)mode_args;

	_dprintf(STDOUT_FILENO, "Comming soon!!");
}

/**
 * command_AND_handler - handle when an or separator works or not
 * @mode_args: pointer to a struct visit
 * [main.h] to get more details
 * Return: void
 */
void command_AND_handler(m_args *mode_args)
{
	(void)mode_args;

	_dprintf(STDOUT_FILENO, "Comming soon!!");
}
