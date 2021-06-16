/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ai_rand.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 16:42:13 by nneronin          #+#    #+#             */
/*   Updated: 2021/06/16 17:00:53 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int	ai_track_player(t_doom *doom, t_entity *entity)
{
	double	a;
	double	dist;
	double	speed;

	entity->velocity.x = doom->player.where.x - entity->where.x;
	entity->velocity.y = doom->player.where.y - entity->where.y;
	entity->velocity.z = doom->player.where.z - entity->where.z + doom->player.eye_lvl;
	speed = doom->time.delta *  entity->data->speed;
	if (entity->velocity.x == 0 && entity->velocity.y == 0 && entity->velocity.z == 0)
		return (1);
	dist = space_diagonal(entity->velocity);
	entity->velocity.x *= speed / dist;
   	entity->velocity.y *= speed / dist;
	entity->velocity.z *= (entity->data->flying ? speed / dist : 0);
	return (1);
}

int	ai_rand_move(t_doom *doom, t_entity *entity, int chance, int angle)
{
	double	a;
	double	dist;
	double	speed;

	if ((rand() % 1000) > chance)
		return (0);
	a = (entity->yaw + ((rand() % angle) - angle / 2)) * CONVERT_RADIANS;
	entity->velocity.x = (200 * cos(a));
	entity->velocity.y = (200 * sin(a));
	speed = doom->time.delta *  entity->data->speed;
	if (entity->velocity.x == 0 && entity->velocity.y == 0 && entity->velocity.z == 0)
		return (0);
	dist = space_diagonal(entity->velocity);
	entity->velocity.x *= speed / dist;
   	entity->velocity.y *= speed / dist;
	return (1);
}

int	ai_rand_dodge(t_doom *doom, t_entity *entity, int chance, int angle)
{
	double	a;
	double	dist;
	double	speed;

	if ((rand() % 1000) > chance)
		return (0);
	a = angle_to_point(entity->where, doom->player.where);
	a = (a + ((rand() % angle) - angle / 2)) * CONVERT_RADIANS;

	entity->velocity.x = (200 * cos(a));
	entity->velocity.y = (200 * sin(a));
	speed = doom->time.delta *  entity->data->speed;
	if (entity->velocity.x == 0 && entity->velocity.y == 0 && entity->velocity.z == 0)
		return (0);
	dist = space_diagonal(entity->velocity);
	entity->velocity.x *= speed / dist;
   	entity->velocity.y *= speed / dist;
	entity->velocity.z *= (entity->data->flying ? speed / dist : 0);
	return (1);
}
