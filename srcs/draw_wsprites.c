/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wsprites.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 11:50:05 by nneronin          #+#    #+#             */
/*   Updated: 2021/07/11 15:52:04 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	blit_wsprite24(t_render *render, int coord, t_v3 text,
	t_bxpm *bxpm)
{
	Uint32			clr;
	unsigned short	pix;

	pix = bxpm->pix[(int)text.y * bxpm->w + (int)text.x];
	clr = bxpm->clr[pix];
	if (clr == 0xFF800080)
		return ;
	((Uint32 *)render->surface->pixels)[coord] = clr;
	((double *)render->surface->userdata)[coord] = text.z;
}

static void	blit_wsprite32(t_render *render, int coord, t_v3 text,
	t_bxpm *bxpm)
{
	Uint32			clr;
	unsigned short	pix;

	pix = bxpm->pix[(int)text.y * bxpm->w + (int)text.x];
	clr = bxpm->clr[pix];
	if (0 == clr >> 24 & 0xFF)
		return ;
	((Uint32 *)render->surface->pixels)[coord]
		= blend_alpha(clr, ((Uint32 *)render->surface->pixels)[coord], 240);
	((double *)render->surface->userdata)[coord] = text.z;
}

static void	vline_wsprite(t_render *render, t_vline *vline, t_wsprite entity,
	int x)
{
	t_v3	text;
	double	alpha;
	double	pos;
	int		coord;

	text.x = x;
	text.z = vline->z;
	pos = entity.where.y / render->wall.height;
	while (vline->y1 < vline->y2)
	{
		coord = vline->y1 * render->surface->w + render->x;
		alpha = (vline->y1 - vline->max.ceiling) / vline->line_height;
		text.y = (alpha - pos) * entity.tscale.y + entity.src.y1;
		if (text.y > entity.src.y1 && text.y < entity.src.y2)
		{
			if (render->mtx[entity.tx].bpp == 32)
				blit_wsprite32(render, coord, text, &render->mtx[entity.tx]);
			else
				blit_wsprite24(render, coord, text, &render->mtx[entity.tx]);
		}
		vline->y1++;
	}
}

void	draw_wsprites(t_render *render, t_vline *vline)
{
	int			i;
	int			x;
	double		pos;
	t_wsprite	entity;

	i = -1;
	while (++i < render->wsprite.total)
	{
		if (!render->wsprite.num[i].ready)
			continue ;
		entity = render->wsprite.num[i];
		pos = entity.where.x / render->wall.width * entity.tscale.x;
		if (render->wall.sv2.z)
			pos *= render->wall.sv2.z;
		else
			pos *= render->wall.cv2.z;
		x = vline->alpha * entity.tscale.x * vline->z + entity.src.x1 - pos;
		if (x > entity.src.x1 && x < entity.src.x2)
		{
			vline->y1 = vline->curr.ceiling;
			vline->y2 = vline->curr.floor;
			vline_wsprite(render, vline, entity, x);
		}
	}
}
