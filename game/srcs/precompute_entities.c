/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Niklas Neronin <niklas.neronin@gmail.com>
 */

#include "doom.h"

/*
 *	Checks if its time for the next frame.
 *	and resets if frame has reached the end of its loop.
 *	But if entity state is DEATH and it reached the end, return 0
 *	so it can be deleted.
 */
static int	frame_animation(t_doom *doom, t_entity *entity)
{
	if (g_entity_data[entity->type].frame_rate[entity->state]
		< doom->time.curr - entity->time)
	{
		entity->frame++;
		entity->time = doom->time.curr;
	}
	if (entity->frame >= doom->eframes[entity->type].nb[entity->state][FRAMES])
	{
		if (entity->state == DEATH)
			return (0);
		entity->frame = 0;
	}
	return (1);
}

/*
 *	Preform the entity state function.
 *	atm only MOVE and ATTACK have a funcition.
 */
static void	preforme_entity_state_fuction(t_doom *doom, t_entity *entity)
{
	if (!g_entity_data[entity->type].type)
		return ;
	if (entity->state != MOVE)
		entity->velocity = new_v3(0, 0, entity->velocity.z);
	ai_collision(doom, entity);
	if (entity->state == ATTACK)
		ai_attack(doom, entity);
}

/*
 *	Get the entity state frame and and angle.
 *	Then get entity projection values.
 */
static int	get_coresponding_entity_state_frame(t_doom *doom, t_entity *entity)
{
	if (doom->eframes[entity->type].nb[entity->state][FRAMES] > 1
		&& !frame_animation(doom, entity))
		return (0);
	entity->angle = orientation(entity->where, doom->player.where, entity->yaw,
			doom->eframes[entity->type].nb[entity->state][ANGLES]);
	project_entity(doom, entity, &entity->render);
	return (1);
}

/*
 *	Pay the man(the player) for killing the entity.
 *	If a Rift was killed swap it with a MedKit.
 */
static int	pay_the_man(t_doom *doom, t_entity *entity)
{
	doom->inv.dosh += 10 + doom->nb.kills;
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
		project_entity(doom, entity, &entity->render);
		return (0);
	}
	return (1);
}

/*
 *	Handles all the entities calculation.
 */
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
