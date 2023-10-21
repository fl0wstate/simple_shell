#ifndef HEADER
#define HEADER
#include <bits/types/FILE.h>
#include <linux/limits.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/signal.h>
#include <errno.h>

/* -------------MACROS------------ */
#define BUFFER 120
#define REOF 0
#define BUFF_SIZE 1024
#define AND '&'
#define OR '|'

/* ------------ALIASES------------ */
typedef unsigned int long uli;
typedef unsigned int ui;
typedef long int li;
typedef struct list_s list_t;
typedef struct mode_arguments m_args;
typedef struct builtin_commands builtin_t;
typedef struct format_specifiers specifiers_x;
typedef struct environ_configuration env_config;
typedef struct alias_s alias_t;

/* ----------GLOBALS--------------- */
extern char **environ;

/* ----------STRUCTS-------------- */
/**
 * struct environ_configuration - store info of environ
 * @idx: index of environ to update
 * @len: length of environment variables
 * @name: name to update its value
 * @free: flag when to free the envrion
 */
struct environ_configuration
{
	int idx;
	int len;
	int *free;
	const char *name;
};
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
	int (*call)(va_list *, int fd);
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
 * struct alias_s - singly linked list to store aliases
 * @name: alias name
 * @value: alias value
 * @next: points to the next node
 *
 * Description: singly linked list node structure
 */
struct alias_s
{
	char *name;
	char *value;
	struct alias_s *next;
};

/**
 * struct mode_arguments - mode_hanlder (non/interactive)
 * @cmd_toks: tokens represent the command from
 * @tokens: address of array of strings
 * @env: address of environment variables
 * @av: argument vector
 * @args: custom argument
 * @path: address to the executable file
 * @line: address of line read from stdin
 * @cmd_count: integer represents how many time the user interact
 * @list_path: address  of struct `list_t`
 * @alias: struct `alias_s`
 * @free: flag when to free the envrion
 * @_errno: error number to feed to exit
 * @ppid: shell process id
 * @PATH: env variable
 * @logcials: array of char contains values of `AND` and/or `OR`
 * and it has initial size of `BUFFER`
 *
 * Description: mode arguments structures
 */
struct mode_arguments
{
	char **cmd_toks;
	char **tokens;
	char ***env;
	char *args[3];
	char logcials[BUFFER];
	char PATH[BUFF_SIZE];
	char **av;
	char *path;
	char *line;
	ui *cmd_count;
	ui free;
	ui _errno;
	pid_t ppid;
	alias_t *alias;
	list_t **list_path;
};

/**
 * struct builtin_commands - handler for all the builtin commands
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
	void (*builtin)(m_args *mode_args);
};

/* -------------------UTILS----------------- */
char *get_alias(char *name, m_args *mode_args);
void print_alias(alias_t *node, int flag);
void mutate_aliases(char *name, char *value, m_args *mode_args);
void free_aliases(alias_t *head);
void run(int mode_stat, int idx, m_args *mode_args);
void executor(int logical_count, int mode_stat, m_args *mode_args);
int set_logicals(m_args *mode_args);
void str_rev(char *str);
char *utoa(ui n);
char *_utoa(ui n, char *buf, ui idx);
char **expansion_handler(char *str, m_args *mode_args);
void EOF_handler(m_args *mode_args);
void free_safe(m_args *mode_args);
void env_builtin(m_args *mode_args);
void unsetenv_builtin(m_args *mode_args);
void setenv_builtin(m_args *mode_args);
void alias_builtin(m_args *mode_args);
int builtin_handler(m_args *mode_args);
void free_envcpy(char ***cpy);
void (*mode(int fd))(m_args *mode_arguments);
void interactive(m_args *mode_arguments);
void non_interactive(m_args *mode_arguments);
void free_buf(char ***buff, char **buf, int flag);
char **tokenize_line(char *line, char *delim);
char *str_concat(char *s1, char *s2);
int getline_error(char *str);
void prompt(void);
list_t *prepend(list_t **head, const char *str);
list_t *append(list_t **head, const char *str);
void free_list(list_t *head);
list_t *path_list(m_args *mode_args);
char *start_shell(void);
char **tokenize_command(char *cmd);
int execute_command(char **tokens, char *cmd, char **argv, int count, char *s);
int _ui_arg(va_list *ap, int fd);
int _string_arg(va_list *ap, int fd);
int _char_arg(va_list *ap, int fd);
int count_words(char *str);
void malloc_check(char *pointer);
void malloc_check_prev(char *pointer, char *prev_alloc);
void malloc_check_prev_double(char **pointer, char *prev_alloc);
void malloc_check_all(char *pointer, char *prev_alloc, char **pointers, int i);
void *adjust_book(char *ptr, ui old_size, ui new_size);
ui digit_counter(int num);
int adjust(const char *name, const char *value, int overwrite, env_config);
int add_new(const char *name, const char *value, env_config);
int set_envconfig(env_config *);
/* addons from MK */
void exit_builtin(m_args *mode_args);
void change_directory(m_args *mode_args);
int count_tokens(char *str, char *delim);

/* -------------------MOCKS---------------------- */
int _setenv(const char *name, const char *value, int overwrite);
int _unsetenv(env_config *);
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
int _dprintf(int fd, const char *format, ...);
int _atoi(char *s);
int _isdigit(int c);

#endif /* HEADER */
