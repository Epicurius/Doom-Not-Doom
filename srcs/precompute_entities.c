/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precompute_entities.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 10:53:11 by nneronin          #+#    #+#             */
/*   Updated: 2021/05/23 18:43:31 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int	frame_animation(t_doom *doom, t_entity *entity)
{
	if (doom->time.curr - entity->time > entity->data->frame_rate[entity->state] * doom->time.delta)
	{
		entity->frame++;
		entity->time = doom->time.curr;
	}
	if (entity->frame >= doom->sheet[entity->type].nb[entity->state][FRAMES])
	{
		if (entity->state == DEATH)
			return (0);
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
/*
int	ai_track_player(t_doom *doom, t_entity *entity)
{
	entity->dest = doom->player.where;
	entity->dest.z += EYE_LVL;
	return (1);
}
*/
void	animated_entity_state(t_doom *doom, t_entity *entity)
{
	double dist;

	dist = point_distance_2d(entity->where.x, entity->where.y,doom->player.where.x, doom->player.where.y);
	if (doom->player.shooting && dist > entity->data->view_distance && ai_track_player(doom, entity))
		entity->state = MOVE;
	else if (entity_line_of_sight(doom, entity, dist))
	{
		if (entity->danger && ai_rand_dodge(doom, entity, 900, 110))
			entity->state = MOVE;
		else if (entity->data->attack_range > dist)
			entity->state = ATTACK;
		else if (ai_track_player(doom, entity))
			entity->state = MOVE;
	}
	else
	{
		if (entity->data->move && ai_rand_move(doom, entity, 10, 360))
			entity->state = MOVE;
		else
			entity->state = IDLE;
	}
}

void	get_entity_render(t_doom *doom, t_entity *entity)
{
	t_i2	size;
	t_xyz	dist;
	t_xyz	screen;

	dist.x = entity->where.x - doom->player.where.x;
	dist.y = entity->where.z - doom->player.where.z - EYE_LVL;
	dist.z = entity->where.y - doom->player.where.y;
	screen.x = dist.x * doom->player.anglesin - dist.z * doom->player.anglecos;
	screen.z = dist.x * doom->player.anglecos + dist.z * doom->player.anglesin;
	screen.y = dist.y + screen.z * doom->player.pitch;
	screen.x = doom->w2 + (screen.x * doom->cam.scale / -screen.z);
	screen.y = doom->h2 + (screen.y * doom->cam.scale / -screen.z);
	size.x = doom->sheet[entity->type].pos[entity->state][entity->frame][entity->angle].w
		* entity->data->scale / screen.z;
	size.y = doom->sheet[entity->type].pos[entity->state][entity->frame][entity->angle].h
		* entity->data->scale / screen.z;
	entity->render.z = screen.z;
	entity->render.start.x			= screen.x - size.x / 2;
	entity->render.end.x			= screen.x + size.x / 2;
	entity->render.start.y			= screen.y - size.y;
	entity->render.end.y			= screen.y;
	entity->render.clamp_start.x	= ft_clamp(entity->render.start.x, 0, doom->surface->w - 1);
	entity->render.clamp_end.x		= ft_clamp(entity->render.end.x,   0, doom->surface->w - 1);
	entity->render.clamp_start.y	= ft_clamp(entity->render.start.y, 0, doom->surface->h - 1);
	entity->render.clamp_end.y		= ft_clamp(entity->render.end.y,   0, doom->surface->h - 1);
	entity->render.xrange			= entity->render.end.x - entity->render.start.x;
	entity->render.yrange			= entity->render.end.y - entity->render.start.y;
}

void	get_entity_state(t_doom *doom, t_entity *entity)
{

	if (entity->render.z > 10
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

int		get_coresponding_entity_state_frame(t_doom *doom, t_entity *entity)
{
	if (doom->sheet[entity->type].nb[entity->state][FRAMES] > 1 && !frame_animation(doom, entity))
		return (0);
	entity->angle = orientation(entity->where, doom->player.where,
		entity->yaw, doom->sheet[entity->type].nb[entity->state][ANGLES]);
	get_entity_render(doom, entity);
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
