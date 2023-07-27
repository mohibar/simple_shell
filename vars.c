#include <stdio.h>
#include "shell.h"

/**
 * is_chain - test whetherthe current char in buffer
 * @info: parameter struct
 * @buf: char buffer
 * @p: address for current position in buf
 *
 * Return: 1 if chain delimeter, els 0
 */

int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t n = *p;

	if (buf[n] == '|' && buf[n + 1] == '|')
	{
		buf[n] = 0;
		j++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[n] == '&' && buf[n + 1] == '&')
	{
		buf[j] = 0;
		n++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[n] == ';') /* found end of this command */
	{
		buf[n] = 0; /* replace semicolon with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = n;
	return (1);
}

/**
 * check_chain - check for continue the last status
 * @info: parameter struct
 * @buf: char buffer
 * @p: address for current position in buf
 * @i: start position in buf
 * @len: length of buf
 *
 * Return: Void
 */

void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t n = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			n = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			n = len;
		}
	}

	*p = n;
}

/**
 * replace_alias - replace an aliases in the tokenize
 * @info: parameter struct
 *
 * Return: 1 if replaced, else 0
 */

int replace_alias(info_t *info)
{
	int x;
	list_t *node;
	char *p;

	for (x = 0; i < 10; x++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * replace_vars - replace vars in the tokeniz string
 * @info: parameter struct
 *
 * Return: 1 if replaced, else 0
 */

int replace_vars(info_t *info)
{
	int n = 0;
	list_t *node;

	for (n = 0; info->argv[n]; n++)
	{
		if (info->argv[i][0] != '$' || !info->argv[n][1])
			continue;

		if (!_strcmp(info->argv[n], "$?"))
		{
			replace_string(&(info->argv[i]),
				_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[i], "$$"))
		{
			replace_string(&(info->argv[i]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[i][1], '=');
		if (node)
		{
			replace_string(&(info->argv[i]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[i], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - replace string
 * @old: address for old string
 * @new: new string
 *
 * Return: 1 if replaced, else 0
 */

int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
