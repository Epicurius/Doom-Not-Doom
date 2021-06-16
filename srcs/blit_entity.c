/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blit_entity.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 10:42:07 by nneronin          #+#    #+#             */
/*   Updated: 2021/06/16 16:21:05 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	hit_enemy(t_entity_thread *thread, int coord)
{
	if (thread->hp != NULL && thread->shooting && coord == thread->center)
	{
		*thread->hp -= thread->dmg;
	}
}

void	blit_game_entity24(t_entity_thread *thread, int coord, t_v3 text)
{
	uint32_t		clr;
	unsigned short	pix;

	if (text.z >= ((double*)thread->surface->userdata)[coord])
		return ;
	pix = thread->bxpm->pix[(int)text.y * thread->bxpm->w + (int)text.x];
	clr = thread->bxpm->clr[pix];
	if (clr == 0xFF800080)
		return ;
	if (thread->hp != NULL)
		hit_enemy(thread, coord);
	((Uint32*)thread->surface->pixels)[coord] = clr;
	((double*)thread->surface->userdata)[coord] = text.z;
}

void	blit_game_entity32(t_entity_thread *thread, int coord, t_v3 text)
{
	uint32_t	clr;
	unsigned short	pix;

	if (text.z >= ((double*)thread->surface->userdata)[coord])
		return ;
	pix = thread->bxpm->pix[(int)text.y * thread->bxpm->w + (int)text.x];
	clr = thread->bxpm->clr[pix];
	if (clr == 0x00000000)
		return ;
	hit_enemy(thread, coord);
	((Uint32*)thread->surface->pixels)[coord] =
		blend_alpha(((uint32_t*)thread->surface->pixels)[coord], clr, clr >> 24 & 0xFF);
	((double*)thread->surface->userdata)[coord] = text.z;
}

int		blit_game_entity(void *arg)
{
	double alphax;
	double alphay;
	t_v3 text;
	t_entity_thread *thread;

	thread = arg;
	text.z = thread->render.z;
	int y = thread->render.clamp_start.y - 1;
	while (++y < thread->render.clamp_end.y)
	{
		alphay = (y - thread->render.start.y) / thread->render.yrange;
		text.y = (1.0 - alphay) * thread->pos.y1 + alphay * thread->pos.y2;
		int x = thread->render.clamp_start.x - 1;
		while (++x < thread->render.clamp_end.x)
		{
			alphax = (x - thread->render.start.x) / thread->render.xrange;
			text.x = (1.0 - alphax) * thread->pos.x1 + alphax * thread->pos.x2;
			if (thread->bxpm->bpp == 32)
				blit_game_entity32(thread, y * thread->surface->w + x, text);
			else
				blit_game_entity24(thread, y * thread->surface->w + x, text);
		}
	}
	return (1);
}
