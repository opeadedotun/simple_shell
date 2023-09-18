#include "shell.h"

/**
 * **strtow - Function that splits a string into words
 * @str: variable for the input string
 * @d: variable for the delimeter string
 *
 * Return: Returns a pointer to an array string, or NULL otherwise
 */
char **strtow(char *str, char *d)
{
	int a, b, c, f, num_words = 0;
	char **e;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (a = 0; str[a] != '\0'; a++)
		if (!is_delim(str[a], d) && (is_delim(str[a + 1], d) || !str[a + 1]))
			num_words++;

	if (num_words == 0)
		return (NULL);
	e = malloc((1 + num_words) * sizeof(char *));
	if (!e)
		return (NULL);
	for (a = 0, b = 0; b < num_words; b++)
	{
		while (is_delim(str[a], d))
			a++;
		c = 0;
		while (!is_delim(str[a + c], d) && str[a + c])
			c++;
		e[b] = malloc((c + 1) * sizeof(char));
		if (!e[b])
		{
			for (c = 0; c < b; c++)
				free(e[c]);
			free(e);
			return (NULL);
		}
		for (f = 0; f < c; f++)
			e[b][f] = str[a++];
		e[b][f] = 0;
	}
	e[b] = NULL;
	return (e);
}

/**
 * **strtow2 - Function that splits a string into words
 * @str: Variable for the input string
 * @d: Variable for the delimiter
 *
 * Return: Return a pointer to a string array, or NULL otherwise
 */
char **strtow2(char *str, char d)
{
	int a, b, c, f, num_words = 0;
	char **e;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (a = 0; str[a] != '\0'; a++)
		if ((str[a] != d && str[a + 1] == d) ||
				(str[a] != d && !str[a + 1]) || str[a + 1] == d)
			num_words++;
	if (num_words == 0)
		return (NULL);
	e = malloc((1 + num_words) * sizeof(char *));
	if (!e)
		return (NULL);
	for (a = 0, b = 0; b < num_words; b++)
	{
		while (str[a] == d && str[a] != d)
			a++;
		c = 0;
		while (str[a + c] != d && str[a + c] && str[a + c] != d)
			c++;
		e[b] = malloc((c + 1) * sizeof(char));
		if (!e[b])
		{
			for (c = 0; c < b; c++)
				free(e[c]);
			free(e);
			return (NULL);
		}
		for (f = 0; f < c; f++)
			e[b][f] = str[a++];
		e[b][f] = 0;
	}
	e[b] = NULL;
	return (e);
}
