#include "main.h"

/**
 * alias_builtin - alias builtin command handler
 * @mode_args: struct (read main.h)
 */
void alias_builtin(m_args *mode_args)
{
	int i = 0;
	char *name, *value;
	alias_t *tmp = mode_args->alias;

	if (!mode_args->tokens[i + 1])
	{
		/*TODO: print list of aliases if any */
		print_alias(tmp, 1);
		return;
	}
	while (mode_args->tokens[++i])
	{
		name = _strtok(mode_args->tokens[i], "=");
		value = _strtok(0, "=");
		if (!value)
		{
			for (tmp = mode_args->alias; tmp; tmp = (tmp)->next)
				if (!_strcmp((tmp)->name, name))
				{
					/*TODO: print that alias */
					print_alias(tmp, 0);
					break;
				}
		}
		else
			mutate_aliases(name, value, mode_args);
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
	alias_t *tmp = mode_args->alias;

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
	else /* append alias */
		append_alias(&mode_args->alias, name, value);
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
		_dprintf(STDOUT_FILENO, "%s='%s'\n", node->name, node->value);
	else
	{
		while (head)
		{
			_dprintf(STDOUT_FILENO, "%s='%s'\n", head->name, head->value);
			head = head->next;
		}
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
	char *old_name = 0;
	char *new_name = 0;

	for (; head; head = head->next)
		if (!_strcmp(name, head->name))
		{
			old_name = head->value;
			break;
		}

	new_name = (_get_alias(old_name, mode_args));

	if (!new_name)
		return (old_name);
	return (new_name);
}

/**
 * _get_alias - search for aliasing recursively
 * @name: alias name
 * @mode_args: struct (read main.h)
 *
 * Return: alias value or NULL
 */
char *_get_alias(char *name, m_args *mode_args)
{
	alias_t *head = mode_args->alias;
	char *old_name = name;

	if (!old_name)
		return (0);

	for (; head; head = head->next)
		if (!_strcmp(name, head->name))
			old_name = _get_alias(head->value, mode_args);
	return (old_name);
}

