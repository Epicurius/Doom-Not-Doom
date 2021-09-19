/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wsprites.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 11:50:05 by nneronin          #+#    #+#             */
/*   Updated: 2021/09/19 17:30:08 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
 *	Blit wall sprite depending on if it has alpha or not.
 */
static void	blit_wsprite(t_render *render, int coord, t_v3 text, t_bxpm *bxpm)
{
	Uint32			clr;
	unsigned short	pix;

	pix = bxpm->pix[(int)text.y * bxpm->w + (int)text.x];
	clr = bxpm->clr[pix];
	if (bxpm->bpp == 32)
	{
		if (0 == (clr >> 24 & 0xFF))
			return ;
		clr = blend_alpha(((Uint32 *)render->surface->pixels)[coord], clr,
				clr >> 24 & 0xFF);
	}
	else if (clr == 0xFF800080)
		return ;
	((Uint32 *)render->surface->pixels)[coord] = clr;
	((TEMP_DOUBLE *)render->surface->userdata)[coord] = text.z;
}

/*
 *	Draw vertical line wall sprite to window surface.
 */
static void	vline_wsprite(t_render *render, t_vline *vline,
	t_wsprite *wsprite, int x)
{
	t_v3	text;
	TEMP_DOUBLE	alpha;
	TEMP_DOUBLE	pos;
	int		coord;

	text.x = x;
	text.z = vline->z;
	pos = wsprite->where.y / render->wall->height;
	while (vline->y1 < vline->y2)
	{
		coord = vline->y1 * render->surface->w + render->x;
		alpha = (vline->y1 - vline->max.top) / vline->line_height;
		text.y = (alpha - pos) * wsprite->tscale.y + wsprite->src.y1;
		if (text.y > wsprite->src.y1 && text.y < wsprite->src.y2)
		{
			if (wsprite->trigger == 0 && render->center.z == coord
				&& render->player->action == wsprite->action)
				wsprite->trigger = TRUE;
			blit_wsprite(render, coord, text, &render->mtx[wsprite->tx]);
		}
		vline->y1++;
	}
}

/*
 *	Draw wall sprite.
 */
void	draw_wsprites(t_render *render, t_vline *vline)
{
	int			i;
	int			x;
	TEMP_DOUBLE		pos;
	t_wsprite	*wsprite;

	i = -1;
	while (++i < render->wsprite->total)
	{
		if (!render->wsprite->num[i].ready)
			continue ;
		wsprite = &render->wsprite->num[i];
		pos = wsprite->where.x / render->wall->width * wsprite->tscale.x;
		if (render->wall->sv2.z)
			pos *= render->wall->sv2.z;
		else
			pos *= render->wall->cv2.z;
		x = vline->alpha * wsprite->tscale.x * vline->z + wsprite->src.x1 - pos;
		if (x > wsprite->src.x1 && x < wsprite->src.x2)
		{
			vline->y1 = vline->curr.top;
			vline->y2 = vline->curr.bot;
			vline_wsprite(render, vline, wsprite, x);
		}
	}
}
