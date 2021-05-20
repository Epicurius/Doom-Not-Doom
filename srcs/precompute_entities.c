/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precompute_entities.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 10:53:11 by nneronin          #+#    #+#             */
/*   Updated: 2021/05/20 17:09:16 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int	frame_animation(t_doom *doom, t_entity *entity)
{
	if (entity->time - doom->time.curr < -(entity->data->frame_rate[entity->state]))
	{
		entity->frame++;
		entity->time = doom->time.curr;
	}
	if (entity->frame >= doom->sheet[entity->type].nb[entity->state][FRAMES])
	{
		if (entity->state == DEATH)
		{
			doom->nb.kills += 1;
			return (0);
		}
		entity->frame = 0;
	}
	return (1);
}

int		entity_see(t_doom *doom, t_entity *entity)
{
	t_xyz	far_left;
	t_xyz	far_right;

	far_left.z	= entity->yaw + 67.5;
	far_right.z	= entity->yaw - 67.5;
	far_left.z	-= far_left.z > 360 ? 360 : 0;
	far_right.z	+= far_right.z < 0 ? 360 : 0;
	far_left.z	= (far_left.z * CONVERT_RADIANS);
	far_right.z	= (far_right.z * CONVERT_RADIANS);
	far_left.x	= 1000 * cos(far_left.z)  + entity->where.x;
	far_left.y	= 1000 * sin(far_left.z)  + entity->where.y;
	far_right.x	= 1000 * cos(far_right.z) + entity->where.x;
	far_right.y	= 1000 * sin(far_right.z) + entity->where.y;
	far_left.z	= point_side(far_left, entity->where, doom->player.where);
	far_right.z	= point_side(entity->where, far_right, doom->player.where);
	if (far_left.z > 0 && far_right.z > 0)
		return (1);
	return (0);
}

int		entity_line_of_sight(t_doom *doom, t_entity *entity, double dist)
{
	if (dist > entity->data->view_distance)
		return (0);
	if (dist < entity->data->detection_radius)
		return (1);
	if (entity_see(doom, entity))
		return (2);
	return (0);
}

void	animated_entity_state(t_doom *doom, t_entity *entity)
{
	double dist;

	dist = point_distance_2d(entity->where.x, entity->where.y,
							doom->player.where.x, doom->player.where.y);
	if (entity_line_of_sight(doom, entity, dist))
	{
		///if (entity->danger && ai_rand_move(entity, rand() % 40000))
		//	entity->state = MOVE;
		if (entity->data->attack_range > dist)
			entity->state = ATTACK;
		else
		{
			entity->dest = doom->player.where;
			entity->dest.z += EYE_LVL;
			entity->state = MOVE;
		}
	}
	else
	{
		if (entity->data->wonder_distance > 0 && ai_rand_move(entity, rand() % 40000))
			entity->state = MOVE;
		else
			entity->state = IDLE;
	}
}

void	get_entity_state(t_doom *doom, t_entity *entity)
{
	if (entity->hp <= 0 && entity->state != DEATH)
	{
		entity->state = DEATH;
		entity->frame = 0;
		entity->time = 0;
	}
	else if (entity->frame)// || !compare_xyz(entity->where, entity->dest))
		return ;
	else if (!entity->data->animate)
		return ;
	else
		animated_entity_state(doom, entity);
}

void	preforme_entity_state_fuction(t_doom *doom, t_entity *entity)
{
	if (entity->state == MOVE)
		ai_movement(doom, entity);
	else if (entity->state == ATTACK)
		ai_attack(doom, entity);
}

int		get_coresponding_entity_state_frame(t_doom *doom, t_entity *entity)
{
	if (doom->sheet[entity->type].nb[entity->state][FRAMES] > 1)
			if (!frame_animation(doom, entity))
				return (0);
	entity->angle = orientation(entity->where, doom->player.where,
		entity->yaw, doom->sheet[entity->type].nb[entity->state][ANGLES]);
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
		if (!(get_coresponding_entity_state_frame(doom, curr->content)))
		{
			curr = ft_dellstnode(&doom->sprite, curr);
			doom->nb.sprites -= 1;
			doom->game.spawns -= 1;
		}
		else
			curr = curr->next;
	}
}
