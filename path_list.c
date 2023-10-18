#include "main.h"
/**
 * path_list - creates a linkedlist of PATH directories
 *
 * Return: pointer to the head
 */
list_t *path_list()
{
	char *tok = 0, *delim = "PATH=:", *path = _getenv("PATH");
	list_t *head = 0, *current;

	tok = _strtok(path, delim);
	while (tok)
	{
		prepend(&head, tok);
		tok = _strtok(0, delim);
	}

	current = head;
	while (current)
	{
		_dprintf(STDOUT_FILENO, "%Node [%s]\n", current->str);
		current = current->next;
	}

	return (head);
}
