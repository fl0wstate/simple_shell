#include "main.h"

char *utoa(ui n)
{
	char *buf = malloc(BUFFER);

	_utoa(n, buf, 0);
	str_rev(buf);

	return (buf);
}

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
