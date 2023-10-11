#include "main.h"

/**
 * _strlen - returns the length of a string
 * @s: pointer to string
 *
 * Return: the length of s
 */
int _strlen(char *s)
{
	int len = 0;

	if (!s)
		return (len);
	for (; s[len]; len++)
		;
	return (len);
}

