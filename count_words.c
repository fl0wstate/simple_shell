#include "main.h"

/**
 * count_words - count number of words in a string
 * @str: string pointer
 *
 * Return: number of words,
 * 0 on failure
 */
int count_words(char *str)
{
	int len = 0, count = 0;

	if (!str)
		return (0);
	for (; str[len]; len++)
	{
		if (str[len] == 32)
			continue;
		if (str[len + 1] == 32)
			count++;
	}
	if (!len)
		return (0);
	if (str[len - 1] != 32)
		count++;
	if (count == 0)
		return (0);

	return (count);
}
/**
 * count_tokens - count number of words in a string
 * @str: string pointer
 * @delim: delimeter char value
 * @_strint: function pointer
 *
 * Return: number of words,
 * 0 on failure
 */
int count_tokens(char *str, char delim)
{
	int len = 0, count = 0;

	if (!str)
		return (0);
	for (; str[len]; len++)
	{
		if ((int)(str[len]) == (int)(delim))
			continue;
		if ((int)(str[len + 1]) == (int)(delim))
			count++;
	}
	if (!len)
		return (0);
	if ((int)(str[len - 1]) != (int)(delim))
		count++;
	if (count == 0)
		return (0);

	return (count);
}
