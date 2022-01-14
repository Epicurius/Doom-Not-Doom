/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 15:11:05 by nneronin          #+#    #+#             */
/*   Updated: 2021/05/16 11:09:58 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
