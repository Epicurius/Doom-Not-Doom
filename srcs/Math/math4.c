/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/19 17:37:16 by nneronin          #+#    #+#             */
/*   Updated: 2021/09/13 10:50:58 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libm.h"

/*
 *	Length of a vector 2D
 */
double	vector_magnitude_v2(t_v3 v)
{
	return (sqrt((v.x * v.y) + (v.x * v.y)));
}

/*
 *	Length of a vector 3D
 */
double	vector_magnitude_v3(t_v3 v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

/*
 *	Space Diagonal
 */
double	pythagoras(double x, double y)
{
	return (sqrt(x * x + y * y));
}

/*
 *	Space Diagonal/Pythagoras
 */
double	space_diagonal(t_v3 v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

/*
 *	Get normal
 */
double	normalize_v3(t_v3 *vec)
{
	double	length;

	length = sqrt(vec->x * vec->x + vec->y * vec->y + vec->z * vec->z);
	if (length)
	{
		vec->x /= length;
		vec->y /= length;
		vec->z /= length;
	}
	return (length);
}
