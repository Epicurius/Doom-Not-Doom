/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blit_entity.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 10:42:07 by nneronin          #+#    #+#             */
/*   Updated: 2021/05/20 17:09:26 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	hit_enemy(t_entity_render *render, int coord)
{
	if (render->hp != NULL && render->shooting
			&& coord == (render->surface->h/2 * render->surface->w + render->surface->w/2))
		*render->hp -= render->dmg;
	//if (coord == (render->surface->h/2 * render->surface->w + render->surface->w/2))
	//	*render->danger = 1;
	//else
	//	*render->danger = 0;
}

void	blit_game_entity24(t_entity_render *render, int coord, t_xyz text)
{
	uint32_t	clr;
	unsigned short	pix;

	if (text.z >= ((double*)render->surface->userdata)[coord])
		return ;
	pix = render->bxpm->pix[(int)text.y * render->bxpm->w + (int)text.x];
	clr = render->bxpm->clr[pix];
	if (clr == 0xFF800080)
		return ;
	if (render->hp != NULL)
		hit_enemy(render, coord);
	((Uint32*)render->surface->pixels)[coord] = clr;
	((double*)render->surface->userdata)[coord] = text.z;
}

void	blit_game_entity32(t_entity_render *render, int coord, t_xyz text)
{
	uint32_t	clr;
	unsigned short	pix;

	if (text.z >= ((double*)render->surface->userdata)[coord])
		return ;
	pix = render->bxpm->pix[(int)text.y * render->bxpm->w + (int)text.x];
	clr = render->bxpm->clr[pix];
	if (clr == 0x00000000)
		return ;
		hit_enemy(render, coord);
	((Uint32*)render->surface->pixels)[coord] =
		blend_alpha(((uint32_t*)render->surface->pixels)[coord], clr, clr >> 24 & 0xFF);
	((double*)render->surface->userdata)[coord] = text.z;
}

int		blit_game_entity(void *arg)
{
	double alphax;
	double alphay;
	t_xyz text;
	t_entity_render *render;

	render = arg;
	text.z = render->screen.z;
	int y = render->clamp_start.y;
	while (++y < render->clamp_end.y)
	{
		alphay = (y - render->start.y) / render->yrange;
		text.y = (1.0 - alphay) * render->pos.y1 + alphay * render->pos.y2;
		int x = render->clamp_start.x;
		while (++x < render->clamp_end.x)
		{
			alphax = (x - render->start.x) / render->xrange;
			text.x = (1.0 - alphax) * render->pos.x1 + alphax * render->pos.x2;
			if (render->bxpm->bpp == 32)
				blit_game_entity32(render, y * render->surface->w + x, text);
			else
				blit_game_entity24(render, y * render->surface->w + x, text);
		}
	}
	return (1);
}
