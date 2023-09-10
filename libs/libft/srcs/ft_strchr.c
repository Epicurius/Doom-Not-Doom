/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Niklas Neronin <niklas.neronin@gmail.com>
 */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	while (*str && *str != c)
		str++;
	if (*str != (char)c)
		return (0);
	return ((char *)str);
}
