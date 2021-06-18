/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animate.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 10:41:58 by nneronin          #+#    #+#             */
/*   Updated: 2021/06/18 12:14:02 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int	animate_wsprite(t_doom *doom, t_wsprite *sprite)
{
	if (sprite->time - doom->time.curr < -100)
	{
		sprite->src.x1 += 64;
		sprite->frame += 1;
		if (sprite->src.x1 >= doom->mtx[sprite->tx].w)
		{
			sprite->src.x1 = 0;
			sprite->src.y1 += 64;
		}
		if (sprite->frame >= 3 || sprite->src.y1 >= doom->mtx[sprite->tx].h)
		{
			sprite->src.x1 = 0;
			sprite->src.y1 = 0;
			sprite->frame = 0;
		}
		sprite->src.x2 = sprite->src.x1 + 64;
		sprite->src.y2 = sprite->src.y1 + 64;
		sprite->time = doom->time.curr;
	}
	return (1);
}

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
	double	dist;

	dist = point_distance_v2(entity->where.x, entity->where.y,
			doom->player.where.x, doom->player.where.y);
	if (doom->player.shooting && dist > entity->data->view_distance
		&& ai_track_player(doom, entity))
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
