/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 12:56:23 by nneronin          #+#    #+#             */
/*   Updated: 2021/04/26 14:37:13 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	vline_color(t_render *render, t_vline vline)
{
	int	x;
	int	y;
	Uint32	*pix;

	x = render->x;
	pix = (Uint32*)render->surface->pixels;
	if (vline.y1 < vline.y2)
	{
        pix[vline.y1 * render->surface->w + x] = 0xFF000000;
		((double*)render->surface->userdata)[vline.y1 * render->surface->w + x] = vline.z;
		y = vline.y1 + 1;
		while (y < vline.y2)
		{
			pix[y * render->surface->w + x] = 0xFF888888;
			((double*)render->surface->userdata)[y * render->surface->w + x] = vline.z;
			y++;
		}
		pix[vline.y2 * render->surface->w + x] = 0xFF000000;
		((double*)render->surface->userdata)[vline.y2 * render->surface->w + x] = vline.z;
	}
}

uint32_t	set_zbuffer_shade(double z, double max_z)
{
	double	alpha;
	uint32_t clr;

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
	uint32_t clr;
	uint32_t *pix;

	x = render->x;
	pix = (Uint32*)render->surface->pixels;
	clr = set_zbuffer_shade(vline.z, 200);
	while (vline.y1 < vline.y2)
	{
		pix[vline.y1 * render->surface->w + x] = clr;
		((double*)render->surface->userdata)[vline.y1 * render->surface->w + x] = vline.z;
		vline.y1++;
	}
}


void	vline_monochromic(t_render *render, t_vline *vline)
{
	vline->y1 = ft_clamp(vline->curr.ceiling, 0, render->surface->h);
	vline->y2 = ft_clamp(vline->curr.floor, 0, render->surface->h);
	if (ZBUFFER_COLOR)
		shade_zbuffer(render, *vline);
	else
		vline_color(render, *vline);

}
