#ifndef HEADER
#define HEADER
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#define BUFFER 120
#define REOF 0
extern char **environ;
unsigned int _strspn(char *s, const char *accept);
char *_strtok(char *str, const char *delim);
char *_strchr(const char *s, char c);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
void *adjust_book(char *ptr, unsigned int old_size, unsigned int new_size);
int getline_error(char *str);
char *str_concat(char *s1, char *s2);
int _strncmp(char *str1, char *str2, int b);
char *_strdup(char *str);
char *_strpbrk(char *s, char *accept);
int _strlen(char *s);
char *_getenv(const char *name);

#endif /* HEADER */
