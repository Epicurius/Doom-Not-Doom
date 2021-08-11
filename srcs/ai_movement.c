/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ai_movement.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 10:41:50 by nneronin          #+#    #+#             */
/*   Updated: 2021/08/11 08:57:49 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
 *	Calculates the velocity for the entity to move towards the player.
 */
int	ai_track_player(t_doom *doom, t_entity *entity)
{
	double	speed;

	speed = doom->time.delta * g_entity_data[entity->type].speed;
	speed /= point_distance_v3(doom->player.where, entity->where);
	entity->velocity.x = (doom->player.where.x - entity->where.x) * speed;
	entity->velocity.y = (doom->player.where.y - entity->where.y) * speed;
	if (g_entity_data[entity->type].flight)
		entity->velocity.z = (doom->player.where.z + doom->player.eyelvl
				- entity->where.z) * speed;
	return (1);
}

/*
 *	Calulates if the entity can random move, and give it x,y velocity.
 */
int	ai_rand_move(t_doom *doom, t_entity *entity, int chance, int angle)
{
	double	a;
	double	speed;

	if ((rand() % 1000) > chance)
		return (0);
	a = (entity->yaw + ((rand() % angle) - angle / 2)) * CONVERT_TO_RADIANS;
	speed = doom->time.delta * g_entity_data[entity->type].speed;
	speed /= space_diagonal(new_v3(100 * cos(a), 100 * sin(a), 0));
	entity->velocity.x = (100 * cos(a)) * speed;
	entity->velocity.y = (100 * sin(a)) * speed;
	return (1);
}

/*
 *	Calclates if the entity can dodge at what angle and gives it velocity.
 */
int	ai_rand_dodge(t_doom *doom, t_entity *entity, int chance, int angle)
{
	double	a;
	double	speed;

	if ((rand() % 1000) > chance)
		return (0);
	a = angle_to_point_v2(entity->where, doom->player.where);
	a = (a + ((rand() % angle) - angle / 2)) * CONVERT_TO_RADIANS;
	speed = doom->time.delta * g_entity_data[entity->type].speed;
	speed /= space_diagonal(new_v3(100 * cos(a), 100 * sin(a), 0));
	entity->velocity.x = (100 * cos(a)) * speed;
	entity->velocity.y = (100 * sin(a)) * speed;
	if (g_entity_data[entity->type].flight)
		entity->velocity.z = (doom->player.where.z + doom->player.eyelvl
				- entity->where.z) * speed;
	return (1);
}

/*
 *	Checks the collision of the entity to its destination, and rotates it.
 */
void	ai_collision(t_doom *doom, t_entity *entity)
{
	t_motion	motion;

	motion.flight = g_entity_data[entity->type].flight;
	motion.height = g_entity_data[entity->type].height;
	motion.sector = entity->sector;
	entity->sector = collision_detection(doom, motion,
			&entity->where, &entity->velocity);
	if (entity->sector < 0)
		entity->state = DEATH;
	else if (entity->velocity.x != 0 || entity->velocity.y != 0)
		entity->yaw = angle_to_point_v2(entity->where,
				add_v3(entity->where, entity->velocity));
}
