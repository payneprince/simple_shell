#include "shell.h"

/**
 * clean - Something for the the get_t structure
 * set_get - For the get_t structure
 * @av: argument vector
 * @get: The struct
 * Return: 0
 */
void clean(get_t *get)
{
	get->arg = NULL;
	get->argv = NULL;
	get->path = NULL;
	get->argc = 0;
}


void set_get(get_t *get, char **av)
{
	int i = 0;

	get->fname = av[0];
	if (get->arg)
	{
		get->argv = str_tow(get->arg, " \t");
		if (!get->argv)
		{
			get->argv = malloc(sizeof(char *) * 2);
			if (get->argv)
			{
				get->argv[0] = str_dup(get->arg);
				get->argv[1] = NULL;
			}
		}
		for (i = 0; get->argv && get->argv[i]; i++)
			;
		get->argc = i;

		replace_alias(get);
		replace_vars(get);
	}
}


void free_get(get_t *get, int i)
{
	release(get->argv);
	get->argv = NULL;
	get->path = NULL;
	if (i)
	{
		if (!get->cmd_buf)
			free(get->arg);
		if (get->env)
			free_lst(&(get->env));
		if (get->history)
			free_lst(&(get->history));
		if (get->alias)
			free_lst(&(get->alias));
		release(get->environ);
			get->environ = NULL;
		re((void **)get->cmd_buf);
		if (get->readfd > 2)
			close(get->readfd);
		_types_char(BUFFER_F);
	}
}
