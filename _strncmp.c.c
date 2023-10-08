#include "main.h"

/**
 * _strncmp - compare 2 strings for certain bytes
 * @str1: 1st string
 * @str2: 2nd string
 * @b: bytes to compare
 *
 * Return: 0 on success,
 * negative str1 < str2,
 * positive otherwise
 */
int _strncmp(char *str1, char *str2, int b)
{
	int i = 0;

	for (; i < b && str1[i] && str2[i]; i++)
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
	}

	return (0);
}
