#include "shell.h"

/**
 * cp - Means duplicate characters
 * @pathstr: The string path
 * @start: Starting
 * @stop: stopping
 *
 * Return: The pointer to new reload
 */
char *cp(char *pathstr, int start, int stop)
{
	static char buffer[1024];
	int i = 0;
int j = 0;

	for (j = 0, i = start; i < stop; i++)
		if (pathstr[i] != ':')
			buffer[j++] = pathstr[i];
	buffer[j] = 0;
	return (buffer);
}

