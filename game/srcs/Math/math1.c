/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Niklas Neronin <niklas.neronin@gmail.com>
 */

#include "libm.h"

/*
 *	Create a new t_point struct and assign values
 */
t_point	new_point(int x, int y)
{
	t_point	new;

	new.x = x;
	new.y = y;
	return (new);
}

/*
 *	Create a new t_v2 struct and assign values
 */
t_v2	new_v2(float x, float y)
{
	t_v2	new;

	new.x = x;
	new.y = y;
	return (new);
}

/*
 *	Create a new t_v3 struct and assign values
 */
t_v3	new_v3(float x, float y, float z)
{
	t_v3	new;

	new.x = x;
	new.y = y;
	new.z = z;
	return (new);
}

/*
 *	Create a new t_rect struct with x1, y1, x2, y2
 */
t_rect	rect_xy2(int x1, int y1, int x2, int y2)
{
	t_rect	new;

	new.x1 = x1;
	new.y1 = y1;
	new.x2 = x2;
	new.y2 = y2;
	new.w = new.x2 - new.x1;
	new.h = new.y2 - new.y1;
	new.ratio = (float)new.h / (float)new.w;
	return (new);
}

/*
 *	Create a new t_rect struct with x, y, width, height
 */
t_rect	rect_xywh(int x1, int y1, int w, int h)
{
	t_rect	new;

	new.x1 = x1;
	new.y1 = y1;
	new.x2 = x1 + w;
	new.y2 = y1 + h;
	new.w = w;
	new.h = h;
	new.ratio = (float)new.h / (float)new.w;
	return (new);
}
