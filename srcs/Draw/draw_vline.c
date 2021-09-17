/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_vline.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 12:56:23 by nneronin          #+#    #+#             */
/*   Updated: 2021/09/17 17:35:45 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
 *	Calculate the shade of white depending on the zbuffer value for the pixel.
 */
Uint32	z_clr(TEMP_FLOAT z, TEMP_FLOAT max_z)
{
	Uint32	clr;
	TEMP_FLOAT	alpha;

	alpha = 1 - z / max_z;
	if (z >= 0 && alpha >= 0 && alpha <= 1)
		clr = (int)(alpha * 0xFF) << 24
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
void	shade_zbuffer(t_render *render, t_vline *vline, int side)
{
	int		coord;
	TEMP_FLOAT	z;

	coord = vline->y1 * render->surface->w + render->x;
	while (vline->y1 < vline->y2)
	{
		if (side == BOT || side == TOP)
		{
			if (side == BOT)
				z = (vline->y1 - vline->max.floor) / vline->height.floor;
			else if (side == TOP)
				z = (vline->max.ceiling - vline->y1) / vline->height.ceiling;
			z = 1 / (NEAR_Z + z * vline->zrange) * vline->z_near_z;
			((Uint32 *)render->surface->pixels)[coord] = z_clr(z, ZB);
			((TEMP_FLOAT *)render->surface->userdata)[coord] = z;
		}
		else
		{
			((Uint32 *)render->surface->pixels)[coord] = z_clr(vline->z, ZB);
			((TEMP_FLOAT *)render->surface->userdata)[coord] = vline->z;
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
	TEMP_FLOAT	z;

	coord = vline->y1 * render->surface->w + render->x;
	while (vline->y1 < vline->y2)
	{
		if (side == BOT)
			z = (vline->y1 - vline->max.floor) / vline->height.floor;
		else if (side == TOP)
			z = (vline->max.ceiling - vline->y1) / vline->height.ceiling;
		z = 1 / (NEAR_Z + z * vline->zrange) * vline->z_near_z;
		((Uint32 *)render->surface->pixels)[coord] = 0xFFAA8888;
		((TEMP_FLOAT *)render->surface->userdata)[coord] = z;
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
		((Uint32 *)render->surface->pixels)[coord] = 0xFF00FF00;
		((TEMP_FLOAT *)render->surface->userdata)[coord] = vline->z;
		coord += render->surface->w;
		while (++vline->y1 < vline->y2 - 1)
		{
			if (render->x - 1 < render->wall->cx1
				|| render->x + 1 > render->wall->cx2)
				((Uint32 *)render->surface->pixels)[coord] = 0xFF00FF00;
			else
				((Uint32 *)render->surface->pixels)[coord] = 0xFF888888;
			((TEMP_FLOAT *)render->surface->userdata)[coord] = vline->z;
			coord += render->surface->w;
		}
		if (vline->y1 < vline->y2)
		{
			((Uint32 *)render->surface->pixels)[coord] = 0xFF00FF00;
			((TEMP_FLOAT *)render->surface->userdata)[coord] = vline->z;
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
	if (ZBUFFER_COLOR)
		shade_zbuffer(render, vline, side);
	else if (side == TOP || side == BOT)
		vline_color_bot_top(render, vline, side);
	else
		vline_color_walls(render, vline);
}
