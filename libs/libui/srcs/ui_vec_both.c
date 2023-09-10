/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Jony Salmi <jony.salmi@gmail.com>
 */

#include "libui.h"

void	print_vec(float *vec, size_t size)
{
	size_t	i;

	i = -1;
	ft_printf("vec { ");
	while (++i < size)
		ft_printf("%.2f ", vec[i]);
	ft_printf("}\n");
}

void	print_veci(int *vec, size_t size)
{
	size_t	i;

	i = -1;
	ft_printf("vec { ");
	while (++i < size)
		ft_printf("%d ", vec[i]);
	ft_printf("}\n");
}

int	compare_veci(int *vec1, int *vec2, size_t size)
{
	size_t	i;

	i = -1;
	while (++i < size)
	{
		if (vec1[i] != vec2[i])
			return (0);
	}
	return (1);
}

int	compare_vec(float *vec1, float *vec2, size_t size)
{
	size_t	i;

	i = -1;
	while (++i < size)
	{
		if (vec1[i] != vec2[i])
			return (0);
	}
	return (1);
}
