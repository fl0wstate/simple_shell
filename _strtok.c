#include "main.h"

/**
 * _strtok - tokenize string base on delimiter
 * @s: string pointer
 * @delim: delimiter
 *
 * Return: token on each iteration, or `NULL`
 */
char *_strtok(char *s, const char *delim)
{
	static char *tok;
	int i = 0, flag = 0;

	if (s)
		tok = s;
	if (!delim || !tok || !*tok)
		return (0);
	for (i = 0; tok[i]; i++)
	{
		if (_strchr(delim, tok[i]))
		{
			flag = 1;
			if (!i)
			{
				tok = tok + i + 1 + _strspn(tok + i + 1, delim);
				s = _strtok(0, delim);
				break;
			}
			else
			{
				tok[i] = 0;
				s = tok;
				break;
			}
		}
		else
			flag = 0;
	}
	if (i && tok[i + 1] && flag)
		tok = tok + i + 1 + _strspn(tok + i + 1, delim);
	else if (i)
	{
		s = tok;
		tok = 0;
	}

	return (s);
}
