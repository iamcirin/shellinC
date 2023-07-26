#include "shell.h"

/**
 **alloc_mem - fills memory with a constant byte
 *@p: a pointer to the memory area
 *@b: a char
 *@n: number of chars
 *Return: returns a pointer to the memory
 */
char *alloc_mem(char *p, char b, unsigned int n)
{
	unsigned int m;

	for (m = 0; m < n; m++)
		p[m] = b;
	return (p);
}

/**
 * free_mem - a function that frees a pointer
 * @ptrptr: a pointer to a pointer
 */
void free_mem(char **ptrptr)
{
	char **a = ptrptr;

	if (!ptrptr)
		return;
	while (*ptrptr)
		free(*ptrptr++);
	free(a);
}

/**
 * mem_realloc - a function that reallocates a block of memory
 * @cla: pointer to previous block
 * @size1: an unsigned int byte size of previous block
 * @size2: an unsigned int  byte size of new block
 * Return: returns a pointer
 */
void *mem_realloc(void *cla, unsigned int size1, unsigned int size2)
{
	char *ptr;

	if (!cla)
		return (malloc(size2));
	if (!size2)
		return (free(cla), NULL);
	if (size2 == size1)
		return (cla);

	ptr = malloc(size2);
	if (!ptr)
		return (NULL);

	size1 = size1 < size2 ? size1 : size2;
	while (size1--)
		ptr[size1] = ((char *)cla)[size1];
	free(cla);
	return (ptr);
}

/**
 * free_add - a function that frees the address
 * @p: a pointer to pointer
 * Return: returns 1 or 0.
 */
int free_add(void **p)
{
	if (p && *p)
	{
		free(*p);
		*p = NULL;
		return (1);
	}
	return (0);
}

