/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math5.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/19 17:37:59 by nneronin          #+#    #+#             */
/*   Updated: 2021/08/11 13:06:22 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libm.h"

/*
 *	Dot product v2 Returns scalar
 */
double	dot_product_v2(t_v3 v1, t_v3 v2)
{
	return (v1.x * v2.x + v1.y * v2.y);
}

/*
 *	Dot product v3
 */
double	dot_product_v3(t_v3 v1, t_v3 v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

/*
 *	Returns angle between 2 verticies in radians
 */
double	vectors_angle(t_v3 v1, t_v3 v2)
{
	return (acos(dot_product_v3(v1, v2)
			/ (space_diagonal(v1) * space_diagonal(v2))));
}

/*
 *	Cross product of v2
 */
double	cross_product_v2(double x1, double y1, double x2, double y2)
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
