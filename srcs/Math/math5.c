/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math5.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/19 17:37:59 by nneronin          #+#    #+#             */
/*   Updated: 2021/09/17 17:35:45 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libm.h"

/*
 *	Dot product v2 Returns scalar
 */
TEMP_FLOAT	dot_product_v2(t_v3 v1, t_v3 v2)
{
	return (v1.x * v2.x + v1.y * v2.y);
}

/*
 *	Dot product v3
 */
TEMP_FLOAT	dot_product_v3(t_v3 v1, t_v3 v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

/*
 *	Returns angle between 2 verticies in radians
 */
TEMP_FLOAT	vectors_angle(t_v3 v1, t_v3 v2)
{
	return (acos(dot_product_v3(v1, v2)
			/ (space_diagonal(v1) * space_diagonal(v2))));
}

/*
 *	Cross product of v2
 */
TEMP_FLOAT	cross_product_v2(TEMP_FLOAT x1, TEMP_FLOAT y1, TEMP_FLOAT x2, TEMP_FLOAT y2)
{
	return (x1 * y2 - y1 * x2);
}

/*
 *	Cross product of v3
 */
t_v3	cross_product_v3(t_v3 v1, t_v3 v2)
{
	t_v3	res;

	res.x = v1.y * v2.z - v1.z * v2.y;
	res.y = v1.z * v2.x - v1.x * v2.z;
	res.z = v1.x * v2.y - v1.y * v2.x;
	return (res);
}
