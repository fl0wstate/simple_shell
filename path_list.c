#include "main.h"

/**
 * path_list - creates a linkedlist of PATH directories
 * @mode_args: struct (read main.h)
 *
 * Return: pointer to the head
 */
list_t *path_list(m_args *mode_args)
{
	char *tok = 0, *delim = ":";
	list_t *head = 0;
	char *PATH = _getenv("PATH");

	if (!PATH)
		return (0);

	_strcpy(mode_args->PATH, PATH);

	tok = _strtok(mode_args->PATH, delim);
	while (tok)
	{
		prepend(&head, tok);
		tok = _strtok(0, delim);
	}

	return (head);
}
