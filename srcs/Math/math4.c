/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/19 17:37:16 by nneronin          #+#    #+#             */
/*   Updated: 2021/09/19 17:30:09 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libm.h"

/*
 *	Length of a vector 2D
 */
TEMP_DOUBLE	vector_magnitude_v2(t_v3 v)
{
	return (sqrt((v.x * v.y) + (v.x * v.y)));
}

/*
 *	Length of a vector 3D
 */
TEMP_DOUBLE	vector_magnitude_v3(t_v3 v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

/*
 *	Space Diagonal
 */
TEMP_DOUBLE	pythagoras(TEMP_DOUBLE x, TEMP_DOUBLE y)
{
	return (sqrt(x * x + y * y));
}

/*
 *	Space Diagonal/Pythagoras
 */
TEMP_DOUBLE	space_diagonal(t_v3 v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

/*
 *	Get normal
 */
TEMP_DOUBLE	normalize_v3(t_v3 *vec)
{
	TEMP_DOUBLE	length;

	length = sqrt(vec->x * vec->x + vec->y * vec->y + vec->z * vec->z);
	if (length)
	{
		vec->x /= length;
		vec->y /= length;
		vec->z /= length;
	}
	return (length);
}
