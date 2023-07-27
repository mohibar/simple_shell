#include <stdio.h>
#include "shell.h"

/**
 * _myenv - print all the current environment
 * @info: structures containing potential argument use to maintain
 * constant function prototype.
 *
 * Return: Always 0
 */

int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (NULL);
}

/**
 * _getenv - get the value of environ variable in argutmen
 * @info: structure containing potential arguments use to maintain
 * @name: envron var name
 *
 * Return: the value
 */

char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - initialize new environment var
 * and modify an existing one
 * @info: structure containing potential argument use to maintain
 * constant function prototype
 *
 *  Return: Always 0
 */

int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("there's incorrect no. of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - remove an environment variable
 * @info: structure containing potential argument use to maintain
 * constant function prototype
 *
 *  Return: Always 0
 */

int _myunsetenv(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_eputs("there are few arguement in it.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		_unsetenv(info, info->argv[i]);

	return (0);
}

/**
 * populate_env_list - populates env link_list
 * @info: structure containing potential argument use to maintain
 * constant function prototype
 *
 * Return: Always 0
 */

int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	info->env = node;
	return (NULL);
}
