#include "shell.h"

/**
 * *_memset - Function that fills the memory with a const type
 * @s: Variable pointer to the memory area
 * @b: Variable for the byte to fill *s
 * @n: Variable fo rthe amount of bytes to be filled
 *
 * Return: Returns a pointer to the memory 2
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int m;

	for (m = 0; m < n; m++)
		s[m] = b;
	return (s);
}

/**
 * ffree - Function that frees a string
 * @pp: Variable for string
 */
void ffree(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}

/**
 * _realloc - Function the reallocates a block of memory
 * @ptr: Variable pointer to previous malloc block
 * @old_size: Variable for byte size of previous block
 * @new_size: Variable for byte size of new block
 *
 * Return: Return the pointer to the old block
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}
