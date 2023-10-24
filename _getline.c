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
	size_t old, i = 0, init = !*line || !*len ? BUFFER : *len;
	ssize_t bytes = 0;
	int count = 0;

	/*TODO: handle errors with allocation */
	*len = !*line || !*len ? init : *len;
	if (!*line || *len == 0)
	{
		*line = malloc(init);
		if (!*line)
			return (getline_error("malloc"));
	}
	while ((bytes = read(stream->_fileno, *line + i, BUFFER)) > REOF)
	{
		count++;
		i += bytes;
		if (i >= init)
		{
			old = init;
			init *= 2;
			*len = init;
			*line = _realloc(*line, old, init);
			if (!*line)
				return (getline_error("realloc"));
		}
		if ((*line)[i - 1] == '\n')
			break;
	}
	if (bytes == REOF)
	{
		(*line)[i] = 0;
		return (EOF);
	}
	if (count > 2)
		*len = i + 1;
	(*line)[i] = 0;

	return (i);
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
	return (EOF);
}
