/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 12:56:23 by nneronin          #+#    #+#             */
/*   Updated: 2021/07/26 15:02:43 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

Uint32	z_clr(double z, double max_z)
{
	Uint32	clr;
	double	alpha;

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

void	shade_zbuffer(t_render *render, t_vline *vline, int side)
{
	int		coord;
	double	z;

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
			((double *)render->surface->userdata)[coord] = z;
		}
		else
		{
			((Uint32 *)render->surface->pixels)[coord] = z_clr(vline->z, ZB);
			((double *)render->surface->userdata)[coord] = vline->z;
		}
		coord += render->surface->w;
		vline->y1++;
	}
}

void	vline_color_bot_top(t_render *render, t_vline *vline, int side)
{
	int		coord;
	double	z;

	coord = vline->y1 * render->surface->w + render->x;
	while (vline->y1 < vline->y2)
	{
		if (side == BOT)
			z = (vline->y1 - vline->max.floor) / vline->height.floor;
		else if (side == TOP)
			z = (vline->max.ceiling - vline->y1) / vline->height.ceiling;
		z = 1 / (NEAR_Z + z * vline->zrange) * vline->z_near_z;
		((Uint32 *)render->surface->pixels)[coord] = 0xFFAA8888;
		((double *)render->surface->userdata)[coord] = z;
		coord += render->surface->w;
		vline->y1++;
	}
}

void	vline_color_walls(t_render *render, t_vline *vline)
{
	int	coord;

	coord = vline->y1 * render->surface->w + render->x;
	if (vline->y1 < vline->y2)
	{
		((Uint32 *)render->surface->pixels)[coord] = 0xFF00FF00;
		((double *)render->surface->userdata)[coord] = vline->z;
		coord += render->surface->w;
		while (++vline->y1 < vline->y2 - 1)
		{
			if (render->x - 1 < render->wall.cx1
				|| render->x + 1 > render->wall.cx2)
				((Uint32 *)render->surface->pixels)[coord] = 0xFF00FF00;
			else
				((Uint32 *)render->surface->pixels)[coord] = 0xFF888888;
			((double *)render->surface->userdata)[coord] = vline->z;
			coord += render->surface->w;
		}
		if (vline->y1 < vline->y2)
		{
			((Uint32 *)render->surface->pixels)[coord] = 0xFF00FF00;
			((double *)render->surface->userdata)[coord] = vline->z;
			vline->y1 += 1;
		}
	}
}

void	vline_monochromic(t_render *render, t_vline *vline, int side)
{
	if (ZBUFFER_COLOR)
		shade_zbuffer(render, vline, side);
	else if (side == TOP || side == BOT)
		vline_color_bot_top(render, vline, side);
	else
		vline_color_walls(render, vline);
}
