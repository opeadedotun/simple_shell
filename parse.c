#include "shell.h"

/**
 * is_cmd - Function that determines if a file is an executable
 * @info: Variable for the info struct
 * @path: Variable for  the path to the file
 *
 * Return: Returns 1 if true and 0 otherwise
 */
int is_cmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - Function that duplicates chars
 * @pathstr: Variable for the PATH string
 * @start: Variable for starting index
 * @stop: Variable for stopping index
 *
 * Return: Return the pointer to the new buffer
*/
char *dup_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int a = 0, b = 0;

	for (b = 0, a = start; a < stop; a++)
		if (pathstr[a] != ':')
			buf[b++] = pathstr[a];
	buf[b] = 0;
	return (buf);
}

/**
 * find_path - Function that finds cmd in the PATH
 * @info: Variable for the info struct
 * @pathstr: Variable for the PATH string
 * @cmd: Variable for the cmd to find
 *
 * Return: Return the full path of cmd
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int a = 0, current_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[a] || pathstr[a] == ':')
		{
			path = dup_chars(pathstr, current_pos, a);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(info, path))
				return (path);
			if (!pathstr[a])
				break;
			current_pos = a;
		}
		a++;
	}
	return (NULL);
}
