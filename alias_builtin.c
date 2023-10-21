#include "main.h"

/**
 * alias_builtin - alias builtin command handler
 * @mode_args: struct (read main.h)
 */
void alias_builtin(m_args *mode_args)
{
	char *name;
	char *value;
	alias_t *tmp = mode_args->alias;

	if (!mode_args->tokens[1])
	{
		/*TODO: print list of aliases if any */
		(print_alias(tmp, 1));
		return;
	}
	name = _strtok(mode_args->tokens[1], "=");
	value = _strtok(0, "=");
	if (!value)
	{
		for (; tmp; tmp = tmp->next)
			if (!_strcmp(tmp->name, name))
				break;
		/*TODO: print that alias if any */
		(print_alias(tmp, 0));
		return;
	}

	while (name && value)
	{
		mutate_aliases(name, value, mode_args);
		name = _strtok(0, "=");
		value = _strtok(0, "=");
	}
}

/**
 * mutate_aliases - add or update alias
 * @name: alias name
 * @value: alias value
 * @mode_args: struct (read main.h)
 */
void mutate_aliases(char *name, char *value, m_args *mode_args)
{
	int overwrite = 0;
	alias_t *alias, *tmp = mode_args->alias;

	while (tmp)
	{
		if (!_strcmp(tmp->name, name))
		{
			overwrite = 1;
			break;
		}
		tmp = tmp->next;
	}

	if (overwrite)
	{
		free(tmp->value);
		tmp->value = _strdup(value);
	}
	else
	{
		alias = malloc(sizeof(alias_t));
		alias->name = _strdup(name);
		alias->value = _strdup(value);
		alias->next = mode_args->alias;
		mode_args->alias = alias;
	}
}

/**
 * print_alias - print alias/es.
 * Description: prints all aliases if flag is set, corresponding alias otherwie
 * @node: struct of `alias_t` (read main.h)
 * @flag: integer
 */
void print_alias(alias_t *node, int flag)
{
	alias_t *head = node;

	if (!flag)
		_dprintf(STDOUT_FILENO, "%s=%s\n", node->name, node->value);
	else
	{
		while (head)
		{
			_dprintf(STDOUT_FILENO, "%s=%s\n", head->name, head->value);
			head = head->next;
		}
	}
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

/**
 * get_alias - get alias by name
 * @name: alias name
 * @mode_args: struct (read main.h)
 *
 * Return: alias value or NULL
 */
char *get_alias(char *name, m_args *mode_args)
{
	alias_t *head = mode_args->alias;

	for (; head; head = head->next)
		if (!_strcmp(name, head->name))
			return (head->value);

	return (0);
}

