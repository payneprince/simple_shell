#include "shell.h"

/**
 **_strncpy - It copies a string
 *strn_cat - It adds up two string values
 *_strchr - It locates a bunch of strings
 *@rubik: The string to copy
 *@cube: Where to copy from
 *@num: Total values to copy
 *Return: The string
 */
char *_strncpy(char *rubik, char *cube, int num)
{
	int i;
	int j;
	char *s = rubik;

	i = 0;
	while (cube[i] != '\0' && i < num - 1)
	{
		rubik[i] = cube[i];
		i++;
	}
	if (i < num)
	{
		j = i;
		while (j < num)
		{
			rubik[j] = '\0';
			j++;
		}
	}
	return (s);
}

char *strn_cat(char *rubik, char *cube, int num)
{
	int i;
	int j;
	char *s = rubik;

	i = 0;
	j = 0;
	while (rubik[i] != '\0')
		i++;
	while (cube[j] != '\0' && j < num)
	{
		rubik[i] = cube[j];
		i++;
		j++;
	}
	if (j < num)
		rubik[i] = '\0';
	return (s);
}


char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}

