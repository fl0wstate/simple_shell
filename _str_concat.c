#include "main.h"

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
