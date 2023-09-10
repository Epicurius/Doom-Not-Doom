/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Jony Salmi <jony.salmi@gmail.com>
 */

#include "libui.h"

void	vec2i_swap(t_vec2i *v1, t_vec2i *v2)
{
	t_vec2i	temp;
	int		i;

	temp = *v1;
	i = -1;
	while (++i < VEC2_SIZE)
		v1->v[i] = v2->v[i];
	i = -1;
	while (++i < VEC2_SIZE)
		v2->v[i] = temp.v[i];
}

void	vec2_swap(t_vec2 *v1, t_vec2 *v2)
{
	t_vec2	temp;
	int		i;

	temp = *v1;
	i = -1;
	while (++i < VEC2_SIZE)
		v1->v[i] = v2->v[i];
	i = -1;
	while (++i < VEC2_SIZE)
		v2->v[i] = temp.v[i];
}

t_vec2i	vec2i_add(t_vec2i v1, t_vec2i v2)
{
	t_vec2i	v;

	v.x = v1.x + v2.x;
	v.y = v1.y + v2.y;
	return (v);
}

t_vec2i	vec2i_sub(t_vec2i v1, t_vec2i v2)
{
	t_vec2i	v;

	v.x = v1.x - v2.x;
	v.y = v1.y - v2.y;
	return (v);
}
