#include "shell.h"

/**
 * _myhistory - Function that displays the history list
 * @info: VAriable for structure containing potential arguments
 *
 * Return: 0
 */
int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - Function that sets alias to string
 * @info: Variable for parameter struct
 * @str: Variable for the string alias
 *
 * Return: 0 on success, 1 on failure
 */
int unset_alias(info_t *info, char *str)
{
	char *p, f;
	int ret_int;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	f = *p;
	*p = 0;
	ret_int = delete_node_at_index(&(info->alias),
			get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*p = f;
	return (ret_int);
}

/**
 * set_alias - Function that sets alias to string
 * @info: Variable for parameter struct
 * @str: VAriable for the string alias
 *
 * Return: 0 on success, 1 on error
 */
int set_alias(info_t *info, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - Function that prints an alias string
 * @node: Variable for te alias node
 *
 * Return: 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - Function that mimics the bultin alias
 * @info: Variable for structure containing argumetns
 *
 * Return: 0
 */
int _myalias(info_t *info)
{
	int a = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (a = 1; info->argv[a]; a++)
	{
		p = _strchr(info->argv[a], '=');
		if (p)
			set_alias(info, info->argv[a]);
		else
			print_alias(node_starts_with(info->alias, info->argv[a], '='));
	}

	return (0);
}
