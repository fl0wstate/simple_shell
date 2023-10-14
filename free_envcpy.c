#include "main.h"

/**
 * free_envcpy - free environ copy
 * @cpy: copy of environ
 */
void free_envcpy(char ***cpy)
{
	int i = 0;

	if (*cpy)
	{
		for (i = 0; (*cpy)[i]; i++)
		{
			free((*cpy)[i]);
			(*cpy)[i] = 0;
		}
		free(*cpy);
		*cpy = 0;
	}
}
