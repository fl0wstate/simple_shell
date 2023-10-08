#include "main.h"

/**
 * _strspn - gets the length of a prefix substring.
 * @s: string pointer
 * @accept: string pointer to look for in s
 *
 * Return: number of bytes in the initial segment of s,
 * which consist only of bytes from accept
 */
unsigned int _strspn(char *s, const char *accept)
{
	int i = 0, count = 0, j;

	for (; s[i]; i++)
	{
		if (count < i)
			break;
		for (j = 0; accept[j]; j++)
			if (s[i] == accept[j])
			{
				count++;
				break;
			}
	}
	return (count);


}
