/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 12:56:23 by nneronin          #+#    #+#             */
/*   Updated: 2021/04/21 15:55:09 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	vline_color(t_render *render, t_vline *vline, int y1, int y2)
{
	int	x;
	int	y;
	Uint32	*pix;

	x = render->x;
	pix = (Uint32*)render->surface->pixels;
	if (y1 < y2)
	{
        pix[y1 * render->surface->w + x] = 0xFF000000;
		((double*)render->surface->userdata)[y1 * render->surface->w + x] = vline->z;
		y = y1 + 1;
		while (y < y2)
		{
			pix[y * render->surface->w + x] = 0xFF888888;
			((double*)render->surface->userdata)[y * render->surface->w + x] = vline->z;
			y++;
		}
		pix[y2 * render->surface->w + x] = 0xFF000000;
		((double*)render->surface->userdata)[y2 * render->surface->w + x] = vline->z;
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


void	shade_zbuffer(t_render *render, t_vline *vline, int y1, int y2)
{
	int x;
	Uint32	*pix;

	x = render->x;
	pix = (Uint32*)render->surface->pixels;
	while (y1 < y2)
	{
		pix[y1 * render->surface->w + x] = set_zbuffer_shade(vline->z, 100);
		((double*)render->surface->userdata)[y1 * render->surface->w + x] = vline->z;
		y1++;
	}
}


void	vline_monochromic(t_render *render, t_vline *vline)
{
	int y1;
	int y2;

	y1 = ft_clamp(vline->y1, 0, render->surface->h);
	y2 = ft_clamp(vline->y2, 0, render->surface->h);
	if (ZBUFFER_COLOR)
		shade_zbuffer(render, vline, y1, y2);
	else
		vline_color(render, vline, y1, y2);

}
