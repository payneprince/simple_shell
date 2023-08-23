#include "shell.h"

/**
 * get_environ - returns the string array copy of our environ
 * _setenv - First environment variable
 * _unsetenv - It removes variables from environment
 * @brick: The string of the environment
 * @get: The structure containing arguments
 * Return: Always 0
 */
char **get_environ(get_t *get)
{
	if (!get->environ || get->env_changed)
	{
		get->environ = string(get->env);
		get->env_changed = 0;
	}

	return (get->environ);
}


int _unsetenv(get_t *get, char *brick)
{
	lst_t *node = get->env;
	size_t i = 0;
	char *ptr;

	if (!node || !brick)
		return (0);

	while (node)
	{
		ptr = begins(node->str, brick);
		if (ptr && *ptr == '=')
		{
			get->env_changed = delete_node_at_index(&(get->env), i);
			i = 0;
			node = get->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (get->env_changed);
}


int _setenv(get_t *get, char *brick, char *value)
{
	char *buffer = NULL;
	lst_t *node;
	char *p;

	if (!brick || !value)
		return (0);

	buffer = malloc(str_len(brick) + str_len(value) + 2);
	if (!buffer)
		return (1);
	str_cpy(buffer, brick);
	str_cat(buffer, "=");
	str_cat(buffer, value);
	node = get->env;
	while (node)
	{
		p = begins(node->str, brick);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buffer;
			get->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(get->env), buffer, 0);
	free(buffer);
	get->env_changed = 1;
	return (0);
}

