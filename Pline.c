#include "shell.h"

/**
 * str_len - returns the length of a string
 * str_cat - displays the string
 * begins - It begins
 * @pt: the string whose length to check
 *
 * Return: integer length of string
 */
int str_len(char *pt)
{
	int i = 0;

	if (!pt)
		return (0);

	while (*pt++)
		i++;
	return (i);
}


int str_cmp(char *jay, char *kay)
{
	while (*jay && *kay)
	{
		if (*jay != *kay)
			return (*jay - *kay);
		jay++;
		kay++;
	}
	if (*jay == *kay)
		return (0);
	else
		return (*jay < *kay ? -1 : 1);
}


char *begins(const char *run, const char *pin)
{
	while (*pin)
		if (*pin++ != *run++)
			return (NULL);
	return ((char *)run);
}


char *str_cat(char *rubik, char *cube)
{
	char *_rubik = rubik;

	while (*rubik)
		rubik++;
	while (*cube)
		*rubik++ = *cube++;
	*rubik = *cube;
	return (_rubik);
}

