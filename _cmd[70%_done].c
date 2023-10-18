#include "main.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

void command_AND_handler(m_args *mode_args, char ch, char *delim);
void command_OR_handler(m_args *mode_args, char ch, char *delim);
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
}
/**
 * command_tokenizer - does an execution for each command
 * @mode_args: struct containing all the command line input
 * @ch: character for count_commands function
 * @delim: type of delemiter to use
 * Return: void
 */
char **command_tokenizer(m_args *mode_args, char ch, char *delim)
{
	int i = 0, d = 0;
	char **new_tokens_arry = {NULL};
	char *token = NULL;

	new_tokens_arry = malloc(sizeof(char *) *
			count_commands(*mode_args->line) + 1);
	/*just to be sure */
	_dprintf(STDOUT_FILENO,
			"command count -> %u\n", count_tokens(*mode_args->line, ch));

	for (i = 0, token = _strtok(*mode_args->line, delim);
			token; i++, token = _strtok(0, delim))
	{
		d = _strspn(token, " ");
		token += d;
		new_tokens_arry[i] = token;
	}
	new_tokens_arry[i] = NULL; /* terminate the command array */
	return (new_tokens_arry);
}
/**
 * command_semicolon_handler - does an execution for each command
 * @mode_args: struct containing all the command line input
 * @ch: character for count_commands function
 * @delim: delimeter for _strtok
 * Return: void
 */
void command_semicolon_handler(m_args *mode_args, char ch, char *delim)
{
	int j = 0, status;

	char **commands = command_tokenizer(mode_args, ch, delim);

	for (; (commands)[j]; j++)
	{
		*mode_args->tokens = tokenize_line((commands)[j]);
		*mode_args->path = _which((commands)[j], *mode_args->list_path);
		status = executes_command(mode_args);
		if (status)
			printf("check exit status here >[for AND && OR]<\n");
	}
	/* don't forget to free me dwang!! */
	free(commands);
	free_safe(mode_args);
}
/**
 * command_handler_checker - checks for the right command execution to happen
 * Entry point start here then calls which commands that matches delims
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
				command_semicolon_handler(mode_args, ';', ";");
				break;
			case '&':
				command_AND_handler(mode_args, '&', "&&");
				break;
			case '|':
				command_OR_handler(mode_args, '|', "||");
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
 * @ch: character for count_commands function
 * @delim: delimeter for _strtok
 * Return: void
 */
void command_OR_handler(m_args *mode_args, char ch, char *delim)
{
	int j = 0, status;

	char **commands = command_tokenizer(mode_args, ch, delim);

	for (; (commands)[j]; j++)
	{
		*mode_args->tokens = tokenize_line((commands)[j]);
		*mode_args->path = _which((commands)[j], *mode_args->list_path);
		status = executes_command(mode_args);
		/*:TODO: same as ; but check it anyways */
		if (status)
			printf("check exit status here >[for AND && OR]<\n");
	}
	/* don't forget to free me dwang!! */
	free(commands);
	free_safe(mode_args);
}

/**
 * command_AND_handler - handle when an or separator works or not
 * @mode_args: pointer to a struct visit
 * [main.h] to get more details
 * @ch: character for count_commands function
 * @delim: delimeter for _strtok
 * Return: void
 */
void command_AND_handler(m_args *mode_args, char ch, char *delim)
{
	int j = 0, status;

	char **commands = command_tokenizer(mode_args, ch, delim);

	for (; (commands)[j]; j++)
	{
		*mode_args->tokens = tokenize_line((commands)[j]);
		*mode_args->path = _which((commands)[j], *mode_args->list_path);
		status = executes_command(mode_args);
		/**
		 * :TODO: very crucial to check the return value of
		 * execute_commands to stop the loop
		 */
		if (status)
			printf("check exit status here >[for AND && OR]<\n");
	}
	/* don't forget to free me dwang!! */
	free(commands);
	free_safe(mode_args);
}
