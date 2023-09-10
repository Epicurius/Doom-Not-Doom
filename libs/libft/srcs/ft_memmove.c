/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Niklas Neronin <niklas.neronin@gmail.com>
 */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	char		*tmp;
	const char	*src2;

	tmp = dst;
	src2 = src;
	if (dst > src)
	{
		while (n > 0)
		{
			n--;
			tmp[n] = src2[n];
		}
	}
	else
		ft_memcpy(dst, src, n);
	return (dst);
}
