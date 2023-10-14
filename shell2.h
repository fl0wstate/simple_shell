#ifndef __SHELL_01__
#define __SHELL_01__

/* Header files */
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <error.h>
#include <sys/stat.h>
#include <time.h>
#include <stdbool.h>
#include <sys/signal.h>
#include <stdlib.h>
#include <stdarg.h>


/* custom builtin functions struct */

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
typedef struct format_specifiers
{
	char form_t;
	int (*call)(va_list *);
} specifiers_x;

/* functions for print */
int _ui_arg(va_list *ap);
int _string_arg(va_list *ap);

/* for signal handling */
typedef struct memory_pointers
{
	char *cmd;
	int count;
	char **argv;
} error_h;

/* aliases */
typedef unsigned int long uli;
typedef unsigned int ui;
typedef long int li;

/* Defined macro */
#define BUFFER 120
#define REOF 0
#define BUFF_SIZE 1024

/* String function prototypes */
int count_words(char *str);
int _printf(const char *format, ...);

/* Memory management */
void malloc_check(char *pointer);
void malloc_check_prev(char *pointer, char *prev_alloc);
void malloc_check_prev_double(char **pointer, char *prev_alloc);
void malloc_check_all(char *pointer, char *prev_alloc, char **pointers, int i);

/* Shell functions prototypes */
char *start_shell(void);
char **tokenize_command(char *cmd);
int execute_command(char **tokens, char *cmd, char **argv, int count, char *s);

#endif
