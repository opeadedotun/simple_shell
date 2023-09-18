#include "shell.h"

/**
 * is_chain - Function to tesst if char is a chain delimiter
 * @info: variable for the parameter struct
 * @buf: variable for the char buffer
 * @p: variable for the address of position in buf
 *
 * Return: 1 if true and 0 otherwise
 */
int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t a = *p;

	if (buf[a] == '|' && buf[a + 1] == '|')
	{
		buf[a] = 0;
		a++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[a] == '&' && buf[a + 1] == '&')
	{
		buf[a] = 0;
		a++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[a] == ';')
	{
		buf[a] = 0;
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = a;
	return (1);
}

/**
 * check_chain - Function to check if chaining should continue
 * based on the last status
 * @info: variable for the parameter struct
 * @buf: variable for the char buffer
 * @p: variable for the address of position in buffer
 * @i: variable for the stating position in buffer
 * @len: variable for the length of the buffer
 *
 * Return: Void
 */
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t a = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			a = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			a = len;
		}
	}
	*p = a;
}

/**
 * replace_alias - Function to replace an alias
 * @info: Variable for the struct parameter
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias(info_t *info)
{
	int b;
	list_t *str_node;
	char *p;

	for (b = 0; b < 10; b++)
	{
		str_node = node_starts_with(info->alias, info->argv[0], '=');
		if (!str_node)
			return (0);
		free(info->argv[0]);
		p = _strchr(str_node->str, '=');
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * replace_vars - Function that replaces vars in the tokenized string
 * @info: Variable for the struct parameter
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_vars(info_t *info)
{
	int b = 0;
	list_t *str_node;

	for (b = 0; info->argv[b]; b++)
	{
		if (info->argv[b][0] != '$' || !info->argv[b][1])
			continue;
		if (!_strcmp(info->argv[b], "$?"))
		{
			replace_string(&(info->argv[b]),
					_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[b], "$$"))
		{
			replace_string(&(info->argv[b]), _strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		str_node = node_starts_with(info->env, &info->argv[b][1], '=');
		if (str_node)
		{
			replace_string(&(info->argv[b]), _strdup(_strchr(str_node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[b], _strdup(""));
	}
	return (0);
}

/**
 * replace_string - Function that replaces string
 * @old: variable of the old string address
 * @new: variable for the new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
