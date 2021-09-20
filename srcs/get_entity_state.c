/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_entity_state.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 13:53:14 by nneronin          #+#    #+#             */
/*   Updated: 2021/09/20 10:43:10 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
 *	Checks the entity's view cone if the the player is present.
 */
static int	entity_see(t_doom *doom, t_entity *entity)
{
	t_v3	far_left;
	t_v3	far_right;

	far_left.z = entity->yaw + 1.178097;
	far_right.z = entity->yaw - 1.178097;
	//clamp_degrees(&far_left.z);
	//clamp_degrees(&far_right.z);
	//far_left.z = (far_left.z * CONVERT_TO_RADIANS);
	//far_right.z = (far_right.z * CONVERT_TO_RADIANS);
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

/*
 *	Checks it the line of sight ray reaches the player.
 */
int	ray_collision(t_doom *doom, t_v3 enemy, t_v3 player, int sector)
{
	int		i;
	t_wall	*wall;

	i = -1;
	reset_sectbool(doom, sector);
	while (++i < doom->sectors[sector].npoints)
	{
		if (doom->player.sector == sector)
			return (1);
		wall = doom->sectors[sector].wall[i];
		if (wall->n >= 0 && doom->sectbool[wall->n] == FALSE)
		{
			if (doom->player.sector == wall->n)
				return (1);
			doom->sectbool[wall->n] = TRUE;
			if (intersect_v2(enemy, player, wall->v1, wall->v2))
			{
				sector = wall->n;
				i = -1;
			}
		}
	}
	return (0);
}

/*
 *	Checks the entity sees the player.
 */
static int	entity_line_of_sight(t_doom *doom, t_entity *entity, TEMP_DOUBLE dist)
{
	if (dist > g_entity_data[entity->type].view_distance)
		return (0);
	if (dist < g_entity_data[entity->type].detection_radius
		|| entity_see(doom, entity))
	{
		if (doom->player.sector == entity->sector)
			return (1);
		if (ray_collision(doom, entity->where,
				doom->player.where, entity->sector))
			return (2);
	}
	return (0);
}

/*
 *	Gets the state of the entity.
 *	If the entity sees the player and danger try to dodge,
 *	else move into range and preform attack.
 *	If none are true state -> IDLE.
 */
void	get_entity_state2(t_doom *doom, t_entity *entity)
{
	TEMP_DOUBLE	dist;

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

/*
 *	Gets the state of the entity.
 *	If not hp -> DEATH.
 *	Is the not in the players active area -> IDLE.
 *	(To not calculate every entity on the map).
 *	If player is hovering over the entity give it danger flag.
 */
void	get_entity_state(t_doom *doom, t_entity *entity)
{
	if (entity->hp <= 0 && entity->state != DEATH)
	{
		entity->state = DEATH;
		entity->frame = 0;
		entity->time = 0;
	}
	if (g_entity_data[entity->type].type == INANIMATE
		|| entity->state == DEATH || entity->frame)
		return ;
	if (g_entity_data[entity->type].type && entity->render.z > 10
		&& doom->c.x > entity->render.start.x
		&& doom->c.x < entity->render.end.x
		&& doom->c.y > entity->render.start.y
		&& doom->c.y < entity->render.end.y)
		entity->danger = TRUE;
	get_entity_state2(doom, entity);
	entity->danger = FALSE;
}
