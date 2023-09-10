/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Niklas Neronin <niklas.neronin@gmail.com>
 */

#include "libft.h"

int	ft_strchrlen(const char *str, int c)
{
	int	x;

	x = 0;
	while (*str && *str != c)
	{
		str++;
		x++;
	}
	if (*str != (char)c)
		return (0);
	return (x);
}
