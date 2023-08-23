#include "shell.h"

/**
 * is_chain -It  test if current char in buffer is a chain delimeter
 * @get: the parameter struct
 * @buffer: Stands for buffer
 * @p: The  address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */

int is_chain(get_t *get, char *buffer, size_t *p)
{
	size_t j = *p;

	if (buffer[j] == '|' && buffer[j + 1] == '|')
	{
		buffer[j] = 0;
		j++;
		get->cmd_buf_type = CMD_OR;
	}
	else if (buffer[j] == '&' && buffer[j + 1] == '&')
	{
		buffer[j] = 0;
		j++;
		get->cmd_buf_type = CMD_AND;
	}
	else if (buffer[j] == ';')
	{
		buffer[j] = 0;
		get->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}


void check_chain(get_t *get, char *buffer, size_t *ptr, size_t i, size_t num)
{
	size_t p = *ptr;

	if (get->cmd_buf_type == CMD_AND)
	{
		if (get->status)
		{
			buffer[i] = 0;
			p = num;
		}
	}
	if (get->cmd_buf_type == CMD_OR)
	{
		if (!get->status)
		{
			buffer[i] = 0;
			p = num;
		}
	}

	*ptr = p;
}

int replace_alias(get_t *get)
{
	int i;
	lst_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = first_node(get->alias, get->argv[0], '=');
		if (!node)
			return (0);
		free(get->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = str_dup(p + 1);
		if (!p)
			return (0);
		get->argv[0] = p;
	}
	return (1);
}


int replace_vars(get_t *get)
{
	int i = 0;
	lst_t *node;

	for (i = 0; get->argv[i]; i++)
	{
		if (get->argv[i][0] != '$' || !get->argv[i][1])
			continue;

		if (!str_cmp(get->argv[i], "$?"))
		{
			replace_string(&(get->argv[i]),
					str_dup(convert_number(get->status, 10, 0)));
			continue;
		}
		if (!str_cmp(get->argv[i], "$$"))
		{
			replace_string(&(get->argv[i]),
					str_dup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = first_node(get->env, &get->argv[i][1], '=');
		if (node)
		{
			replace_string(&(get->argv[i]),
					str_dup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&get->argv[i], str_dup(""));

	}
	return (0);
}


int replace_string(char **prev, char *new)
{
	free(*prev);
	*prev = new;
	return (1);
}

