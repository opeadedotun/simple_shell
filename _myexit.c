#include "shell.h"

/**
 * _myexit - Function for exiting the shell
 * @info: Variable for structure containing potential arguments
 * used to maintain constant function prototype.
 *
 * Return: exits with a given exit status
 * (0) if info.argv[0] != "exit"
 */
int _myexit(info_t *info)
{
int exitcheck;
	if (info->argv[1])
	{
		exitcheck = _erratoi(info->argv[1]);
				if (exitcheck == -1)
				{
					info->status = 2;
					print_error(info, "illegal number:");
					_eputs(info->argv[1]);
					_eputchar('\n');
				return (1);
				}
				info->err_num = _erratoi(info->argv[1]);
				return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _mycd - Function that changes the current directory of the process
 * @info: VAriable to structure containing potential arguments
 * used to maintain constant function prototype.
 *
 * Return: Always 0
 */
int _mycd(info_t *info)
{
	char *e, *dir, buffer[1024];
	int cd_dir_ret;

	e = getcwd(buffer, 1024);
	if (!e)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = _getenv(info, "HOME=");
		if (!dir)
			cd_dir_ret = chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
		else
			cd_dir_ret = chdir(dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(e);
			_putchar('\n');
			return (1);
		}
	_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
	cd_dir_ret = chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
	}
	else
		cd_dir_ret = chdir(info->argv[1]);
	if (cd_dir_ret == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
* _myhelp - Function that changes the current directory of the process
* @info: Variable for structure containing potential arguments
* used to maintain constant function prototype.
*
* Return: ALways 0
*/
int _myhelp(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_puts("help call works. Function not yet implement\n");
	if (0)
	_puts(*arg_array);
	return (0);
}
