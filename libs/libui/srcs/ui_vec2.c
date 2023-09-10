/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Jony Salmi <jony.salmi@gmail.com>
 */

#include "libui.h"

t_vec2	vec2_add(t_vec2 v1, t_vec2 v2)
{
	t_vec2	v;

	v.x = v1.x + v2.x;
	v.y = v1.y + v2.y;
	return (v);
}

t_vec2	vec2_sub(t_vec2 v1, t_vec2 v2)
{
	t_vec2	v;

	v.x = v1.x - v2.x;
	v.y = v1.y - v2.y;
	return (v);
}

t_vec2	vec2_divide(t_vec2 v1, t_vec2 v2)
{
	t_vec2	v;

	v.x = v1.x / v2.x;
	v.y = v1.y / v2.y;
	return (v);
}

t_vec2	vec2_divide_float(t_vec2 v1, float n)
{
	t_vec2	v;

	v.x = v1.x / n;
	v.y = v1.y / n;
	return (v);
}
