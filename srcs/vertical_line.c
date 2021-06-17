/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 12:56:23 by nneronin          #+#    #+#             */
/*   Updated: 2021/06/17 13:55:49 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

Uint32	set_zbuffer_shade(double z, double max_z)
{
	double	alpha;
	Uint32 clr;

	alpha = 1 - z / max_z;
	if (z >= 0 && alpha >= 0 && alpha <= 1)
		clr = (int)(alpha * 0xFF) << 24 |
				(int)(alpha * 0xFF) << 16 |
				(int)(alpha * 0xFF) << 8 |
				(int)(alpha * 0xFF);
	else
		clr = 0;
	return (clr);
}


void	shade_zbuffer(t_render *render, t_vline vline)
{
	int x;
	Uint32 clr;
	Uint32 *pix;

	x = render->x;
	pix = (Uint32*)render->surface->pixels;
	clr = set_zbuffer_shade(vline.z, 500);
	while (vline.y1 < vline.y2)
	{
		pix[vline.y1 * render->surface->w + x] = clr;
		((double*)render->surface->userdata)[vline.y1 * render->surface->w + x] = vline.z;
		vline.y1++;
	}
}

void	vline_color(t_render *render, t_vline *vline)
{
	int		coord;

	coord = vline->y1 * render->surface->w + render->x;
	if (vline->y1 < vline->y2)
	{
        ((Uint32*)render->surface->pixels)[coord] = 0xFF00FF00;
		//((double*)render->surface->userdata)[coord] = 200;//vline->z;
		vline->y1 += 1;
		while (vline->y1 < vline->y2 - 1)
		{
			//if (render->x == render->wall.cx1 || render->x == render->wall.cx2)
			if ((render->x - 1 < render->wall.cx1 || render->x + 1 > render->wall.cx2)
					&& vline->y1 < vline->curr.floor && vline->y1 > vline->curr.ceiling)
				((Uint32*)render->surface->pixels)[coord] = 0xFFFF0000;
			//else
				//((Uint32*)render->surface->pixels)[coord] = 0xFF888888;
			coord += render->surface->w;
			//((double*)render->surface->userdata)[coord] = 200;//vline->z;
			vline->y1 += 1;
		}
		coord += render->surface->w;
		((Uint32*)render->surface->pixels)[coord] = 0xFF00FF00;
		//((double*)render->surface->userdata)[coord] = 200;//vline->z;
		vline->y1 += 1;
	}
}

void	vline_monochromic(t_render *render, t_vline *vline)
{
	//vline->y1 = ft_clamp(vline->curr.ceiling, 0, render->surface->h);
	//vline->y2 = ft_clamp(vline->curr.floor, 0, render->surface->h);
	//if (ZBUFFER_COLOR)
	//	shade_zbuffer(render, *vline);
	//else
		vline_color(render, vline);

}
