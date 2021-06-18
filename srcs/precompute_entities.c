/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precompute_entities.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 10:53:11 by nneronin          #+#    #+#             */
/*   Updated: 2021/06/18 12:16:10 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int	frame_animation(t_doom *doom, t_entity *entity)
{
	if (entity->data->frame_rate[entity->state] * doom->time.delta
		< doom->time.curr - entity->time)
	{
		entity->frame++;
		entity->time = doom->time.curr;
	}
	if (entity->frame >= doom->npc_bxpm[entity->type].nb[entity->state][FRAMES])
	{
		if (entity->state == DEATH)
			return (0);
		entity->frame = 0;
	}
	return (1);
}

void	get_entity_state(t_doom *doom, t_entity *entity)
{
	if (entity->data->animate && entity->render.z > 10
		&& doom->w2 > entity->render.start.x && doom->w2 < entity->render.end.x
		&& doom->h2 > entity->render.start.y && doom->h2 < entity->render.end.y)
		entity->danger = 1;
	if (entity->hp <= 0 && entity->state != DEATH)
	{
		entity->state = DEATH;
		entity->frame = 0;
		entity->time = 0;
	}
	else if (!entity->data->animate || entity->state == DEATH || entity->frame)
		return ;
	else
		animated_entity_state(doom, entity);
	entity->danger = 0;
}

void	preforme_entity_state_fuction(t_doom *doom, t_entity *entity)
{
	if (entity->state == MOVE)
		ai_movement(doom, entity);
	else if (entity->state == ATTACK)
		ai_attack(doom, entity);
}

int	get_coresponding_entity_state_frame(t_doom *doom, t_entity *entity)
{
	if (doom->npc_bxpm[entity->type].nb[entity->state][FRAMES] > 1
		&& !frame_animation(doom, entity))
		return (0);
	entity->angle = orientation(entity->where, doom->player.where, entity->yaw,
			doom->npc_bxpm[entity->type].nb[entity->state][ANGLES]);
	project_entity(doom, entity);
	return (1);
}

void	precompute_entities(t_doom *doom)
{
	t_list		*curr;

	curr = doom->sprite;
	while (curr != NULL)
	{
		get_entity_state(doom, curr->content);
		preforme_entity_state_fuction(doom, curr->content);
		if (!get_coresponding_entity_state_frame(doom, curr->content))
		{
			curr = ft_dellstnode(&doom->sprite, curr);
			doom->nb.kills += 1;
			doom->nb.sprites -= 1;
			doom->game.spawns -= 1;
		}
		else
			curr = curr->next;
	}
}
