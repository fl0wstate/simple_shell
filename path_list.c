#include "main.h"

/**
 * path_list - creates a linkedlist of PATH directories
 *
 * Return: pointer to the head
 */
list_t *path_list()
{
	char *tok = 0, *delim = ":", *path = _getenv("PATH");
	list_t *head = 0;

	tok = _strtok(path, delim);
	while (tok)
	{
		prepend(&head, tok);
		tok = _strtok(0, delim);
	}

	return (head);
}
