#include "shell.h"

/**
 * get_history_file - Funcntion that gets the history file
 * @info: Variable for parameter struct
 *
 * Return: allocated string containg history file
 */

char *get_history_file(info_t *info)
{
	char *buf, *dir;

	dir = _getenv(info, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);
	return (buf);
}

/**
 * write_history - Functions that creates a file or appends to an existing file
 * @info: Variable for the parameter struct
 *
 * Return: 1 on success, else -1
 */
int write_history(info_t *info)
{
	ssize_t fd;
	char *filename = get_history_file(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_history - Function that reads history from file
 * @info: Variable for the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int read_history(info_t *info)
{
	int a, last = 0, line_count = 0;
	ssize_t fd, rd_len, f_size = 0;
	struct stat st;
	char *buf = NULL, *file_name = get_history_file(info);

	if (!file_name)
		return (0);

	fd = open(file_name, O_RDONLY);
	free(file_name);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		f_size = st.st_size;
	if (f_size < 2)
		return (0);
	buf = malloc(sizeof(char) * (f_size + 1));
	if (!buf)
		return (0);
	rd_len = read(fd, buf, f_size);
	buf[f_size] = 0;
	if (rd_len <= 0)
		return (free(buf), 0);
	close(fd);
	for (a = 0; a < f_size; a++)
		if (buf[a] == '\n')
		{
			buf[a] = 0;
			build_history_list(info, buf + last, line_count++);
			last = a + 1;
		}
	if (last != a)
		build_history_list(info, buf + last, line_count++);
	free(buf);
	info->histcount = line_count;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}

/**
 * build_history_list - Function that adds entry to a history linked list
 * @info: Variable for structure containing potential arguments
 * used to maintain
 * @buf: Variable for buffer
 * @linecount: Variable for the history linecount, histcount
 *
 * Return: Always 0
 */
int build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_node_end(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * renumber_history - Function that renumbers the history
 * linked list after changes
 * @info: Variable for structure containing potential arguments
 * used to maintain
 *
 * Return: the new histcount
 */
int renumber_history(info_t *info)
{
	list_t *node = info->history;
	int a = 0;

	while (node)
	{
		node->num = a++;
		node = node->next;
	}
	return (info->histcount = a);
}

