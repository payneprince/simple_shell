#include "shell.h"

/**
 * input_buf - This is a buffer chain command
 * get_input - It gets a line without new line
 * _getline - Itgets the next line
 * @get: parameter struct
 * @buffer: The address
 * @len: address of len
 *
 * Return: Always 0
 * Return: s
 */
ssize_t input_buf(get_t *get, char **buffer, size_t *len)
{
	ssize_t riz = 0;
	size_t len_p = 0;

	if (!*len)
	{

		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		riz = getline(buffer, &len_p, stdin);
#else
		riz = _getline(get, buffer, &len_p);
#endif
		if (riz > 0)
		{
			if ((*buffer)[riz - 1] == '\n')
			{
				(*buffer)[riz - 1] = '\0';
				riz--;
			}
			get->linecount_flag = 1;
			remove_comments(*buffer);
			build_history_lst(get, *buffer, get->histcount++);
			{
				*len = riz;
				get->cmd_buf = buffer;
			}
		}
	}
	return (riz);
}


ssize_t get_input(get_t *get)
{
	static char *buffer;
	static size_t i, j, len;
	ssize_t riz = 0;
	char **buf_p = &(get->arg), *ptr;

	_types_char(BUFFER_F);
	riz = input_buf(get, &buffer, &len);
	if (riz == -1)
		return (-1);
	if (len)
	{
		j = i;
		ptr = buffer + i;
		check_chain(get, buffer, &j, i, len);
		while (j < len)
		{
			if (is_chain(get, buffer, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			get->cmd_buf_type = CMD_NORM;
		}

		*buf_p = ptr;
		return (str_len(ptr));
	}

	*buf_p = buffer;
	return (riz);
}

ssize_t read_buf(get_t *get, char *buffer, size_t *i)
{
	ssize_t riz = 0;

	if (*i)
		return (0);
	riz = read(get->readfd, buffer, READ_BUF_SIZE);
	if (riz >= 0)
		*i = riz;
	return (riz);
}


int _getline(get_t *get, char **ptr, size_t *length)
{
	static char buffer[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t riz = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	riz = read_buf(get, buffer, &len);
	if (riz == -1 || (riz == 0 && len == 0))
		return (-1);

	c = _strchr(buffer + i, '\n');
	k = c ? 1 + (unsigned int)(c - buffer) : len;
	new_p = move(p, s, s ? s + k : k + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);

	if (s)
		strn_cat(new_p, buffer + i, k - i);
	else
		_strncpy(new_p, buffer + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}


void sigintHandler(__attribute__((unused))int sig_num)
{
	_types("\n");
	_types("$ ");
	_types_char(BUFFER_F);
}

