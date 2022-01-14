/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 09:06:49 by nneronin          #+#    #+#             */
/*   Updated: 2021/12/10 09:21:03 by jsalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
