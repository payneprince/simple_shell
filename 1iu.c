#include "shell.h"

/**
 * exe_c - Checks to see if can be executed
 * @get: struct
 * @path: pathway
 *
 * Return: 1, or 0
 */
int exe_c(get_t *get, char *path)
{
	struct stat st;

	(void)get;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

