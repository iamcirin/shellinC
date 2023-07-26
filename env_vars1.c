#include "shell.h"

/**
 * get_environ - a function that returns the string array copy
 * @data_list: a struct of members
 * Return: returns 0
 */
char **get_environ(info_t *data_list)
{
	if (!data_list->environ || data_list->env_changed)
	{
		data_list->environ = list_to_strings(data_list->env);
		data_list->env_changed = 0;
	}

	return (data_list->environ);
}

/**
 * _unsetenv - a function that remove an environment variable
 * @data_list: a struct data_list containing potential argument
 * @str: a pointer to string
 *  Return: returns 1 or
 */
int _unsetenv(info_t *data_list, char *str)
{
	list_t *node = data_list->env;
	size_t n = 0;
	char *ptr;

	if (!node || !str)
		return (0);

	while (node)
	{
		ptr = string_starts_with(node->str, str);
		if (ptr && *ptr == '=')
		{
			data_list->env_changed = delete_node_at_index(&(data_list->env), n);
			n = 0;
			node = data_list->env;
			continue;
		}
		node = node->next;
		n++;
	}
	return (data_list->env_changed);
}

/**
 * _setenv - a function that initialize a new environment variable
 * @data_list: struct data_list
 * @str: a pointer to sytring
 * @value: a pointer to string
 *  Return: retruns 0
 */
int _setenv(info_t *data_list, char *str, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *ptr;

	if (!str || !value)
		return (0);

	buf = malloc(string_len(str) + string_len(value) + 2);
	if (!buf)
		return (1);
	string_cpy(buf, str);
	string_concat(buf, "=");
	string_concat(buf, value);
	node = data_list->env;
	while (node)
	{
		ptr = string_starts_with(node->str, str);
		if (ptr && *ptr == '=')
		{
			free(node->str);
			node->str = buf;
			data_list->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(data_list->env), buf, 0);
	free(buf);
	data_list->env_changed = 1;
	return (0);
}
