#include "main.h"

/**
 * free_buf - free buffer and set it to NULL
 * @buff: address of array of strings
 * @buf: address of simple buffer
 * @flag: to determine it's array or not
 */
void free_buf(char ***buff, char **buf, int flag)
{
	if (flag)
	{
		if (buff && *buff)
		{
			free(*buff);
			*buff = 0;
		}
	}
	else
	{
		if (buf && *buf)
		{
			free(*buf);
			*buf = 0;
		}
	}
}
