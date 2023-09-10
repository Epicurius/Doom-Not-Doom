/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Niklas Neronin <niklas.neronin@gmail.com>
 */

#include "libm.h"

/*
 *	Compare 2 t_v3.
 */
int	comp_v3(t_v3 v1, t_v3 v2)
{
	if (v1.x == v2.x && v1.y == v2.y && v1.z == v2.z)
		return (1);
	return (0);
}

/*
 *	t_v3 v1 + t_v3 v2.
 */
t_v3	add_v3(t_v3 v1, t_v3 v2)
{
	return (new_v3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z));
}

/*
 *	t_v3 v1 - t_v3 v2.
 */
t_v3	sub_v3(t_v3 v1, t_v3 v2)
{
	return (new_v3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z));
}

/*
 *	t_v3 vec * scalar.
 */
t_v3	mult_v3(t_v3 vec, float scalar)
{
	return (new_v3(vec.x * scalar, vec.y * scalar, vec.z * scalar));
}

/*
 *	t_v3 vec / scalar.
 */
t_v3	div_v3(t_v3 vec, float scalar)
{
	return (new_v3(vec.x / scalar, vec.y / scalar, vec.z / scalar));
}
