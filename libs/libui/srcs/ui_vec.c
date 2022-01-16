/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_vec.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalmi <jsalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 19:24:47 by jsalmi            #+#    #+#             */
/*   Updated: 2021/12/10 19:24:48 by jsalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

t_vec2	vec2(float x, float y)
{
	t_vec2	v;

	v.x = x;
	v.y = y;
	return (v);
}

t_vec2i	vec2i(int x, int y)
{
	t_vec2i	v;

	v.x = x;
	v.y = y;
	return (v);
}

//////////////////////
// Vec4
//////////////////////

t_vec4	vec4(float x, float y, float w, float h)
{
	t_vec4	v;

	v.x = x;
	v.y = y;
	v.w = w;
	v.h = h;
	return (v);
}

t_vec4i	vec4i(int x, int y, int w, int h)
{
	t_vec4i	v;

	v.x = x;
	v.y = y;
	v.w = w;
	v.h = h;
	return (v);
}

int	vec2_in_vec4(t_vec2i v2, t_vec4i v4)
{
	if (v2.x >= v4.x && v2.y >= v4.y
		&& v2.x < v4.x + v4.w && v2.y < v4.y + v4.h)
		return (1);
	return (0);
}
