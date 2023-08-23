#include "shell.h"

/**
 * **strtow - splits a string into words.
 *  It Repeat i fdelimiters are ignored
 * @wrd: The word of the string
 * @drag: String delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **str_tow(char *wrd, char *drag)
{
	int i;
	int j;
	int k;
	int a;
	int numb = 0;
	char **s;

	if (wrd == NULL || wrd[0] == 0)
		return (NULL);
	if (!drag)
		drag = " ";
	for (i = 0; wrd[i] != '\0'; i++)
		if (!bound(wrd[i], drag) && (bound(wrd[i + 1], drag) || !wrd[i + 1]))
			numb++;

	if (numb == 0)
		return (NULL);
	s = malloc((1 + numb) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numb; j++)
	{
		while (bound(wrd[i], drag))
			i++;
		k = 0;
		while (!bound(wrd[i + k], drag) && wrd[i + k])
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (a = 0; a < k; a++)
			s[j][a] = wrd[i++];
		s[j][a] = 0;
	}
	s[j] = NULL;
	return (s);
}


char **str_tow2(char *wrd, char drag)
{
	int i = 0;
	int j = 0;
	int k = 0;
	int a = 0;
	int numb = 0;
	char **s;

	if (wrd == NULL || wrd[0] == 0)
		return (NULL);
	for (i = 0; wrd[i] != '\0'; i++)
		if ((wrd[i] != drag && wrd[i + 1] == drag) ||
				    (wrd[i] != drag && !wrd[i + 1]) || wrd[i + 1] == drag)
			numb++;
	if (numb == 0)
		return (NULL);
	s = malloc((1 + numb) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numb; j++)
	{
		while (wrd[i] == drag && wrd[i] != drag)
			i++;
		k = 0;
		while (wrd[i + k] != drag && wrd[i + k] && wrd[i + k] != drag)
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (a = 0; a < k; a++)
			s[j][a] = wrd[i++];
		s[j][a] = 0;
	}
	s[j] = NULL;
	return (s);
}

