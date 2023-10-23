#include "main.h"

/**
 * set_logicals - creats an array of logical operators if any ('&&', '||')
 * @mode_args: struct (read main.h)
 *
 * Return: the number of logicals
 */
int set_logicals(m_args *mode_args)
{
	int i, j;

	for (i = 0, j = 0; mode_args->line && (mode_args->line)[i]; i++)
	{
		if ((mode_args->line)[i] == SEPARATOR)
		{
			mode_args->logicals[j++] = SEPARATOR;
			continue;
		}
		if ((mode_args->line)[i] == AND)
		{
			mode_args->logicals[j++] = AND;
			i++;
			continue;
		}
		if ((mode_args->line)[i] == OR)
		{
			mode_args->logicals[j++] = OR;
			i++;
			continue;
		}
	}
	mode_args->logicals[j] = 0;

	return (j);
}
