/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Niklas Neronin <niklas.neronin@gmail.com>
 */

#include "libft.h"

char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t	x;

	x = 0;
	while (x < n && src[x] != '\0')
	{
		dest[x] = src[x];
		++x;
	}
	while (x < n)
	{
		dest[x] = '\0';
		++x;
	}
	return (dest);
}
