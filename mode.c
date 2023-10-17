#include "main.h"

/**
 * mode - determines the mode (non/interactive)
 * @mode_stat: mode status (1 is terminal - interactive), 0 otherwise
 *
 * Return: pointer to a function - mode hanlder(non/interactive).
 */
void (*mode(int mode_stat))(m_args * mode_args)
{
#if 0
	(void)mode_stat;
	return (interactive);
#endif
	if (mode_stat)
		return (interactive);
	return (non_interactive);
}
