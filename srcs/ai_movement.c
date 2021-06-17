/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ai_movement.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 10:41:50 by nneronin          #+#    #+#             */
/*   Updated: 2021/06/17 10:51:14 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	ai_movement(t_doom *doom, t_entity *entity)
{
	t_collision e;

	e.where			= &entity->where;
	e.velocity		= &entity->velocity;
	e.sector		= &entity->sector;
	e.sectors		= doom->sectors;
	e.entities		= doom->sprite;
	e.nb_entities	= doom->nb.sprites;
	e.player		= 0;
	e.hitbox_height	= entity->data->height;
	e.hitbox_radius	= entity->data->hitbox_radius;
	e.step_height	= 2;
	collision_detection(&e);
	entity->yaw = angle_to_point_v2(entity->where, add_v2(entity->where, entity->velocity));
}
