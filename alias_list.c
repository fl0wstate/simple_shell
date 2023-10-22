#include "main.h"

/**
 * append_alias - append new alias to the list
 * @head: pointer to the head
 * @name: alias name
 * @value: alias vlaue
 *
 * Return: pointer to the appended node
 */
alias_t *append_alias(alias_t **head, char *name, char *value)
{
	alias_t *new_alias, *tmp = *head;

	new_alias = malloc(sizeof(alias_t));
	if (!new_alias)
		return (0);
	new_alias->name = _strdup(name);
	new_alias->value = _strdup(value);
	if (!tmp)
	{
		new_alias->next = *head;
		*head = new_alias;
	}
	else
		for (; tmp; tmp = tmp->next)
			if (!tmp->next)
			{
				tmp->next = new_alias;
				new_alias->next = 0;
			}
	return (new_alias);
}
/**
 * free_aliases - frees alias linked list
 * @head: pointer to the list head
 */
void free_aliases(alias_t *head)
{
	if (head)
	{
		free_aliases(head->next);
		free(head->name);
		free(head->value);
		free(head);
		head = 0;
	}
}
