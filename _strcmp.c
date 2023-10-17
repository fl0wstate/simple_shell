#include "main.h"

/**
 * _strcmp - compares 2 strings
 * @s1: 1st string
 * @s2: 2nd string
 *
 * Return: 0 if s1 & s2 are equal,
 * a negative value if s1 < s2
 * a positive value if s1 > s2
 *
 */
int _strcmp(char *s1, char *s2)
{
	int ret = 0;

	/*TODO: fix the return value, when they're not equal */
	for (; *s1 || *s2; s1++, s2++)
	{
		if (*s1 != *s2)
		{
			ret = *s1 - *s2;
			break;
		}
	}

	return (ret);
}
