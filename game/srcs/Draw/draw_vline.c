/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Niklas Neronin <niklas.neronin@gmail.com>
 */

#include "doom.h"

/*
 *	Calculate the shade of white depending on the zbuffer value for the pixel.
 */
static Uint32	z_clr(float z)
{
	Uint32	clr;
	float	alpha;

	alpha = 1 - z / ZB;
	if (z >= 0 && alpha >= 0 && alpha <= 1)
		clr = 255 << 24
			| (int)(alpha * 0xFF) << 16
			| (int)(alpha * 0xFF) << 8
			| (int)(alpha * 0xFF);
	else
		clr = 0;
	return (clr);
}

/*
 *	Color the screen with shades of white depending
 *	 on the distance from the player.
 */
void	depth_shadding(t_render *render, t_vline *vline, int side)
{
	int		coord;
	float	z;

	coord = vline->y1 * render->surface->w + render->x;
	while (vline->y1 < vline->y2)
	{
		if (side == BOT || side == TOP)
		{
			if (side == BOT)
				z = (vline->y1 - vline->max.bot) / vline->height.bot;
			else
				z = (vline->max.top - vline->y1) / vline->height.top;
			z = 1 / (NEAR_Z + z * vline->zrange) * vline->z_near_z;
			((Uint32 *)render->surface->pixels)[coord] = z_clr(z);
			((float *)render->surface->userdata)[coord] = z;
		}
		else
		{
			((Uint32 *)render->surface->pixels)[coord] = z_clr(vline->z);
			((float *)render->surface->userdata)[coord] = vline->z;
		}
		coord += render->surface->w;
		vline->y1++;
	}
}

/*
 *	Draw monochrome color neighbour wall.
 */
void	vline_color_bot_top(t_render *render, t_vline *vline, int side)
{
	int		coord;
	float	z;

	coord = vline->y1 * render->surface->w + render->x;
	while (vline->y1 < vline->y2)
	{
		if (side == BOT)
			z = (vline->y1 - vline->max.bot) / vline->height.bot;
		else
			z = (vline->max.top - vline->y1) / vline->height.top;
		z = 1 / (NEAR_Z + z * vline->zrange) * vline->z_near_z;
		((Uint32 *)render->surface->pixels)[coord] = FLOOR_CEILING_COLOR;
		((float *)render->surface->userdata)[coord] = z;
		coord += render->surface->w;
		vline->y1++;
	}
}

/*
 *	Draw monochrome color walls.
 */
void	vline_color_walls(t_render *render, t_vline *vline)
{
	int	coord;

	coord = vline->y1 * render->surface->w + render->x;
	if (vline->y1 < vline->y2)
	{
		((Uint32 *)render->surface->pixels)[coord] = MAP_OUTLINE_COLOR;
		((float *)render->surface->userdata)[coord] = vline->z;
		coord += render->surface->w;
		while (++vline->y1 < vline->y2 - 1)
		{
			if (render->x - 1 < render->wall->cx1
				|| render->x + 1 > render->wall->cx2)
				((Uint32 *)render->surface->pixels)[coord] = MAP_OUTLINE_COLOR;
			else
				((Uint32 *)render->surface->pixels)[coord] = WALL_COLOR;
			((float *)render->surface->userdata)[coord] = vline->z;
			coord += render->surface->w;
		}
		if (vline->y1 < vline->y2)
		{
			((Uint32 *)render->surface->pixels)[coord] = MAP_OUTLINE_COLOR;
			((float *)render->surface->userdata)[coord] = vline->z;
			vline->y1 += 1;
		}
	}
}

/*
 *	Depending on the macro draw walls with white zbuffer shade
 *	or monochrome color.
 */
void	vline_monochromic(t_render *render, t_vline *vline, int side)
{
	if (DEPTH_SHADING)
		depth_shadding(render, vline, side);
	else if (side == TOP || side == BOT)
		vline_color_bot_top(render, vline, side);
	else
		vline_color_walls(render, vline);
}
