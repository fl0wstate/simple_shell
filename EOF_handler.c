#include "main.h"

/**
 * EOF_handler - hanlde EOF
 * @mode_args: struct (check main.h for details)
 */
void EOF_handler(m_args *mode_args)
{
	free_safe(mode_args);
	free_list(*mode_args->list_path);
	free_aliases(mode_args->alias);
	if (mode_args->free)
		free_envcpy(&environ);
	exit(mode_args->_errno);
}
