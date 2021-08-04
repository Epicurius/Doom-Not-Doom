/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precompute_entities.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 10:53:11 by nneronin          #+#    #+#             */
/*   Updated: 2021/08/04 12:07:04 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static int	frame_animation(t_doom *doom, t_entity *entity)
{
	if (g_entity_data[entity->type].frame_rate[entity->state] * doom->time.delta
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

static void	preforme_entity_state_fuction(t_doom *doom, t_entity *entity)
{
	if (!g_entity_data[entity->type].type)
		return ;
	if (entity->state != MOVE)
		entity->velocity = new_v3(0, 0, entity->velocity.z);
	if (!g_entity_data[entity->type].flight)
	{
		if (entity->where.z > floor_at(&doom->sectors[entity->sector],
				entity->where))
			entity->velocity.z -= doom->sectors[entity->sector].gravity;
	}
	ai_collision(doom, entity);
	if (entity->state == ATTACK)
		ai_attack(doom, entity);
}

static int	get_coresponding_entity_state_frame(t_doom *doom, t_entity *entity)
{
	if (doom->npc_bxpm[entity->type].nb[entity->state][FRAMES] > 1
		&& !frame_animation(doom, entity))
		return (0);
	entity->angle = orientation(entity->where, doom->player.where, entity->yaw,
			doom->npc_bxpm[entity->type].nb[entity->state][ANGLES]);
	project_entity(doom, entity, &entity->render);
	return (1);
}

static int	pay_the_man(t_doom *doom, t_entity *entity)
{
	doom->inv.dosh += 10 + doom->nb.kills * 1;
	Mix_PlayChannel(-1, doom->sound[WAV_DOSH], 0);
	doom->nb.kills += 1;
	doom->game.spawns -= 1;
	doom->nb.entities -= 1;
	if (entity->type == RIFT)
	{
		entity->type = MED_KIT;
		entity->hp = g_entity_data[MED_KIT].health;
		entity->state = IDLE;
		entity->frame = 0;
		doom->nb.entities += 1;
		return (0);
	}
	return (1);
}

void	precompute_entities(t_doom *doom)
{
	t_list		*curr;

	curr = doom->entity;
	while (curr != NULL)
	{
		get_entity_state(doom, curr->content);
		preforme_entity_state_fuction(doom, curr->content);
		if (!get_coresponding_entity_state_frame(doom, curr->content))
		{
			if (pay_the_man(doom, curr->content))
				curr = ft_dellstnode(&doom->entity, curr);
			else
				curr = curr->next;
		}
		else
			curr = curr->next;
	}
}
