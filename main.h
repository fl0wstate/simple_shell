#ifndef HEADER
#define HEADER
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define BUFFER 120
#define REOF 0
unsigned int _strspn(char *s, const char *accept);
char *_strtok(char *str, const char *delim);
char *_strchr(const char *s, char c);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
void *adjust_book(char *ptr, unsigned int old_size, unsigned int new_size);
#endif /* HEADER */
