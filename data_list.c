#include "shell.h"

/**
 * clear_info - a function that initializes info_t struct
 * @data_list: struct address
 */
void clear_info(info_t *data_list)
{
	data_list->arg = NULL;
	data_list->argv = NULL;
	data_list->path = NULL;
	data_list->argc = 0;
}

/**
 * set_info - initializes info_t struct
 * @data_list: struct address
 * @av: argument vector
 */
void set_info(info_t *data_list, char **av)
{
	int i = 0;

	data_list->fname = av[0];
	if (data_list->arg)
	{
		data_list->argv = (char **)strtok(data_list->arg, " \t");
		if (!data_list->argv)
		{

			data_list->argv = (char **)malloc(sizeof(char *) * 2);
			if (data_list->argv)
			{
				data_list->argv[0] = string_dup(data_list->arg);
				data_list->argv[1] = NULL;
			}
		}
		for (i = 0; data_list->argv && data_list->argv[i]; i++)
			;
		data_list->argc = i;

		replace_alias(data_list);
		replace_vars(data_list);
	}
}

/**
 * free_info - a function that frees info_t struct fields
 * @data_list: struct address
 * @all: true if freeing all fields
 */
void free_info(info_t *data_list, int all)
{
	free_mem(data_list->argv);
	data_list->argv = NULL;
	data_list->path = NULL;
	if (all)
	{
		if (!data_list->cmd_buf)
			free(data_list->arg);
		if (data_list->env)
			free_list(&(data_list->env));
		if (data_list->history)
			free_list(&(data_list->history));
		if (data_list->alias)
			free_list(&(data_list->alias));
		free_mem(data_list->environ);
			data_list->environ = NULL;
		free_add((void **)data_list->cmd_buf);
		if (data_list->readfd > 2)
			close(data_list->readfd);
		_putchar(BUF_FLUSH);
	}
}
