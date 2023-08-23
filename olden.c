#include "shell.h"

/**
 * get_history_file - It gets the history file
 * renumber_history - It renumbers the history list
 * build_history_lst - It adds up to the history list
 * write_history - It creates a file or appends to an existing file
 * read_history - It reads history of a file
 * @get: The parameter struct
 *
 * Return: String containing history file
 * Return: 1 on success, else -1
 */

char *get_history_file(get_t *get)
{
	char *buffer, *rep;

	rep = _getenv(get, "HOME=");
	if (!rep)
		return (NULL);
	buffer = malloc(sizeof(char) * (str_len(rep) + str_len(HIST_FILE) + 2));
	if (!buffer)
		return (NULL);
	buffer[0] = 0;
	str_cpy(buffer, rep);
	str_cat(buffer, "/");
	str_cat(buffer, HIST_FILE);
	return (buffer);
}

int write_history(get_t *get)
{
	ssize_t file_des;
	char *file_name = get_history_file(get);
	lst_t *node = NULL;

	if (!file_name)
		return (-1);

	file_des = open(file_name, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(file_name);
	if (file_des == -1)
		return (-1);
	for (node = get->history; node; node = node->next)
	{
		_put_fd(node->str, file_des);
		put_fd('\n', file_des);
	}
	put_fd(BUFFER_F, file_des);
	close(file_des);
	return (1);
}


int read_history(get_t *get)
{
	int i, buttom = 0, tot_num = 0;
	ssize_t file_des, rdlen, fsize = 0;
	struct stat st;
	char *buffer = NULL, *file_name = get_history_file(get);

	if (!file_name)
		return (0);

	file_des = open(file_name, O_RDONLY);
	free(file_name);
	if (file_des == -1)
		return (0);
	if (!fstat(file_des, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buffer = malloc(sizeof(char) * (fsize + 1));
	if (!buffer)
		return (0);
	rdlen = read(file_des, buffer, fsize);
	buffer[fsize] = 0;
	if (rdlen <= 0)
		return (free(buffer), 0);
	close(file_des);
	for (i = 0; i < fsize; i++)
		if (buffer[i] == '\n')
		{
			buffer[i] = 0;
			build_history_lst(get, buffer + buttom, tot_num++);
			buttom = i + 1;
		}
	if (buttom != i)
		build_history_lst(get, buffer + buttom, tot_num++);
	free(buffer);
	get->histcount = tot_num;
	while (get->histcount-- >= HIST_MAX)
		delete_node_at_index(&(get->history), 0);
	renumber_history(get);
	return (get->histcount);
}


int build_history_lst(get_t *get, char *buffer, int tot_num)
{
	lst_t *node = NULL;

	if (get->history)
		node = get->history;
	add_node_end(&node, buffer, tot_num);

	if (!get->history)
		get->history = node;
	return (0);
}


int renumber_history(get_t *get)
{
	lst_t *node = get->history;
	int kik = 0;

	while (node)
	{
		node->num = kik++;
		node = node->next;
	}
	return (get->histcount = kik);
}

