#include "shell.h"

/**
 * list_len - a function that determines length of linked list
 * @head: pointer to the head node
 * Return: returns size of list
 */
size_t list_len(const list_t *head)
{
	size_t n = 0;

	while (head)
	{
		head = head->next;
		n++;
	}
	return (n);
}

/**
 * list_to_strings - a function that returns an array
 * @h: a pointer to the head node
 * Return: returns an array of strings
 */
char **list_to_strings(list_t *h)
{
	list_t *node = h;
	size_t i = list_len(h), j;
	char **strs;
	char *str;

	if (!h || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(string_len(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = string_cpy(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}


/**
 * print_list - a function that prints all elements of a list_t linked list
 * @h: pointer to first node
 * Return: returns the size of list
 */
size_t print_list(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		string_puts(convert_to_char(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		string_puts(h->str ? h->str : "(nil)");
		string_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * node_starts_with - a function that returns node
 * @head: pointer to list head
 * @prefixs: string to match
 * @c: the next character after prefix to match
 * Return: match node or null
 */
list_t *node_starts_with(list_t *head, char *prefixs, char c)
{
	char *p = NULL;

	while (head)
	{
		p = string_starts_with(head->str, prefixs);
		if (p && ((c == -1) || (*p == c)))
			return (head);
		head = head->next;
	}
	return (NULL);
}

/**
 * get_node_index - a function that gets the index of a node
 * @h: pointer to list head
 * @node: pointer to the node
 * Return: returns index of node or -1
 */
ssize_t get_node_index(list_t *h, list_t *node)
{
	size_t n = 0;

	while (h)
	{
		if (h == node)
			return (n);
		h = h->next;
		n++;
	}
	return (-1);
}

