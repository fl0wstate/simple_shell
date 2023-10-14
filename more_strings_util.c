#include "main.h"

/**
 * _strlen - return the length of an array
 * @s: array of chars
 * Return: number of chars in a string
 */
size_t _strlen(char *s)
{
	size_t len = 0;

	while (s && s[len])
	{
		len++;
	}
	return (len);
}

/**
 * _strdup - returns a pointer to a newly allocated space in memory,
 * which contains a copy of the string given as a parameter.
 * @str: string to copy
 *
 * Return: a pointer to the copy or `NULL`
 */
char *_strdup(char *str)
{
	int len = 0, i = 0;
	char *cpy;

	if (!str)
		return (0);

	for (; str[len]; len++)
		;
	cpy = malloc(sizeof(char) * (len + 1));

	if (!cpy)
		return (0);

	for (; str[i]; i++)
		cpy[i] = str[i];
	cpy[i] = '\0';

	return (cpy);
}
