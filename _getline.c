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
	static int count;

	count = 0, *len = !*line || !*len ? init : *len;

	fflush(stdout);
	if (!*line || *len == 0)
	{
		*line = malloc(init);
		if (!*line)
			return (getline_error("malloc"));
	}
	while ((bytes = read(stream->_fileno, &((*line)[i++]), 1)) != EOF)
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
			line = _realloc(*line, old,  init);
			if (!*line)
				return (getline_error("realloc"));
		}
		if ((*line)[i - 1] == '\n')
		{
			(*line)[i] = 0;
			return (i);
		}
	}

	return (-1);
}
/**
 * getline_error - print error and exit
 * @str: string of error
 *
 * Return: -1 as error number
 */
int getline_error(char *str)
{
	perror(str);
	return (-1);
}
