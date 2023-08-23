#include "shell.h"

/**
 * ceed - to add up the byte
 *release - It releases the pointer
 * @ptr: It is like a string or pointer
 * @pt: Pointer memory
 * @byte: the byte to fill  with
 * @n: the number of bytes to add up
 * Return: (pt) a pointer to the memory
 */
char *ceed(char *pt, char byte, unsigned int num)
{
	unsigned int i;

	for (i = 0; i < num; i++)
		pt[i] = byte;
	return (pt);
}


void release(char **ptr)
{
	char **pttt = ptr;

	if (!ptr)
		return;
	while (*ptr)
		free(*ptr++);
	free(pttt);
}

