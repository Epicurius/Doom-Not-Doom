/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wsprites.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 11:50:05 by nneronin          #+#    #+#             */
/*   Updated: 2021/05/19 14:55:49 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	blit_wsprite_pixels(t_render *render, int coord, t_xyz text, t_bxpm *bxpm)
{
	uint32_t	clr;
	unsigned short	pix;

	pix = bxpm->pix[(int)text.y * bxpm->w + (int)text.x];
	clr = bxpm->clr[pix];
	if (clr == 0x800080)
		return ;
	((Uint32*)render->surface->pixels)[coord] = clr;
	((double*)render->surface->userdata)[coord] = text.z;
}

void	vline_wsprite(t_render *render, t_vline *vline, t_wsprite sprite, int x)
{
	t_xyz text;
	double alpha;
	double pos;
	int coord;

	text.x = x;
	text.z = vline->z;
	pos = sprite.where.y / render->wall.height;
	while (vline->y1 < vline->y2)
	{
		coord = vline->y1 * render->surface->w + render->x;
		alpha = (vline->y1 - vline->max.ceiling) / vline->line_height;
		text.y = (alpha - pos) * sprite.tscale.y + sprite.src.y1;
		if (text.y > sprite.src.y1 && text.y < sprite.src.y2)
			blit_wsprite_pixels(render, coord, text, &render->mtx[sprite.tx]);
		vline->y1++;
	}
}

void	draw_wsprites(t_render *render, t_vline *vline)
{
	int i = -1;
	t_wsprite sprite;

	while (++i < render->wsprite.total)
	{
		if (!render->wsprite.num[i].ready)
			continue ;
		sprite = render->wsprite.num[i];
		double pos = sprite.where.x / render->wall.width * sprite.tscale.x;
		pos *= (render->wall.sv2.z) ? render->wall.sv2.z : render->wall.cv2.z;
		int x = vline->alpha * sprite.tscale.x * vline->z + sprite.src.x1 - pos;
		if (x > sprite.src.x1 && x < sprite.src.x2)
		{
			vline->y1 = vline->curr.ceiling;
			vline->y2 = vline->curr.floor;
			vline_wsprite(render, vline, sprite, x);
		}
	}
}
