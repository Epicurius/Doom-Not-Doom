/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ai_rand.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 16:42:13 by nneronin          #+#    #+#             */
/*   Updated: 2021/06/17 12:56:57 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int	ai_track_player(t_doom *doom, t_entity *entity)
{
	double	a;
	double	dist;
	double	speed;

	entity->velocity = sub_v3(doom->player.where, entity->where);
	entity->velocity.z += doom->player.eye_lvl;
	speed = doom->time.delta * entity->data->speed;
	if (comp_v3(entity->velocity, new_v3(0, 0, 0)))
		return (1);
	dist = space_diagonal(entity->velocity);
	entity->velocity.x *= speed / dist;
	entity->velocity.y *= speed / dist;
	entity->velocity.z *= speed / dist;
	if (entity->data->flying)
		entity->velocity.z = 0;
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
	speed = doom->time.delta * entity->data->speed;
	if (comp_v3(entity->velocity, new_v3(0, 0, 0)))
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
	a = angle_to_point_v2(entity->where, doom->player.where);
	a = (a + ((rand() % angle) - angle / 2)) * CONVERT_RADIANS;
	entity->velocity.x = (200 * cos(a));
	entity->velocity.y = (200 * sin(a));
	speed = doom->time.delta * entity->data->speed;
	if (comp_v3(entity->velocity, new_v3(0, 0, 0)))
		return (0);
	dist = space_diagonal(entity->velocity);
	entity->velocity.x *= speed / dist;
	entity->velocity.y *= speed / dist;
	entity->velocity.z *= speed / dist;
	if (entity->data->flying)
		entity->velocity.z = 0;
	return (1);
}
