#include "shell.h"

/**
 * _myenv - a function that prints the curr env
 * @data_list: struct containing arguments.
 * Return: returns 0
 */
int _myenv(info_t *data_list)
{
	print_list_str(data_list->env);
	return (0);
}

/**
 * _getenv - a funcrion that gets the value of an env var
 * @data_list: struct containing potential arguments
 * @str: env var string
 * Return: returns the value
 */
char *_getenv(info_t *data_list, const char *str)
{
	list_t *node = data_list->env;
	char *ptr;

	while (node)
	{
		ptr = string_starts_with(node->str, str);
		if (ptr && *ptr)
			return (ptr);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - a function that initialize a new environment variable
 * @data_list: a struct containing potential arguments
 *  Return: returns 0
 */
int _mysetenv(info_t *data_list)
{
	if (data_list->argc != 3)
	{
		err_puts("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(data_list, data_list->argv[1], data_list->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - a function that removes an env var
 * @data_list: a struct containing potential arguments
 *  Return: returns 0
 */
int _myunsetenv(info_t *data_list)
{
	int n;

	if (data_list->argc == 1)
	{
		err_puts("Too few arguements.\n");
		return (1);
	}
	for (n = 1; n <= data_list->argc; n++)
		_unsetenv(data_list, data_list->argv[n]);

	return (0);
}

/**
 * populate_env_list - a function that populates env linked list
 * @data_list: a struct containing arguments
 * Return: returns 0 - success
 */
int populate_env_list(info_t *data_list)
{
	list_t *knot = NULL;
	size_t n;

	for (n = 0; environ[n]; n++)
		add_node_end(&knot, environ[n], 0);
	data_list->env = knot;
	return (0);
}
/*11:55*/
