/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ai_movement.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 10:41:50 by nneronin          #+#    #+#             */
/*   Updated: 2021/07/05 14:22:39 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

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
