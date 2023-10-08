#include "main.h"

/**
 * _getline - read line from stream
 * @line: address of buffer to update
 * @len: size of @line
 * @stream: stdin, stdout, stderr
 *
 * Return: the number of bytes read
 */
ssize_t _getline(char **line, size_t *len, FILE *stream)
{
	size_t init = !*line || !*len ? BUFFER : *len, i = 0, old;
	ssize_t bytes;
	static int count = 0;

	*len = !*line || !*len ? init : *len;

	if (!*line || *len == 0)
	{
		*line = malloc(init);
		if (!*line)
		{
			dprintf(STDERR_FILENO, "malloc: failed\n");
			return (-1);
		}
	}
	while ((bytes = read(stream->_fileno, &((*line)[i++]), 1)) > REOF)
	{
		if (i >= init)
		{
			if (++count < 2)
			{
				old = init;
				init *= 2;
			}
			else
			{
				old = init;
				init += bytes + 1;
			}
			*len = init;
			*line = _realloc(*line, old,  init);
			if (!*line)
			{
				dprintf(STDERR_FILENO, "realloc: failed\n");
				return (-1);
			}
		}
		if ((*line)[i - 1] == '\n')
			break;
	}
	if (bytes < REOF)
	{
		dprintf(STDERR_FILENO, "failed to read stream\n");
		return (-1);
	}

	(*line)[i] = 0;

	return (i);
}
