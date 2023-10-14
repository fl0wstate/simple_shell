#include "main.h"

/**
 * mode - determines the mode (non/interactive)
 * @fd: mode status (1 is terminal - interactive), 0 otherwise
 *
 * Return: pointer to a function - mode hanlder(non/interactive).
 */
void (*mode(int mode_stat))(m_args * mode_args)
{
	if (mode_stat)
		return (interactive);
	return (non_interactive);
}
