#include "main.h"
/**
 * path_list - creates a linkedlist of PATH directories
 * @mode_args: struct (read main.h)
 *
 * Return: pointer to the head
 */
list_t *path_list(m_args *mode_args)
{
	char *tok = 0, *delim = "PATH=:";
	list_t *head = 0;

	_strcpy(mode_args->PATH, _getenv("PATH"));

	tok = _strtok(mode_args->PATH, delim);
	while (tok)
	{
		prepend(&head, tok);
		tok = _strtok(0, delim);
	}

	return (head);
}
