#include "shell.h"

/**
 * _myenv - prints the current environment
 * _getenv - It fetches input from environment
 * @get: The Structure containing potential arguments
 * @set: Name for ev
 * Return: Always 0
 */
int _myenv(get_t *get)
{
	print_list_str(get->env);
	return (0);
}


char *_getenv(get_t *get, const char *set)
{
	lst_t *node = get->env;
	char *ptr;

	while (node)
	{
		ptr = begins (node->str, set);
		if (ptr && *ptr)
			return (ptr);
		node = node->next;
	}
	return (NULL);
}

int _mysetenv(get_t *get)
{
	if (get->argc != 3)
	{
		type("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(get, get->argv[1], get->argv[2]))
		return (0);
	return (1);
}

int _myunsetenv(get_t *get)
{
	int i;

	if (get->argc == 1)
	{
		type("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= get->argc; i++)
		_unsetenv(get, get->argv[i]);

	return (0);
}


int populate_env_list(get_t *get)
{
	lst_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	get->env = node;
	return (0);
}

