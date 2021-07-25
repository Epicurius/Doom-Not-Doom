/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blit_entity.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 10:42:07 by nneronin          #+#    #+#             */
/*   Updated: 2021/07/25 13:59:36 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	hit_enemy(t_entity_thread *thread, int coord)
{
	if (thread->hp != NULL && thread->shooting && coord == thread->center.z)
	{
		*thread->hp -= thread->dmg;
		*thread->hm = 1;
	}
}

static void	blit_entity24(t_entity_thread *thread, int coord, t_v3 text)
{
	Uint32			clr;
	unsigned short	pix;

	if (text.z >= ((double *)thread->surface->userdata)[coord])
		return ;
	pix = thread->bxpm->pix[(int)text.y * thread->bxpm->w + (int)text.x];
	clr = thread->bxpm->clr[pix];
	if (clr == 0xFF800080)
		return ;
	if (thread->hp != NULL)
		hit_enemy(thread, coord);
	((Uint32 *)thread->surface->pixels)[coord] = clr;
	((double *)thread->surface->userdata)[coord] = text.z;
}

static void	blit_entity32(t_entity_thread *thread, int coord, t_v3 text)
{
	Uint32			clr;
	unsigned short	pix;

	if (text.z >= ((double *)thread->surface->userdata)[coord])
		return ;
	pix = thread->bxpm->pix[(int)text.y * thread->bxpm->w + (int)text.x];
	clr = thread->bxpm->clr[pix];
	if (clr == 0x00000000)
		return ;
	hit_enemy(thread, coord);
	((Uint32 *)thread->surface->pixels)[coord]
		= blend_alpha(((Uint32 *)thread->surface->pixels)[coord],
			clr, clr >> 24 & 0xFF);
	((double *)thread->surface->userdata)[coord] = text.z;
}

int	blit_game_entity(void *arg)
{
	t_v3			text;
	t_v2			alpha;
	t_point			p;
	t_entity_thread	*thread;

	thread = arg;
	text.z = thread->render.z;
	p.y = thread->render.clamp_start.y - 1;
	while (++p.y < thread->render.clamp_end.y)
	{
		alpha.y = (p.y - thread->render.start.y) / thread->render.yrange;
		text.y = (1.0 - alpha.y) * thread->pos.y1 + alpha.y * thread->pos.y2;
		p.x = thread->render.clamp_start.x - 1;
		while (++p.x < thread->render.clamp_end.x)
		{
			alpha.x = (p.x - thread->render.start.x) / thread->render.xrange;
			text.x = (1.0 - alpha.x) * thread->pos.x1 + alpha.x
				* thread->pos.x2;
			if (thread->bxpm->bpp == 32)
				blit_entity32(thread, p.y * thread->surface->w + p.x, text);
			else
				blit_entity24(thread, p.y * thread->surface->w + p.x, text);
		}
	}
	return (1);
}
