#include "shell.h"

/**
 * hsh - a function thatmain shell loop
 * @data_list: the parameter & return info struct
 * @av: the argument vector from main()
 * Return: return 0 or 1
 */
int hsh(info_t *data_list, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		clear_info(data_list);
		if (inter_func(data_list))
			string_puts("$ ");
		error_putchar(BUF_FLUSH);
		r = get_input(data_list);
		if (r != -1)
		{
			set_info(data_list, av);
			builtin_ret = find_builtin(data_list);
			if (builtin_ret == -1)
				find_cmd(data_list);
		}
		else if (inter_func(data_list))
			_putchar('\n');
		free_info(data_list, 0);
	}
	write_history(data_list);
	free_info(data_list, 1);
	if (!inter_func(data_list) && data_list->status)
		exit(data_list->status);
	if (builtin_ret == -2)
	{
		if (data_list->err_num == -1)
			exit(data_list->status);
		exit(data_list->err_num);
	}
	return (builtin_ret);
}

/**
 * find_builtin - finds a builtin command
 * @data_list: the parameter & return info struct
 * Return: -1 or 0 or 1 or 2
 */
int find_builtin(info_t *data_list)
{
	int i, built_in_ret = -1;
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
		if (string_cmp(data_list->argv[0], builtintbl[i].type) == 0)
		{
			data_list->line_count++;
			built_in_ret = builtintbl[i].func(data_list);
			break;
		}
	return (built_in_ret);
}

/**
 * find_cmd - afunction that finds a command in PATH
 * @data_list: the parameter & return info struct
 */
void find_cmd(info_t *data_list)
{
	char *path = NULL;
	int i, k;

	data_list->path = data_list->argv[0];
	if (data_list->linecount_flag == 1)
	{
		data_list->line_count++;
		data_list->linecount_flag = 0;
	}
	for (i = 0, k = 0; data_list->arg[i]; i++)
		if (!check_delim(data_list->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = find_path(data_list, _getenv(data_list, "PATH="), data_list->argv[0]);
	if (path)
	{
		data_list->path = path;
		fork_cmd(data_list);
	}
	else
	{
		if ((inter_func(data_list) || _getenv(data_list, "PATH=")
			|| data_list->argv[0][0] == '/') && is_cmd(data_list, data_list->argv[0]))
			fork_cmd(data_list);
		else if (*(data_list->arg) != '\n')
		{
			data_list->status = 127;
			error_msg(data_list, "not found\n");
		}
	}
}

/**
 * fork_cmd - a function forks a an exec thread to run cmd
 * @data_list: the parameter & return info struct
 * Return: void
 */
void fork_cmd(info_t *data_list)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(data_list->path, data_list->argv, get_environ(data_list)) == -1)
		{
			free_info(data_list, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(data_list->status));
		if (WIFEXITED(data_list->status))
		{
			data_list->status = WEXITSTATUS(data_list->status);
			if (data_list->status == 126)
				error_msg(data_list, "Permission denied\n");
		}
	}
}

