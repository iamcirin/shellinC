#include "shell.h"

/**
 * is_chain - a function that test if current char in buffer
 * @data_list: astruct
 * @buf: a pointer
 * @ptr: address of current position in buf
 * Return: retuens 1 if chain delimeter, 0 otherwise
 */
int is_chain(info_t *data_list, char *buf, size_t *ptr)
{
	size_t j = *ptr;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		data_list->cmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		data_list->cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';') /* found end of this command */
	{
		buf[j] = 0; /* replace semicolon with null */
		data_list->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*ptr = j;
	return (1);
}

/**
 * check_chain - a function that checks we should continue chaining
 * @data_list: struct
 * @str: the char buffer
 * @ptr: address of current position in buf
 * @i: starting position in buf
 * @len: length of buf
 */
void check_chain(info_t *data_list,
char *str, size_t *ptr, size_t i, size_t len)
{
	size_t j = *ptr;

	if (data_list->cmd_buf_type == CMD_AND)
	{
		if (data_list->status)
		{
			str[i] = 0;
			j = len;
		}
	}
	if (data_list->cmd_buf_type == CMD_OR)
	{
		if (!data_list->status)
		{
			str[i] = 0;
			j = len;
		}
	}

	*ptr = j;
}

/**
 * replace_alias - a function that replaces an aliases in the tokenized string
 * @data_list: the parameter struct
 * Return: returns 1 if replaced, 0 otherwise
 */
int replace_alias(info_t *data_list)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = node_starts_with(data_list->alias, data_list->argv[0], '=');
		if (!node)
			return (0);
		free(data_list->argv[0]);
		p = string_search(node->str, '=');
		if (!p)
			return (0);
		p = string_dup(p + 1);
		if (!p)
			return (0);
		data_list->argv[0] = p;
	}
	return (1);
}

/**
 * replace_vars - replaces vars in the tokenized string
 * @data_list: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_vars(info_t *data_list)
{
	int i = 0;
	list_t *node;

	for (i = 0; data_list->argv[i]; i++)
	{
		if (data_list->argv[i][0] != '$' || !data_list->argv[i][1])
			continue;

		if (!string_cmp(data_list->argv[i], "$?"))
		{
			replace_string(&(data_list->argv[i]),
				string_dup(convert_to_char(data_list->status, 10, 0)));
			continue;
		}
		if (!string_cmp(data_list->argv[i], "$$"))
		{
			replace_string(&(data_list->argv[i]),
				string_dup(convert_to_char(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(data_list->env, &data_list->argv[i][1], '=');
		if (node)
		{
			replace_string(&(data_list->argv[i]),
				string_dup(string_search(node->str, '=') + 1));
			continue;
		}
		replace_string(&data_list->argv[i], string_dup(""));

	}
	return (0);
}

/**
 * replace_string - a function thatreplaces string
 * @old: address of old string
 * @newstr: new string
 * Return: returns 1 if replaced, 0 otherwise
 */
int replace_string(char **old, char *newstr)
{
	free(*old);
	*old = newstr;
	return (1);
}

