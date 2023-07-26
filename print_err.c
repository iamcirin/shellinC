#include "shell.h"

/**
 *err_puts - a function that prints err
 * @s: the string to be printed
 */
void err_puts(char *s)
{
	int i = 0;

	if (!s)
		return;
	while (s[i] != '\0')
	{
		error_putchar(s[i]);
		i++;
	}
}

/**
 * error_putchar - a function that writes the char c to stderr
 * @c: The character to print
 * Return: returns 1 or -1.
 */
int error_putchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * _putfd - a function that writes the character c to given fd
 * @c: The character to print
 * @fd: The filedescriptor to write to
 * Return: returns on success 1.
 */
int _putfd(char c, int fd)
{
	static int i;
	static char buf[1024];

	if (c == (-1) || i >= 1024)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != (-1))
		buf[i++] = c;
	return (1);
}

/**
 *_putsfd - a function that prints an input string
 * @st: the sting to be printed
 * @filedesc: the file descriptor to write to
 * Return: returns the number of chars put
 */
int _putsfd(char *st, int filedesc)
{
	int i = 0;

	if (!st)
		return (0);
	while (*st)
	{
		i += _putfd(*st++, filedesc);
	}
	return (i);
}

