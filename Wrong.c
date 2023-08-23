#include "shell.h"

/**
 * 2vert - It converts a string to an integer
 * _error - It prints an error
 * @buffer: For modification of string
 * decimal - This function prints a decimal
 * @get: The struct containing parameters
 * @input: the input
 * @wave: Argument
 * @emsg: error message
 * @s: the string to be converted
 * Return: 0 if no numbers, otherwise -1
 * Return: Always 0
 */
int _vert(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;
	for (i = 0;  s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}


void _error(get_t *get, char *emsg)
{
	type(get->fname);
	type(": ");
	decimal(get->line_count, STDERR_FILENO);
	type(": ");
	type(get->argv[0]);
	type(": ");
	type(emsg);
}


int decimal(int display, int file_des)
{
	int (*__types_char)(char) = _types_char;
	int i, num = 0;
	unsigned int _abs_, now;

	if (file_des == STDERR_FILENO)
		__types_char = type_char;
	if (display < 0)
	{
		_abs_ = -display;
		__types_char('-');
		num++;
	}
	else
		_abs_ = display;
	now = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__types_char('0' + now / i);
			num++;
		}
		now %= i;
	}
	__types_char('0' + now);
	num++;

	return (num);
}


char *convert_number(long int num, int base, int wave)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(wave & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	array = wave & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}


void remove_comments(char *buffer)
{
	int i;

	for (i = 0; buffer[i] != '\0'; i++)
		if (buffer[i] == '#' && (!i || buffer[i - 1] == ' '))
		{
			buffer[i] = '\0';
			break;
		}
}

