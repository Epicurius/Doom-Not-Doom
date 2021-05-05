/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_portal_texture.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 21:16:15 by nneronin          #+#    #+#             */
/*   Updated: 2021/05/05 11:35:57 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	draw_portal_solid(t_render *render, t_vline *vline)
{
	t_xyz text;
	double alpha;
	int	coord;
	t_bxpm *ptx;

	ptx = &render->mtx[3];
	text.z = vline->z;
	text.x = (vline->alpha * render->wall.tscale.x * vline->z);
	if (text.x >= ptx->w || text.x < 0)
		text.x = abs((int)text.x % ptx->w);
	while (vline->y1 < vline->y2)
	{
		coord = vline->y1 * render->surface->w + render->x;
		alpha = (vline->y1 - vline->max.ceiling) / vline->line_height;
		text.y = alpha * render->wall.tscale.y;
		if (text.y >= ptx->h || text.y < 0)
			text.y = abs((int)text.y % ptx->h);
		blit_pixel_opaque(render, coord, text, ptx);
		vline->y1++;
	}
}

void	draw_portal_alpha(t_render *render, t_vline *vline)
{
	t_xyz text;
	double alpha;
	int	coord;
	t_bxpm *ptx;

	ptx = &render->mtx[3];
	text.z = vline->z;
	text.x = (vline->alpha * render->wall.tscale.x * vline->z);
	if (text.x >= ptx->w || text.x < 0)
		text.x = abs((int)text.x % ptx->w);
	while (vline->y1 < vline->y2)
	{
		coord = vline->y1 * render->surface->w + render->x;
		alpha = (vline->y1 - vline->max.ceiling) / vline->line_height;
		text.y = alpha * render->wall.tscale.y;
		if (text.y >= ptx->h || text.y < 0)
			text.y = abs((int)text.y % ptx->h);
		blit_pixel_alpha(render, coord, text, ptx);
		vline->y1++;
	}
}


void	draw_portal_texture(t_render *render, t_vline *vline)
{
	vline->y1 = render->ytop;
	vline->y2 = render->ybot;
	draw_portal_solid(render, vline);
	//draw_portal_alpha(render, vline);
	vline->y1 = render->ytop;
	vline->y2 = render->ybot;
	draw_wsprites(render, vline);
}
