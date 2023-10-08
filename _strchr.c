#include "main.h"

/**
 *  _strchr - locates a character in a string
 * @s: string pointer
 * @c: character to find
 *
 * Return: pointer to the first occurence of `c`
 */
char *_strchr(const char *s, char c)
{
	const char *ptr = NULL;

	for (; *s; s++)
	{
		if (*s == c)
		{
			ptr = s;
			break;
		}
	}

	/* `c` is null-terminating character */
	if (c == '\0')
		ptr = s;

	/* there's no match */
	if (ptr == NULL)
		return (NULL);

	/* match found */
	return ((char *)ptr);
}
