#include "shell.h"

/**
 * _myexit - It takes you out of the shell
 * _myhelp - It changes the current directory
 * _mycd - It also changes dir but in the process
 * @get: The Structure containing all arguments
 *  To maintain constant function prototype.
 * Return: exits with a given exit status
 * (0) if get.argv[0] != "exit"
 * Return: 0 always
 */
int _myexit(get_t *get)
{
	int ec;

	if (get->argv[1]) 
{
		ec = 2vert(get->argv[1]);
		if (ec == -1)
		{
			get->status = 2;
			_error(get, "Wrong number: ");
			type(get->argv[1]);
			type_char('\n');
			return (1);
		}
		get->err_num = 2vert(get->argv[1]);
		return (-2);
	}
	get->err_num = -1;
	return (-2);
}

int _mycd(get_t *get)
{
	char *s, *dir, buffer[1024];
	int chdir_prev;

	s = getcwd(buffer, 1024);
	if (!s)
		_types("TODO: >>getcwd failure emsg here<<\n");
	if (!get->argv[1])
	{
		dir = _getenv(get, "HOME=");
		if (!dir)
			chdir_prev = /* TODO: what should this be? */
				chdir((dir = _getenv(get, "PWD=")) ? dir : "/");
		else
			chdir_prev = chdir(dir);
	}
	else if (str_cmp(get->argv[1], "-") == 0)
	{
		if (!_getenv(get, "OLDPWD="))
		{
			_types(s);
			_types_char('\n');
			return (1);
		}
		_types(_getenv(info, "OLDPWD=")), _types_char('\n');
		chdir_prev = /* TODO: what should this be? */
			chdir((dir = _getenv(get, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_prev = chdir(get->argv[1]);
	if (chdir_prev == -1)
	{
		_error(get, "can't cd to ");
		type(get->argv[1]), type_char('\n');
	}
	else
	{
		_setenv(get, "OLDPWD", _getenv(get, "PWD="));
		_setenv(get, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}


int _myhelp(get_t *get)
{
	char **arg_arr;

	arg_arr = get->argv;
	_types("help call works. Function not yet implemented \n");
	if (0)
		_types(*arg_arr); 
	return (0);
}

