#include "shell.h"

/**
 * str_cpy - it copies the string
 * @rubik: destination
 * @cube: source
 *
 * Return: Pointer
 */
char *str_cpy(char *rubik, char *cube)
{
	int i = 0;

	if (rubik == cube || cube == 0)
		return (rubik);
	while (cube[i])
	{
		rubik[i] = cube[i];
		i++;
	}
	rubik[i] = 0;
	return (rubik);
}


char *str_dup(const char *ris)
{
	int length = 0;
	char *bac;

	if (ris == NULL)
		return (NULL);
	while (*ris++)
		length++;
	bac = malloc(sizeof(char) * (length + 1));
	if (!bac)
		return (NULL);
	for (length++; length--;)
		bac[length] = *--ris;
	return (bac);
}


void _types(char *strng)
{
	int i = 0;

	if (!strng)
		return;
	while (strng[i] != '\0')
	{
		_types_char(strng[i]);
		i++;
	}
}


int _types_char(char loc)
{
	static int i;
	static char reload[WRITE_BUF_SIZE];

	if (loc == BUFFER_F || i >= WRITE_BUF_SIZE)
	{
		write(1, reload, i);
		i = 0;
	}
	if (loc != BUFFER_F)
		reload[i++] = loc;
	return (1);
}

