#include "shell.h"

/**
 * bfree - Function that frees a pointer and NULLs the address
 * @ptr: Variable for address of the pointer to free
 *
 * Return: Returns 1 if freed, 0 otherwise
 */
int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
