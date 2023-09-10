/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Niklas Neronin <niklas.neronin@gmail.com>
 */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void	*mem;

	mem = malloc(size);
	if (!mem)
	{
		write(1, "\x1b[31m!![FT_MEMALLOC ERROR]!!\x1b[00m\n", 35);
		exit(1);
	}
	ft_memset(mem, 0, size);
	return (mem);
}
