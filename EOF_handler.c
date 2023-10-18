#include "main.h"

/**
 * EOF_handler - hanlde EOF
 * @mode_args: struct (check main.h for details)
 * @list_path: struct (check main.h for details)
 */
void EOF_handler(m_args *mode_args, list_t *list_path)
{
	free_safe(mode_args);
	free_list(list_path);
	if (mode_args->free)
		free_envcpy(&environ);
	exit(mode_args->_errno);
}
