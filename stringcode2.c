#include "shell.h"

/**
 * _strlen - Function that returns the length of a string
 * @s: Variable for the string length to check
 *
 * Return: Returns the integer length of string
 */
int _strlen(char *s)
{
	int a = 0;

	if (!s)
		return (0);

	while (*s++)
		a++;
	return (a);
}

/**
 * _strcmp - FUnction that performs lexicogarphic comparison
 * @s1: Variable for the first string
 * @s2: Variable for the second string
 *
 * Return: Returns -1 if s1 < s2, 1 if s1 > s2 and 0 if s1 == s2
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * starts_with - Function to check if neddle starts wirh haystack
 * @haystack: Variable for the string to search
 * @needle: Variable for thr substring to find
 *
 * Return: Returns the address of next char of haystack or NULL
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strcat - Functio to concatenate two strings
 * @dest: Variable for the destination buffer
 * @src: Variable for the source buffer
 *
 * Return: Returns the pointer to destination buffer
 */
char *_strcat(char *dest, char *src)
{
	char *ret_pointer = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret_pointer);
}
