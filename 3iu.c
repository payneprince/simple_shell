#include "shell.h"

/**
 * serch - It searches for cmd in path
 * @get: struct
 * @pathstr: the PATH string
 * @cmd: The command
 *
 * Return: cmd if found, or NULL
 */
char *serch(get_t *get, char *pathstr, char *cmd)
{
	char *path;
	int i = 0;
	int c = 0;

	if (!pathstr)
		return (NULL);
	if ((str_len(cmd) > 2) && begins(cmd, "./"))
	{
		if (exe_c(get, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = cp(pathstr, c, i);
			if (!*path)
				str_cat(path, cmd);
			else
			{
				str_cat(path, "/");
				str_cat(path, cmd);
			}
			if (exe_c(get, path))
				return (path);
			if (!pathstr[i])
				break;
			c = i;
		}
		i++;
	}
	return (NULL);
}

