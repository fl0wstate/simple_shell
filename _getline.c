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

	/*TODO: handle errors with allocation */
	*len = !*line || !*len ? init : *len;
	if (!*line || *len == 0)
		*line = malloc(init);
	/*while ((bytes = read(stream->_fileno, &((*line)[i++]), 1)) > REOF)*/
	while ((bytes = read(stream->_fileno, *line, init)) > REOF)
	{
		i += bytes;
		printf("i = %ld, bytes = %lu, init = %ld\n", i, bytes, init);
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
				init += bytes;
			}
			*len = init;
			printf("Reallocate by %ld\n", init);
			*line = _realloc(*line, old, init);
		}
		if ((*line)[bytes - 1] == '\n')
		{
			printf("[%ld] ------------> new line character\n", i - 1);
			break;
		}
	}
	if (bytes == REOF)
	{
		printf("EOF i = %ld, line = %s\n", i, *line);
		/*(*line)[i - 1] = 0;*/
		return (EOF);
	}
	(*line)[bytes] = 0;

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
	return (-1);
}
