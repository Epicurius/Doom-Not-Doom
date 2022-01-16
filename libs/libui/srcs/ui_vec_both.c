/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_vec_both.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalmi <jsalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 19:24:42 by jsalmi            #+#    #+#             */
/*   Updated: 2021/12/10 19:24:45 by jsalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
