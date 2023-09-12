/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Niklas Neronin <niklas.neronin@gmail.com>
 */

#include "libm.h"

/*
 *	Length of a vector 2D
 */
float	vector_magnitude_v2(t_v3 v)
{
	return (sqrt(v.x * v.x + v.y * v.y));
}

/*
 *	Length of a vector 3D
 */
float	vector_magnitude_v3(t_v3 v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

/*
 *	Space Diagonal
 */
float	pythagoras(float x, float y)
{
	return (sqrt(x * x + y * y));
}

/*
 *	Space Diagonal/Pythagoras
 */
float	space_diagonal(t_v3 v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

/*
 *	Get normal
 */
float	normalize_v3(t_v3 *vec)
{
	float	length;

	length = sqrt(vec->x * vec->x + vec->y * vec->y + vec->z * vec->z);
	if (length)
	{
		vec->x /= length;
		vec->y /= length;
		vec->z /= length;
	}
	return (length);
}
