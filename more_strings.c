#include "shell.h"

/**
 * _strpbrk - searches a string for any of a set of bytes.
 * @s: string pointer
 * @accept: string to look up in `s`
 *
 * Return: pointer to the byte in `s` that matches one of the bytes in accept,
 * or NULL if no such byte is found
 */
char *_strpbrk(char *s, char *accept)
{
	int i = 0, j;

	for (; s[i]; i++)
		for (j = 0; accept[j]; j++)
		{
			if (s[i] == accept[j])
				return (&s[i]);
		}
	return (NULL);
}
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
/**
 * _strcpy - copies the string pointed to by src,
 * including the terminating null byte (\0),
 * to the buffer pointed to by dest
 * @dest: destination pointer
 * @src: source pointer
 *
 * Return: pointer to dest
 */
char *_strcpy(char *dest, char *src)
{
	int i = 0;

	while (*src)
	{
		dest[i] = *src;
		src++;
		i++;
	}
	dest[i] = '\0';

	return (dest);
}
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
/**
 * str_concat - concatenates two strings.
 * @s1: 1st string
 * @s2: 2nd string
 *
 * Return: pointer to the concatenated string,
 * `NULL` on failure
 */
char *str_concat(char *s1, char *s2)
{

	int i = 0, j = 0, k = 0, len1 = 0, len2 = 0, size;
	char *ptr;

	for (; (s1 && s1[len1]) || (s2 && s2[len2]); )
	{
		if (s1 && s1[len1])
			len1++;
		if (s2 && s2[len2])
			len2++;
	}
	size = len1 + len2 + 1;
	ptr = malloc(sizeof(char) * size);

	if (!ptr)
		return (0);

	for (; i < size; i++)
	{
		ptr[i] = s1 && s1[j] ? s1[j++] : s2 && s2[k] ? s2[k++] : '\0';
	}

	return (ptr);
}
