#include "main.h"

/**
 * prepend - adds a new node at the beginning of a list_t list.
 * @head: the head of the list
 * @str: string pointer as member of the node
 *
 * Return: address to the newly created node,
 * `NULL` on failure
 */
list_t *prepend(list_t **head, const char *str)
{
	list_t *new;

	new = malloc(sizeof(list_t));
	if (!new)
		return (NULL);

	new->next = *head;
	*head = new;
	new->str = _strdup((char *)str);

	return (new);
}

/**
 * append - adds a new node at the end of a list_t list.
 * @head: address of the head pointer
 * @str: string pointer as member of node
 *
 * Return: adddress of the new node,
 * NULL on failure
 */
list_t *append(list_t **head, const char *str)
{
	list_t *tmp = *head, *tail;

	if (!tmp)
	{
		return (prepend(head, str));
	}
	tail = malloc(sizeof(*tail));
	if (!tail)
		return (NULL);

	for (; tmp; tmp = tmp->next)
	{
		if (!(tmp->next))
		{
			tmp->next = tail;
			tail->str = _strdup((char *)str);
			tail->next = NULL;
		}
	}

	return (tail);
}

/**
 * free_list - frees a list
 * @head: head of the list
 *
 */
void free_list(list_t *head)
{
	if (head)
	{
		free_list(head->next);
		free(head->str);
		free(head);
		head = 0;
	}
}

