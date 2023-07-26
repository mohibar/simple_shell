#include <stdio.h>
#include "shell.h"

/**
 * interactive - return is shell is interactive
 * true
 * @info: addresses
 *
 * Return: 1 for interactive mode, else 0
 */

int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - check all the characters for delimeter
 * @c: check char
 * @delim: string
 *
 * Return: 1 for true, else 0 for false
 */

int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 * _isalpha - check alphabetic char
 * @c: input char
 * Return: 1 for alphabetic, else 0
 */

int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - convert all string
 * @s: the string
 * Return: 0 for numbers
 */

int _atoi(char *s)
{
	int i = 0;
	int sign = 1;
	int flag = 0;
	int output = 0;
	unsigned int result = 0;

	for (i = 0; s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
