/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Niklas Neronin <niklas.neronin@gmail.com>
 */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			x;
	unsigned char	*asd;
	unsigned char	*qwe;

	qwe = (unsigned char *)s2;
	asd = (unsigned char *)s1;
	x = 0;
	if (n <= 0)
		return (0);
	while (x < n - 1 && asd[x] && qwe[x])
	{
		if (asd[x] != qwe[x])
			return (asd[x] - qwe[x]);
		x++;
	}
	return (asd[x] - qwe[x]);
}
