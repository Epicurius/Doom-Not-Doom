/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Niklas Neronin <niklas.neronin@gmail.com>
 */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	char			*str;
	unsigned char	cchar;

	i = 0;
	str = b;
	cchar = c;
	while (i < len)
	{
		str[i] = cchar;
		i++;
	}
	return (b);
}
