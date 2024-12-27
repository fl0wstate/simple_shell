#include "main.h"

/**
 * _atoi - converting string to int
 * @s: pointer to a string
 * Return: converted value or 0 on error
 */
int _atoi(char *s)
{
	unsigned int num = 0, sign = 1;

	while (*s)
	{
		if (*s == '-')
			sign *= -1;
		if (_isdigit(*s))
			num = (num * 10) + (*s - 48);
		s++;
	}

	return (num * sign);
}
