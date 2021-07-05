/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ai_movement.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 10:41:50 by nneronin          #+#    #+#             */
/*   Updated: 2021/07/05 14:37:44 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int	ai_track_player(t_doom *doom, t_entity *entity)
{
	double	speed;

	speed = doom->time.delta * entity->data->speed;
	speed /= point_distance_v3(doom->player.where, entity->where);
	entity->velocity.x = (doom->player.where.x - entity->where.x) * speed;
	entity->velocity.y = (doom->player.where.y - entity->where.y) * speed;
	if (entity->data->flying)
		entity->velocity.z = (doom->player.where.z + doom->player.eye_lvl
				- entity->where.z) * speed;
	return (1);
}

int	ai_rand_move(t_doom *doom, t_entity *entity, int chance, int angle)
{
	double	a;
	double	speed;

	if ((rand() % 1000) > chance)
		return (0);
	a = (entity->yaw + ((rand() % angle) - angle / 2)) * CONVERT_RADIANS;
	speed = doom->time.delta * entity->data->speed;
	speed /= space_diagonal(new_v3(100 * cos(a), 100 * sin(a), 0));
	entity->velocity.x = (100 * cos(a)) * speed;
	entity->velocity.y = (100 * sin(a)) * speed;
	return (1);
}

int	ai_rand_dodge(t_doom *doom, t_entity *entity, int chance, int angle)
{
	double	a;
	double	speed;

	if ((rand() % 1000) > chance)
		return (0);
	a = angle_to_point_v2(entity->where, doom->player.where);
	a = (a + ((rand() % angle) - angle / 2)) * CONVERT_RADIANS;
	speed = doom->time.delta * entity->data->speed;
	speed /= space_diagonal(new_v3(100 * cos(a), 100 * sin(a), 0));
	entity->velocity.x = (100 * cos(a)) * speed;
	entity->velocity.y = (100 * sin(a)) * speed;
	if (entity->data->flying)
		entity->velocity.z = (doom->player.where.z + doom->player.eye_lvl
				- entity->where.z) * speed;
	return (1);
}

void	ai_movement(t_doom *doom, t_entity *entity)
{
	t_collision	collision;

	collision.where = &entity->where;
	collision.velocity = &entity->velocity;
	collision.sector = &entity->sector;
	collision.sectors = doom->sectors;
	collision.entities = doom->sprite;
	collision.nb_entities = doom->nb.sprites;
	collision.player = 0;
	collision.hitbox_height = entity->data->height;
	collision.hitbox_radius = entity->data->hitbox_radius;
	collision.step_height = 2;
	collision_detection(&collision);
	entity->yaw = angle_to_point_v2(entity->where,
			add_v3(entity->where, entity->velocity));
}
