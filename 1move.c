#include "shell.h"

/**
 * move - moves the memory
 * @pointer: pointer to block
 * @prev: byte previous block
 * @new: byte of new block
 *
 * Return: pointer of block
 */
void *move(void *pointer, unsigned int prev, unsigned int new)
{
	char *i;

	if (!pointer)
		return (malloc(new));
	if (!new)
		return (free(pointer), NULL);
	if (new == prev)
		return (pointer);

	i = malloc(new);
	if (!i)
		return (NULL);

	prev = prev < new ? prev : new;
	while (prev--)
		i[prev] = ((char *)pointer)[prev];
	free(pointer);
	return (i);
}

