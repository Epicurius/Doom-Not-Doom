/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_detection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 15:32:29 by nneronin          #+#    #+#             */
/*   Updated: 2021/04/24 15:33:04 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int	vertical_collision(t_collision *sprite, t_xyz dest)
{
	t_game_sector sector;

	sector = sprite->sectors[*sprite->sector];
	// So to not keep on falling through floor.
	if (sprite->velocity->z < 0 && dest.z < sector.floor.y)
	{
		sprite->where->z = sector.floor.y;
		return (1);
	}
	// If player has reached the cealing.
	else if (sprite->velocity->z > 0 && dest.z + sprite->hitbox_height > sector.ceiling.y)
		return (1);
	// Let the player keep on rising/falling.
	sprite->where->z += sprite->velocity->z;
	return (0);
}

int	hitbox_collision(t_xyz dest, t_game_wall *wall, float hitbox_radius)
{
	t_xyz point;

	//Dose player hitbox collide with vetex 1.
	if (point_distance_2d(wall->v1.x, wall->v1.y, dest.x, dest.y) <= hitbox_radius)
		return (1);
	//Dose player hitbox collide with vetex 2.
	if (point_distance_2d(wall->v2.x, wall->v2.y, dest.x, dest.y) <= hitbox_radius)
		return (2);
	point = closest_point_on_segment_2d(dest, wall->v1, wall->v2);
	//Dose player hitbox collide with vertex point closest to the wall.
	if (point_distance_2d(point.x, point.y, dest.x, dest.y) <= hitbox_radius)
		return (3);
	return (0);
}

int	fit_through_portal(t_collision *sprite, t_game_sector *sector, t_game_wall *wall)
{
	double portal_top;
	double portal_bot;

	portal_bot = ft_max(sector->floor.y, sprite->sectors[wall->n].floor.y);
	portal_top = ft_min(sector->ceiling.y, sprite->sectors[wall->n].ceiling.y);
	if (portal_top <= portal_bot + sprite->hitbox_height)
		return (0);
	if (portal_top > sprite->where->z + sprite->hitbox_height &&
		portal_bot <= sprite->where->z + sprite->step_height)
		return (1);
	return (0);
}

int	horizontal_collision(t_collision *sprite, t_xyz dest)
{
	int i;
	t_game_wall *wall;
	t_game_sector *sector;

	i = -1;
	sector = &sprite->sectors[*sprite->sector];
	while (++i < sector->npoints)
	{
		wall = sector->wall[i];
		// Dose path intersecta wall.
		if (intersect_check(*sprite->where, dest, wall->v1, wall->v2))
		{
			// Is wall solid.
			if (wall->solid)
				return (1);
			// Can fit through portal to next sector.
			if (!fit_through_portal(sprite, sector, wall))
				return (1);
			*sprite->sector = wall->n;
			break ;
		}
		// Dose hitbox collide with solid surface
		else if ((wall->solid || !fit_through_portal(sprite, sector, wall))
			&& hitbox_collision(dest, wall, sprite->hitbox_radius))
			return (1);
	}
	sprite->where->x += sprite->velocity->x;
	sprite->where->y += sprite->velocity->y;
	return (0);
}

int	collision_detection(t_collision *sprite)
{
	t_xyz	dest;

	dest = sum_xyz(*sprite->where, *sprite->velocity);
	if (sprite->player && sprite_collision(sprite, dest))
	{
		sprite->velocity->x = 0;
		sprite->velocity->y = 0;
		sprite->velocity->z = 0;
		return (1);
	}
	if (vertical_collision(sprite, dest))
		sprite->velocity->z = 0;
	if (horizontal_collision(sprite, dest))
	{
		sprite->velocity->x = 0;
		sprite->velocity->y = 0;
	}
	return (1);
}
