/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_entity.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 10:43:45 by nneronin          #+#    #+#             */
/*   Updated: 2021/08/28 12:11:23 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
 *	Check if entity is "hitable" if player shooting
 *	and pixel is in the middle of the surface damage the entity.
 */
static void	hit_enemy(t_entity_thread *thread, int coord)
{
	if (thread->hp != NULL && thread->shooting && coord == thread->center.z)
	{
		*thread->hp -= thread->dmg;
		*thread->hm = TRUE;
	}
}

/*
 *	Blit entity to surface.
 */
void	blit_entity(t_entity_thread *thread, int coord, t_v3 text)
{
	Uint32			clr;
	unsigned short	pix;

	if (text.z >= ((double *)thread->surface->userdata)[coord])
		return ;
	pix = thread->bxpm->pix[(int)text.y * thread->bxpm->w + (int)text.x];
	clr = thread->bxpm->clr[pix];
	if (thread->bxpm->bpp == 32)
	{
		if (clr == 0x00000000)
			return ;
		clr = blend_alpha(((Uint32 *)thread->surface->pixels)[coord], clr,
				clr >> 24 & 0xFF);
	}
	else if (clr == 0xFF800080)
		return ;
	((Uint32 *)thread->surface->pixels)[coord] = clr;
	((double *)thread->surface->userdata)[coord] = text.z;
	if (thread->hp != NULL)
		hit_enemy(thread, coord);
}

/*
 *	Mutlythread function that draws a part of the entity to windows surface.
 */
int	draw_entity(void *arg)
{
	t_point			p;
	t_v3			text;
	t_v2			alpha;
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
			blit_entity(thread, p.y * thread->surface->w + p.x, text);
		}
	}
	return (1);
}

/*
 *	Prepares the entity frame to be multy threaded.
 *	Split the frame iono its y axis in to 5 pieces.
 *	Add them to tpool.
 */
static void	entity_threads(t_doom *doom, t_entity *entity,
	t_entity_thread *thread)
{
	int	y;
	int	i;

	y = -1;
	i = (entity->render.clamp_end.y - entity->render.clamp_start.y) / 5;
	while (++y < 5)
	{
		thread[y].render = entity->render;
		thread[y].render.clamp_start.y += i * y;
		thread[y].render.clamp_end.y = thread[y].render.clamp_start.y + i;
		if (y == 5 - 1)
			thread[y].render.clamp_end.y = entity->render.clamp_end.y;
		thread[y].surface = doom->surface;
		thread[y].bxpm = doom->eframes[entity->type].bxpm;
		thread[y].pos = doom->eframes[entity->type].pos
		[entity->state][entity->frame][entity->angle];
		thread[y].shooting = doom->player.action;
		thread[y].dmg = doom->weapon[doom->player.equiped].damage;
		thread[y].hp = &entity->hp;
		thread[y].hm = &doom->player.hm;
		thread[y].center = doom->c;
		tpool_add(&doom->tpool, draw_entity, &thread[y]);
	}
}

/*
 *	Draw entities if visible and not closer that 0.3
 */
void	draw_entities(t_doom *doom)
{
	t_list			*curr;
	t_entity		*entity;
	t_entity_thread	thread[5];

	curr = doom->entity;
	while (curr != NULL)
	{
		entity = curr->content;
		if (doom->sectors[entity->sector].visible && entity->render.z > 0.3)
		{
			tpool_wait(&doom->tpool);
			entity_threads(doom, entity, thread);
		}
		curr = curr->next;
	}
	tpool_wait(&doom->tpool);
}
