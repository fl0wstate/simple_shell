#include "main.h"

/**
 * utoa - convert unsigned int to string
 * @n: unsigned integer
 *
 * Return: string pointer to number
 */
char *utoa(ui n)
{
	char *buf = malloc(BUFFER);

	_utoa(n, buf, 0);
	str_rev(buf);

	return (buf);
}

/**
 * _utoa - helper function recursivly assinged value to buffer
 * @n: unsigned integer
 * @buf: buffer of size 1024
 * @idx: cursor to fill the buffer
 *
 * Return: string pointer to number
 */
char *_utoa(unsigned int n, char *buf, unsigned int idx)
{
	if (n < 10)
	{
		buf[idx] = n % 10 + 48;
		buf[idx + 1] = 0;
		return (buf);
	}
	buf = _utoa(n / 10, buf, idx + 1);
	buf[idx] = n % 10 + 48;

	return (buf);
}
