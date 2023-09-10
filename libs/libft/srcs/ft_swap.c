/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Niklas Neronin <niklas.neronin@gmail.com>
 */

#include "libft.h"

void	ft_swap(int *a, int *b)
{
	int	tmp;

	tmp = 0;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	ft_fswap(float *a, float *b)
{
	float	tmp;

	tmp = 0;
	tmp = *a;
	*a = *b;
	*b = tmp;
}
