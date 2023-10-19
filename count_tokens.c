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
 * count_tokens - count number of tokens in a string based on delmitier
 * @str: string pointer
 * @delim: string pointer
 *
 * Return: number of tokens,
 * 0 on failure
 */
int count_tokens(char *str, char *delim)
{
	int len = 0, count = 0;

	if (!str)
		return (0);
	for (; str[len]; len++)
	{
		if (!str[len + 1])
			break;
		if (_strchr(delim, str[len]))
			continue;
		if (_strchr(delim, str[len + 1]))
			count++;
	}
	if (!len)
		return (0);
	if (!_strchr(delim, str[len - 1]))
		count++;

	return (count);
}
