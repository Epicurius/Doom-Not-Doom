/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/19 17:39:34 by nneronin          #+#    #+#             */
/*   Updated: 2021/07/11 15:27:44 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libm.h"

//	Make a new t_point struct and assign values
t_point	new_point(int x, int y)
{
	t_point	new;

	new.x = x;
	new.y = y;
	return (new);
}

//	Make a new t_v2 struct and assign values
t_v2	new_v2(double x, double y)
{
	t_v2	new;

	new.x = x;
	new.y = y;
	return (new);
}

//	Make a new t_v3 struct and assign values
t_v3	new_v3(double x, double y, double z)
{
	t_v3	new;

	new.x = x;
	new.y = y;
	new.z = z;
	return (new);
}

//		Make new t_rect struct for texture sheets
t_rect	rect_xy2(int x1, int y1, int x2, int y2)
{
	t_rect	new;

	new.x1 = x1;
	new.y1 = y1;
	new.x2 = x2;
	new.y2 = y2;
	new.w = new.x2 - new.x1;
	new.h = new.y2 - new.y1;
	new.ratio = (double)new.h / (double)new.w;
	return (new);
}

t_rect	rect_xywh(int x1, int y1, int w, int h)
{
	t_rect	new;

	new.x1 = x1;
	new.y1 = y1;
	new.x2 = x1 + w;
	new.y2 = y1 + h;
	new.w = w;
	new.h = h;
	new.ratio = (double)new.h / (double)new.w;
	return (new);
}
