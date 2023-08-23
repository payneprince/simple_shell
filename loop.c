#include "shell.h"

/**
 * big - For the main shell loop
 * @get: This is the struct
 * @av: the argument vector from main
 *
 * Return: 0 on success, 1 on error
 */
int big(get_t *get, char **av)
{
	ssize_t imma = 0;
	int symbol = 0;

	while (imma != -1 && symbol != -2)
	{
		clean(get);
		if (is_interactive(get))
			_types("$ ");
		type_char(BUFFER_F);
		imma = get_input(get);
		if (imma != -1)
		{
			set_get(get, av);
			symbol = _symbol(get);
			if (symbol == -1)
				find_cmd(get);
		}
		else if (is_interactive(get))
			_type_char('\n');
		free_get(get, 0);
	}
	write_history(get);
	free_get(get, 1);
	if (!is_interactive(get) && get->status)
		exit(get->status);
	if (symbol == -2)
	{
		if (get->err_num == -1)
			exit(get->status);
		exit(get->err_num);
	}
	return (symbol);
}


int _symbol(get_t *get)
{
	int i;
	int use_symbol = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (str_cmp(get->argv[0], builtintbl[i].type) == 0)
		{
			get->line_count++;
			use_symbol = builtintbl[i].func(get);
			break;
		}
	return (use_symbol);
}


void find_cmd(get_t *get)
{
	char *path = NULL;
	int i;
	int a;

	get->path = get->argv[0];
	if (get->linecount_flag == 1)
	{
		get->line_count++;
		get->linecount_flag = 0;
	}
	for (i = 0, a = 0; get->arg[i]; i++)
		if (!bound(get->arg[i], " \t\n"))
			a++;
	if (!a)
		return;

	path = serch(get, _getenv(get, "PATH="), get->argv[0]);
	if (path)
	{
		get->path = path;
		fork_cmd(get);
	}
	else
	{
		if ((is_interactive(get) || _getenv(get, "PATH=")
					|| get->argv[0][0] == '/') && exe_c(get, get->argv[0]))
			fork_cmd(get);
		else if (*(get->arg) != '\n')
		{
			get->status = 127;
			_error(get, "not found\n");
		}
	}
}


void fork_cmd(get_t *get)
{
	pid_t baby_pid;

	baby_pid = fork();
	if (baby_pid == -1)
	{

		perror("Error:");
		return;
	}
	if (baby_pid == 0)
	{
		if (execve(get->path, get->argv, get_environ(get)) == -1)
		{
			free_get(get, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}

	}
	else
	{
		wait(&(get->status));
		if (WIFEXITED(get->status))
		{
			get->status = WEXITSTATUS(get->status);
			if (get->status == 126)
				_error(get, "Permission denied\n");
		}
	}
}

