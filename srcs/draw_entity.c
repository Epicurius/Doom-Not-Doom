/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_entity.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 10:43:45 by nneronin          #+#    #+#             */
/*   Updated: 2021/07/16 13:06:12 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	sprite_threads(t_doom *doom, t_entity *entity,
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
		thread[y].bxpm = doom->npc_bxpm[entity->type].bxpm;
		thread[y].pos = doom->npc_bxpm[entity->type].pos
		[entity->state][entity->frame][entity->angle];
		thread[y].shooting = doom->player.shooting;
		thread[y].dmg = doom->weapon[doom->player.equiped].damage;
		thread[y].hp = &entity->hp;
		thread[y].center = doom->surface_center;
		tpool_add(&doom->tpool, blit_game_entity, &thread[y]);
	}
}

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
			sprite_threads(doom, entity, thread);
		}
		curr = curr->next;
	}
	tpool_wait(&doom->tpool);
}
