#include "shell.h"

/**
 * get_history_file - a function that gets the history file
 * @data_list: a struct
 * Return: returns an allocated string
 */

char *get_history_file(info_t *data_list)
{
	char *buf, *dir;

	dir = _getenv(data_list, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (string_len(dir) + string_len(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	string_cpy(buf, dir);
	string_concat(buf, "/");
	string_concat(buf, HIST_FILE);
	return (buf);
}

/**
 * write_history - a function that creates a file
 * @data_list: a struct
 * Return: returns 1 or-1
 */
int write_history(info_t *data_list)
{
	ssize_t filedesc;
	char *name_file = get_history_file(data_list);
	list_t *node = NULL;

	if (!name_file)
		return (-1);

	filedesc = open(name_file, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(name_file);
	if (filedesc == -1)
		return (-1);
	for (node = data_list->history; node; node = node->next)
	{
		_putsfd(node->str, filedesc);
		_putfd('\n', filedesc);
	}
	_putfd(BUF_FLUSH, filedesc);
	close(filedesc);
	return (1);
}

/**
 * read_history - a function that reads history from file
 * @data_list: a struct
 * Return: returns  histcount or 0
 */
int read_history(info_t *data_list)
{
	int i, last = 0, count = 0;
	ssize_t filedesc, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_history_file(data_list);

	if (!filename)
		return (0);

	filedesc = open(filename, O_RDONLY);
	free(filename);
	if (filedesc == -1)
		return (0);
	if (!fstat(filedesc, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(filedesc, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(filedesc);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			build_history_list(data_list, buf + last, count++);
			last = i + 1;
		}
	if (last != i)
		build_history_list(data_list, buf + last, count++);
	free(buf);
	data_list->histcount = count;
	while (data_list->histcount-- >= HIST_MAX)
		delete_node_at_index(&(data_list->history), 0);
	renumber_history(data_list);
	return (data_list->histcount);
}

/**
 * build_history_list - a function that adds entry to a history linked list
 * @data_list: a strunct
 * @str: a pointer to string
 * @count: an int count
 * Return: returns 0
 */
int build_history_list(info_t *data_list, char *str, int count)
{
	list_t *node = NULL;

	if (data_list->history)
		node = data_list->history;
	add_node_end(&node, str, count);

	if (!data_list->history)
		data_list->history = node;
	return (0);
}

/**
 * renumber_history - a function that counts the history
 * @data_list: a struct  containing potential arguments
 * Return: returns the new histcount
 */
int renumber_history(info_t *data_list)
{
	list_t *node = data_list->history;
	int n = 0;

	while (node)
	{
		node->num = n++;
		node = node->next;
	}
	return (data_list->histcount = n);
}
