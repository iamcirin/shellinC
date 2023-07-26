#include "shell.h"

/**
 * string_len - a function tha counts the length of a string
 * @str: a pointer to string to count
 * Return: returns an the number of the string
 */
int string_len(char *str)
{
	int n = 0;

	if (!str)
		return (0);

	while (*str != '\0')
		n++;
	return (n);
}

/**
 * string_cmp - a function that compares to string
 * @str1: first param string
 * @str2: second param string
 * Return: returns an int 1, -1 or 0
 */
int string_cmp(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	if (*str1 == *str2)
		return (0);
	else
		return (0);

}

/**
 * string_starts_with - a function to check string
 * @str: a pointer to string to search
 * @prefix: a pointer to the prfix to find
 *
 * Return: returns an address of next char of str or NULL
 */
char *string_starts_with(const char *str, const char *prefix)
{
	while (*prefix != '\0')
		if (*prefix++ != *str++)
			return (NULL);
	return ((char *)str);
}

/**
 * string_concat - a function that concatenates two strings
 * @str_dest: a pointer to the destination buffer
 * @str_src: a pointer to the source buffer
 * Return: returns a pointer to destination buffer
 */
char *string_concat(char *str_dest, char *str_src)
{
	while (*str_dest != '\0')
		str_dest++;
	while (*str_src != '\0')
		*str_dest++ = *str_src++;
	*str_dest = *str_src;

	return (str_dest);
}

