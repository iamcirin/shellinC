#include "shell.h"

/**
 * is_cmd -a function that determines if a file is an executable command
 * @data_list: struct fata
 * @path: path to the file
 * Return: returns 1
 */
int is_cmd(info_t *data_list, char *path)
{
	struct stat st;

	(void)data_list;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & __S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - a function that duplicates characters
 * @str: the PATH string
 * @start: starting index
 * @stop: stopping index
 * Return: pointer to new buffer
 */
char *dup_chars(char *str, int start, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (str[i] != ':')
			buf[k++] = str[i];
	buf[k] = 0;
	return (buf);
}

/**
 * find_path - a function that finds this cmd in the PATH string
 * @data_list: struct
 * @str: string Path
 * @cmd: the cmd to find
 * Return: returns full path of cmd if found or NULL
 */
char *find_path(info_t *data_list, char *str, char *cmd)
{
	int i = 0, current = 0;
	char *path;

	if (!str)
		return (NULL);
	if ((string_len(cmd) > 2) && string_starts_with(cmd, "./"))
	{
		if (is_cmd(data_list, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!str[i] || str[i] == ':')
		{
			path = dup_chars(str, current, i);
			if (!*path)
				string_concat(path, cmd);
			else
			{
				string_concat(path, "/");
				string_concat(path, cmd);
			}
			if (is_cmd(data_list, path))
				return (path);
			if (!str[i])
				break;
			current = i;
		}
		i++;
	}
	return (NULL);
}
