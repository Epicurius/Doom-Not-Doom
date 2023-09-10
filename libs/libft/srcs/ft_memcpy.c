/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Niklas Neronin <niklas.neronin@gmail.com>
 */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t		x;
	char		*str;
	const char	*source;

	str = dst;
	source = src;
	x = 0;
	if (!n || str == source)
		return (dst);
	while (x < n)
	{
		str[x] = source[x];
		x++;
	}
	return (dst);
}
