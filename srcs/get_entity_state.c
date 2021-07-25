/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_entity_state.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 13:53:14 by nneronin          #+#    #+#             */
/*   Updated: 2021/07/25 09:22:57 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static int	entity_see(t_doom *doom, t_entity *entity)
{
	t_v3	far_left;
	t_v3	far_right;

	far_left.z = entity->yaw + 67.5;
	far_right.z = entity->yaw - 67.5;
	degree_fix(&far_left.z);
	degree_fix(&far_right.z);
	far_left.z = (far_left.z * CONVERT_RADIANS);
	far_right.z = (far_right.z * CONVERT_RADIANS);
	far_left.x = 1000 * cos(far_left.z) + entity->where.x;
	far_left.y = 1000 * sin(far_left.z) + entity->where.y;
	far_right.x = 1000 * cos(far_right.z) + entity->where.x;
	far_right.y = 1000 * sin(far_right.z) + entity->where.y;
	far_left.z = point_side_v2(far_left, entity->where, doom->player.where);
	far_right.z = point_side_v2(entity->where, far_right, doom->player.where);
	if (far_left.z > 0 && far_right.z > 0)
		return (1);
	return (0);
}

static int	entity_line_of_sight(t_doom *doom, t_entity *entity, double dist)
{
	if (dist > g_entity_data[entity->type].view_distance)
		return (0);
	if (dist < g_entity_data[entity->type].detection_radius)
		return (1);
	if (entity_see(doom, entity))
		return (2);
	return (0);
}

void	get_entity_state2(t_doom *doom, t_entity *entity)
{
	double	dist;

	dist = point_distance_v2(entity->where.x, entity->where.y,
			doom->player.where.x, doom->player.where.y);
	if (doom->player.action && dist > g_entity_data[entity->type]
		.view_distance && ai_track_player(doom, entity))
		entity->state = MOVE;
	else if (entity_line_of_sight(doom, entity, dist))
	{
		if (entity->danger && ai_rand_dodge(doom, entity, 900, 110))
			entity->state = MOVE;
		else if (g_entity_data[entity->type].attack_range > dist)
			entity->state = ATTACK;
		else if (ai_track_player(doom, entity))
			entity->state = MOVE;
	}
	else
	{
		if (g_entity_data[entity->type].move
			&& ai_rand_move(doom, entity, 10, 360))
			entity->state = MOVE;
		else
			entity->state = IDLE;
	}
}

void	get_entity_state(t_doom *doom, t_entity *entity)
{
	if (g_entity_data[entity->type].animate && entity->render.z > 10
		&& doom->surface_center.x > entity->render.start.x && doom->surface_center.x < entity->render.end.x
		&& doom->surface_center.y > entity->render.start.y && doom->surface_center.y < entity->render.end.y)
		entity->danger = 1;
	if (entity->hp <= 0 && entity->state != DEATH)
	{
		entity->state = DEATH;
		entity->frame = 0;
		entity->time = 0;
	}
	else if (!g_entity_data[entity->type].animate
		|| entity->state == DEATH || entity->frame)
		return ;
	else
		get_entity_state2(doom, entity);
	entity->danger = 0;
}
