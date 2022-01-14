/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clamp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 14:10:50 by nneronin          #+#    #+#             */
/*   Updated: 2021/07/26 14:26:19 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static double	ft_fclamp2(double x, double min, double max)
{
	if (x < min)
		return (min);
	if (x > max)
		return (max);
	return (x);
}

double	ft_fclamp(double x, double a, double b)
{
	if (a > b)
		return (ft_fclamp2(x, b, a));
	else if (a < b)
		return (ft_fclamp2(x, a, b));
	else
		return (a);
}

static int	ft_clamp2(int x, int min, int max)
{
	if (x < min)
		return (min);
	if (x > max)
		return (max);
	return (x);
}

int	ft_clamp(int x, int a, int b)
{
	if (a > b)
		return (ft_clamp2(x, b, a));
	else if (a < b)
		return (ft_clamp2(x, a, b));
	else
		return (a);
}
