#include "shell.h"

/**
 * _myhistory - It displays the history list
 * _myalais - Works like the 0_2 function
 * 
 * @get: The Structure containing potential arguments
 *  Return: Always 0
 */
int _myhistory(get_t *get)
{
	display(get->history);
	return (0);
}


int unset_alias(get_t *get, char *str)
{
	char *ptr, c;
	int prev;

	ptr = _strchr(str, '=');
	if (!ptr)
		return (1);
	c = *ptr;
	*ptr = 0;
	prev = delete_node_at_index(&(get->alias),
		index_node(get->alias, first_node(get->alias, str, -1)));
	*p = c;
	return (prev);
}


int set_alias(get_t *get, char *str)
{
	char *ptr;

	ptr = _strchr(str, '=');
	if (!ptr)
		return (1);
	if (!*++ptr)
		return (unset_alias(get, str));

	unset_alias(get, str);
	return (add_node_end(&(get->alias), str, 0) == NULL);
}


int print_alias(lst_t *node)
{
	char *ptr = NULL, *c = NULL;

	if (node)
	{
		ptr = _strchr(node->str, '=');
		for (c = node->str; c <= ptr; c++)
		_type_char(*c);
		_types_char('\'');
		_types(ptr + 1);
		_types("'\n");
		return (0);
	}
	return (1);
}


int _myalias(get_t *get)
{
	int i = 0;
	char *ptr = NULL;
	lst_t *node = NULL;

	if (get->argc == 1)
	{
		node = get->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; get->argv[i]; i++)
	{
		ptr = _strchr(get->argv[i], '=');
		if (ptr)
			set_alias(get, get->argv[i]);
		else
			print_alias(first_node(get->alias, get->argv[i], '='));
	}

	return (0);
}

