#include "shell.h"

/**
 * type - It prints a valued string
 * type_char - It prints a character
 * @str: The string to be printed
 * put_fd - It prints the character c to given file_des
 * _put_fd - prints an input string
 * @file_des: The filedescriptor
 *
 * @c: The character to print
 * Return: NULL or 0
 * Return: On success 1
 */
void type(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		type_char(str[i]);
		i++;
	}
}

int type_char(char c)
{
	static int i;
	static char buffer[WRITE_BUF_SIZE];

	if (c == BUFFER_F || i >= WRITE_BUF_SIZE)
	{
		write(2, buffer, i);
		i = 0;
	}
	if (c != BUFFER_F)
		buffer[i++] = c;
	return (1);
}


int put_fd(char c, int file_des)
{
	static int i;
	static char buffer[WRITE_BUF_SIZE];

	if (c == BUFFER_F || i >= WRITE_BUF_SIZE)
	{
		write(file_des, buffer, i);
		i = 0;
	}
	if (c != BUFFER_F)
		buffer[i++] = c;
	return (1);
}


int _put_fd(char *str, int file_des)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += put_fd(*str++, file_des);
	}
	return (i);
}

