/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Niklas Neronin <niklas.neronin@gmail.com>
 */

#include "libft.h"

double	ft_pow(double n, int pow)
{
	if (pow > 0)
		return (n * ft_pow(n, pow - 1));
	return (1);
}

long double	ft_long_pow(long double n, int pow)
{
	long double	tmp;

	tmp = n;
	if (pow == 0)
		return (1);
	if (pow < 1)
		return (0);
	while (--pow)
		n *= tmp;
	return (n);
}
