#include "shell.h"

/**
 * input_buf - Function for  buffers chained commands
 * @info: Variable for parameter struct
 * @buf: Variable for address of buffer
 * @len: Variable for address of len var
 *
 * Return: bytes read
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t f = 0;
	size_t length_p = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
		f = getline(buf, &length_p, stdin);
		f = _getline(info, buf, &length_p);
		if (f > 0)
		{
			if ((*buf)[f - 1] == '\n')
			{
				(*buf)[f - 1] = '\0';
				f--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			if (_strchr(*buf, ';'))
			{
				*len = f;
				info->cmd_buf = buf;
			}
		}
	}
	return (f);
}

/**
 * get_input - function that gets a line minus the newline
 * @info: Variable for parameter struct
 *
 * Return: bytes read
 */
ssize_t get_input(info_t *info)
{
	static char *buf;
	static size_t a, b, length;
	ssize_t c = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	c = input_buf(info, &buf, &length);
	if (c == -1)
		return (-1);
	if (length)
	{
		b = a;
		p = buf + a;

		check_chain(info, buf, &b, a, length);
		while (b < length)
		{
			if (is_chain(info, buf, &b))
				break;
			b++;
		}

		a = b + 1;
		if (a >= length)
		{
			a = length = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p;
		return (_strlen(p));
	}

	*buf_p = buf;
	return (c);
}

/**
 * read_buf - Function that reads a buffer
 * @info: Variable for parameter struct
 * @buf: Variable for buffer
 * @i: Variable for size
 *
 * Return: c
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t c = 0;

	if (*i)
		return (0);
	c = read(info->readfd, buf, READ_BUF_SIZE);
	if (c >= 0)
		*i = c;
	return (c);
}

/**
 * _getline - Function that gets the next line of input from STDIN
 * @info: Variable for parameter struct
 * @ptr: Variable for address of pointer to buffer, preallocated or NULL
 * @length: Variable for size of preallocated ptr buffer if not NULL
 *
 * Return: e
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t a, len;
	size_t b;
	ssize_t d = 0, e = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		e = *length;
	if (a == len)
		a = len = 0;

	d = read_buf(info, buf, &len);
	if (d == -1 || (d == 0 && len == 0))
		return (-1);

	c = _strchr(buf + a, '\n');
	b = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, e, e ? e + b : b + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);

	if (e)
		_strncat(new_p, buf + a, b - a);
	else
		_strncpy(new_p, buf + a, b - a + 1);

	e += b - a;
	a = b;
	p = new_p;

	if (length)
		*length = e;
	*ptr = p;
	return (e);
}

/**
 * sigintHandler - Function that blocks ctrl-C
 * @sig_num: Variable for the signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
