#include "shell.h"

/**
 * is_interactive - It checks to see if the shell is interactive
 * @get: This is the struct address
 * @limit: Checking for characters
 * @dim: It checks for the bound of the string
 * @aplha: It looks for alphabetic characters
 * @lim: Analysis characters
 * Return: 1 if true and 0 if false
 * Return: 1 if interactive mode, 0 otherwise
 */
int is_interactive(get_t *get)
{
	return (isatty(STDIN_FILENO) && get->readfd <= 2);
}


int bound(char limit, char *dim)
{
	while (*dim)
		if (*dim++ == limit)
			return (1);
	return (0);
}


int alpha(int lim)
{
	if ((lim >= 'a' && lim <= 'z') || (lim >= 'A' && lim <= 'Z'))
		return (1);
	else
		return (0);
}



int vert(char *s)
{
	int i;
	int tic = 1;
	int wave = 0, display;
	unsigned int result = 0;

	for (i = 0; s[i] != '\0' && wave != 2; i++)
	{
		if (s[i] == '-')
			tic *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			wave = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (wave == 1)
			wave = 2;
	}

	if (tic == -1)
		display = -result;
	else
		display = result;

	return (display);
}

