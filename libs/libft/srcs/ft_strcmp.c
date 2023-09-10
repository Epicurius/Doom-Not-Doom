/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Niklas Neronin <niklas.neronin@gmail.com>
 */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int				x;
	unsigned char	*asd;
	unsigned char	*qwe;

	if (!s1 || !s2)
		return (1);
	qwe = (unsigned char *)s2;
	asd = (unsigned char *)s1;
	x = 0;
	while (asd[x] != '\0' && qwe[x] != '\0' && asd[x] == qwe[x])
	{
		x++;
	}
	return (asd[x] - qwe[x]);
}
