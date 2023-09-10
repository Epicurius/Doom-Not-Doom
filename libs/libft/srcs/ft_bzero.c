/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Niklas Neronin <niklas.neronin@gmail.com>
 */

#include "libft.h"

void	ft_bzero(void *str, size_t n)
{
	if (n > 0)
		ft_memset(str, 0, n);
}
