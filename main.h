#ifndef HEADER
#define HEADER
#include <bits/types/FILE.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/signal.h>
#include <stdbool.h>

/* -------------MACROS------------ */
#define BUFFER 120
#define REOF 0
#define BUFF_SIZE 1024

/* ------------ALIASES------------ */
typedef unsigned int long uli;
typedef unsigned int ui;
typedef long int li;
typedef struct list_s list_t;
typedef struct mode_arguments m_args;
typedef struct builtin_commands builtin_t;
typedef struct format_specifiers specifiers_x;

/* ----------GLOBALS--------------- */
extern char **environ;

/* ----------STRUCTS-------------- */
/**
 * struct format_specifiers - simple _printf
 * data structure
 *
 * @form_t: means format type passed
 * @call: function associated with the char passed
 *
 * Description: Simple data structure which is used to
 * show the relationship between a char passed and
 * function it relates to.
 */
struct format_specifiers
{
	char form_t;
	int (*call)(va_list *);
};

/**
 * struct list_s - singly linked list
 * @str: string - (malloc'ed string) represents path to executable
 * @len: length of the string
 * @next: points to the next node
 *
 * Description: singly linked list node structure
 */
struct list_s
{
	char *str;
	unsigned int len;
	struct list_s *next;
};

/**
 * struct mode_hanlder - mode_hanlder (non/interactive)
 * @tokens: address of array of strings
 * @env: address of environment variables
 * @av: argument vector
 * @path: address to the executable file
 * @cmd_count: integer represents how many time the user interact
 *
 * Description: singly linked list node structure
 */
struct mode_arguments
{
	char ***tokens;
	char ***env;
	char **av;
	char **path;
	char **line;
	char ***command_list;
	bool set_or_not_set;
	ui *cmd_count;
	list_t **list_path;
};

/**
 * struct x_builtins - handler for all the builtin commands
 * @cmd: a constant commmand char pointer to the actual
 * command entered by the user
 * @builtin function: a function pointer to all the builtin
 * commands.
 * 
 * Description: simple builtin struct to handle builtin commands
 */
struct builtin_commands
{
	const char *cmd;
	/* same as void (*builtin)(char ***tokens, char **line); 
	 * where tokens is an arrays of arrays */
	void (*builtin)(m_args *mode_args);
};

/* -------------------UTILS----------------- */
void free_envcpy(char ***cpy);
void (*mode(int fd))(m_args *mode_arguments);
void interactive(m_args *mode_arguments);
void non_interactive(m_args *mode_arguments);
void free_buf(char ***buff, char **buf, int flag);
char **tokenize_line(char *line);
char *str_concat(char *s1, char *s2);
int getline_error(char *str);
void prompt(void);
list_t *prepend(list_t **head, const char *str);
list_t *append(list_t **head, const char *str);
void free_list(list_t *head);
list_t *path_list(void);
char *start_shell(void);
char **tokenize_command(char *cmd);
int execute_command(char **tokens, char *cmd, char **argv, int count, char *s);
int _ui_arg(va_list *ap);
int _string_arg(va_list *ap);
int count_words(char *str);
void malloc_check(char *pointer);
void malloc_check_prev(char *pointer, char *prev_alloc);
void malloc_check_prev_double(char **pointer, char *prev_alloc);
void malloc_check_all(char *pointer, char *prev_alloc, char **pointers, int i);
void *adjust_book(char *ptr, ui old_size, ui new_size);
ui digit_counter(int num);

/* addons from MK */
void _builtins_commands(m_args *mode_args);
void help_builtin(m_args *mode_args);
void exit_builtin(m_args *mode_args);
void change_directory(m_args *mode_args);
void _get_cwd(m_args *mode_args);
/* void command_separator_handler(m_args *mode_args); */
int count_commands(char *str);
void command_separator_handler(char **line);

/* -------------------MOCKS---------------------- */
unsigned int _strspn(char *s, const char *accept);
char *_strtok(char *str, const char *delim);
char *_strchr(char *s, char c);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
int _strcmp(char *s1, char *s2);
int _strncmp(char *str1, char *str2, int b);
char *_strdup(char *str);
char *_strpbrk(char *s, char *accept);
size_t _strlen(char *s);
char *_getenv(const char *name);
char *_which(char *cmd, list_t *list_path);
char *_strcpy(char *dest, char *src);
ssize_t _getline(char **line, size_t *len, FILE *);
int _printf(const char *format, ...);
int _atoi(char *s);

#endif /* HEADER */
