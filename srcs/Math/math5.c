/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Niklas Neronin <niklas.neronin@gmail.com>
 */

#include "libm.h"

/*
 *	Dot product v2 Returns scalar
 */
float	dot_product_v2(t_v3 v1, t_v3 v2)
{
	return (v1.x * v2.x + v1.y * v2.y);
}

/*
 *	Dot product vector 3
 *	How much are they pointing in the same direction, if it be a number)
 *	https://www.youtube.com/watch?v=BcxfxvYCL1g
 */
float	dot_product_v3(t_v3 v1, t_v3 v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

/*
 *	Returns angle between 2 verticies in radians
 */
float	vectors_angle(t_v3 v1, t_v3 v2)
{
	return (acos(dot_product_v3(v1, v2)
			/ (space_diagonal(v1) * space_diagonal(v2))));
}

/*
 *	Cross product of v2
 */
float	cross_product_v2(float x1, float y1, float x2, float y2)
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
