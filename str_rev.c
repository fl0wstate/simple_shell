#include "main.h"

void str_rev(char *str)
{
	int i = 0, len = _strlen(str);

	if (len == 1)
		return;
	for (; i < len - 1; i++, len--)
	{
		str[i] ^= str[len - 1];
		str[len - 1] ^= str[i];
		str[i] ^= str[len - 1];
	}
}
