#include "shell.h"

/**
 * _myexit - a function that exits the shell
 * @data_list: a struct
 *  Return: return 1 or -1
 */
int _myexit(info_t *data_list)
{
	int check_exit;

	if (data_list->argv[1])
	{
		check_exit = atoi_err(data_list->argv[1]);
		if (check_exit == -1)
		{
			data_list->status = 2;
			error_msg(data_list, "Illegal number: ");
			err_puts(data_list->argv[1]);
			error_putchar('\n');
			return (1);
		}
		data_list->err_num = atoi_err(data_list->argv[1]);
		return (-2);
	}
	data_list->err_num = -1;
	return (-2);
}

/**
 * _mycd - a function that changes the current dir
 * @data_list: a struct
 *  Return: returns 0
 */
int _mycd(info_t *data_list)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		string_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!data_list->argv[1])
	{
		dir = _getenv(data_list, "HOME=");
		if (!dir)
			chdir_ret = /* TODO: what should this be? */
				chdir((dir = _getenv(data_list, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (string_cmp(data_list->argv[1], "-") == 0)
	{
		if (!_getenv(data_list, "OLDPWD="))
		{
			string_puts(s);
			_putchar('\n');
			return (1);
		}
		string_puts(_getenv(data_list, "OLDPWD=")), _putchar('\n');
		chdir_ret = chdir((dir = _getenv(data_list, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(data_list->argv[1]);
	if (chdir_ret == -1)
	{
		error_msg(data_list, "can't cd to ");
		err_puts(data_list->argv[1]), error_putchar('\n');
	}
	else
	{
		_setenv(data_list, "OLDPWD", _getenv(data_list, "PWD="));
		_setenv(data_list, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myhelp -a function that changes the current directory of the process
 * @data_list: a struct containing potential arguments
 *  Return: returns 0
 */
int _myhelp(info_t *data_list)
{
	char **arg_array;

	arg_array = data_list->argv;
	string_puts("help call works. Function not yet implemented \n");
	if (0)
		string_puts(*arg_array);
	return (0);
}
