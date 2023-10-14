#include "main.h"

/**
 * mode - determines the mode (non/interactive)
 * @fd: file descriptor
 *
 * Return: pointer to a function - mode hanlder(non/interactive).
 */
void (*mode(int fd))(m_args * mode_args)
{
	if (isatty(fd))
		return (interactive);
	return (non_interactive);
}
