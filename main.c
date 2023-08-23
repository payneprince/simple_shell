#include "shell.h"

/**
 * main - enter
 * @ac: For argument count
 * @av: And argument vector
 * Return: 0 on success, 1 on error
 */
int main(int ac, char **av)
{
	get_t get[] = { get_all };
	int file_des = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (file_des)
			: "r" (file_des));

	if (ac == 2)
	{
		file_des = open(av[1], O_RDONLY);
		if (file_des == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				type(av[0]);
				type(": 0: Can not go through ");
				type(av[1]);
				type_char('\n');
				type_char(BUFFER_F);
				exit(126);
			}
			return (EXIT_FAILURE);
		}
		get->readfd = file_des;
	}
	populate_env_list(get);
	read_history(get);
	big(get, av);
	return (EXIT_SUCCESS);
}

