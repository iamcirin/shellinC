#include "shell.h"

/**
 * **split_str - a function that splits a string into words
 * @st: a pointer to the string
 * @delim: a pointer to the delimeter
 * Return: returns a pointer to an array of strings, or NULL on failure
 */

char **split_str(char *st, char *delim)
{
	int i, j, k, m, wordnum = 0;
	char **s;

	if (st == NULL || st[0] == 0)
		return (NULL);
	if (!delim)
		delim = " ";
	for (i = 0; st[i] != '\0'; i++)
		if (!check_delim(st[i],
		 delim) && (check_delim(st[i + 1], delim) || !st[i + 1]))
			wordnum++;

	if (wordnum == 0)
		return (NULL);
	s = malloc((1 + wordnum) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < wordnum; j++)
	{
		while (check_delim(st[i], delim))
			i++;
		k = 0;
		while (!check_delim(st[i + k], delim) && st[i + k])
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = st[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}
