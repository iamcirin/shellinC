#include "shell.h"

/**
 * main - entry point
 * @ac: arg count
 * @av: arg vars
 * Return: returns 0 on success and 1 on error
 */
int main(int ac, char **av)
{
	info_t info[] = { INFO_INIT };
	int filesesc = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (filesesc)
		: "r" (filesesc));

	if (ac == 2)
	{
		filesesc = open(av[1], O_RDONLY);
		if (filesesc == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				err_puts(av[0]);
				err_puts(": 0: Can't open ");
				err_puts(av[1]);
				error_putchar('\n');
				error_putchar(-1);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = filesesc;
	}
	populate_env_list(info);
	read_history(info);
	hsh(info, av);
	return (EXIT_SUCCESS);
}

