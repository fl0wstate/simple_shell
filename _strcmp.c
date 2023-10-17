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
	unsigned int i = 0;

	while (*s1 != '\0' && *s2 != '\0')
	{
		if (s1[i] < s2[i])
			return (-1);
		else if (*s1 > *s2)
			return (1);
		s1++;
		s2++;
	}
	if (*s1 == '\0' && *s2 == '\0')
		return (0);
	else if (*s1 == '\0')
		return (-1);
	else
		return (1);
}
