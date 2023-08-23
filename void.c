#include "shell.h"

/**
 * add_node - It adds a node to the start of the list
 * add_node_end - It adds a node to the end of the list
 * print_list_str - It prints string element
 * delete_node_at_index -  It deletes node
 * @head: The head address
 * @h: Pointer to node
 * @str: The string field
 * @num: index used
 *
 * Return: the size of the list
 */
lst_t *add_node(lst_t **head, const char *str, int num)
{
	lst_t *_head;

	if (!head)
		return (NULL);
	_head = malloc(sizeof(lst_t));
	if (!_head)
		return (NULL);
	ceed((void *)_head, 0, sizeof(lst_t));
	_head->num = num;
	if (str)
	{
		_head->str = str_dup(str);
		if (!_head->str)
		{
			free(_head);
			return (NULL);
		}
	}
	_head->next = *head;
	*head = _head;
	return (_head);
}


lst_t *add_node_end(lst_t **head, const char *str, int num)
{
	lst_t *_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	_node = malloc(sizeof(lst_t));
	if (!_node)
		return (NULL);
	ceed((void *)_node, 0, sizeof(lst_t));
	_node->num = num;
	if (str)
	{
		_node->str = str_dup(str);
		if (!_node->str)
		{
			free(_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = _node;
	}
	else
		*head = _node;
	return (_node);
}


size_t print_list_str(const lst_t *h)
{
	size_t i = 0;

	while (h)
	{
		_types(h->str ? h->str : "(nil)");
		_types("\n");
		h = h->next;
		i++;
	}
	return (i);
}


int delete_node_at_index(lst_t **head, unsigned int num)
{
	lst_t *node, *ret;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (!num)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (i == num)
		{
			ret->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		i++;
		ret = node;
		node = node->next;
	}
	return (0);
}


void free_lst(lst_t **head_ptr)
{
	lst_t *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}

