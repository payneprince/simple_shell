#include "shell.h"

/**
 * re - It releases the pointer
 * @p: The pointer address
 * Return: 1, otherwise 0.
 */
int re(void **p)
{
	if (p && *p)
	{
		free(*p);
		*p = NULL;
		return (1);
	}
	return (0);
}

