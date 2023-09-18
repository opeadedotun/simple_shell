#include "shell.h"

/**
 * _strcpy - Function that copies a string
 * @dest: Variable for the string destination
 * @src: variable for the string source
 *
 * Return: Returns the pointer to its destination
 */
char *_strcpy(char *dest, char *src)
{
	int a = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[a])
	{
		dest[a] = src[a];
		a++;
	}
	dest[a] = 0;
	return (dest);
}

/**
 * _strdup - Function that dupolicates a string
 * @str: Variable for the string to duplicate
 *
 * Return: Returns the pointer to the duplicated string
 */
char *_strdup(const char *str)
{
	int str_len = 0;
	char *ret_pointer;

	if (str == NULL)
		return (NULL);
	while (*str++)
		str_len++;
	ret_pointer = malloc(sizeof(char) * (str_len + 1));
	if (!ret_pointer)
		return (NULL);
	for (str_len++; str_len--;)
		ret_pointer[str_len] = *--str;
	return (ret_pointer);
}

/**
 * _puts - Function that prints an input string
 * @str: Variable for the string to be printed
 *
 * Return: Nothing
 */
void _puts(char *str)
{
	int a = 0;

	if (!str)
		return;
	while (str[a] != '\0')
	{
		_putchar(str[a]);
		a++;
	}
}

/**
 * _putchar - Function that writes charcter c to stdout
 * @c: Variable for the character to print
 *
 * Return: Returns 1 on success, -1 otherwise
 */
int _putchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}
