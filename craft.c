#include "shell.h"

/**
 * length - The length of the list
 * string - The strings to return
 * desplay - It displays the elements in the list
 * first_node - Returns Node when prefixed
 * index_node - This gets the index of the node
 * @node: The pointer of list head
 * @prefix: The string to match code
 * @c: The next character of prefix to match
 * @head: This is the pointer to node
 * @h: The pointer to the first node
 *
 * Return: size of list
 * Return: An array of strings
 * Return: The match node or null
 * Return: The index of node or -1(NULL)
 */
size_t length(const lst_t *h)
{
	size_t count = 0;

	while (h)
	{
		h = h->next;
		count++;
	}
	return (count);
}


char **string(lst_t *head)
{
	lst_t *node = head;
	size_t n_node = lst_length(head);
	size_t i;
	size_t j;
	char **pel;
	char *str;

	if (!head || !n_node)
		return (NULL);
	pel = malloc(sizeof(char *) * (n_node + 1));
	if (!pel)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(str_len(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(pel[j]);
			free(pel);
			return (NULL);
		}

		str = str_cpy(str, node->str);
		pel[i] = str;
	}
	pel[n_node] = NULL;
	return (pel);
}


size_t display(const lst_t *h)
{
	size_t count = 0;

	while (h)
	{
		_types(convert_number(h->num, 10, 0));
		_type_char(':');
		_type_char(' ');
		_types(h->str ? h->str : "(nil)");
		_types("\n");
		h = h->next;
		count++;
	}
	return (count);
}


lst_t *first_node(lst_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = begins(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}


ssize_tt index_node(lst_t *head, lst_t *node)
{
	size_t a = 0;

	while (head)
	{
		if (head == node)
			return (a);
		head = head->next;
		a++;
	}
	return (-1);
}

