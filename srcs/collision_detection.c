/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_detection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 15:32:29 by nneronin          #+#    #+#             */
/*   Updated: 2021/07/11 15:52:04 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

//	Does player hitbox collide with vetex 1.
//	Does player hitbox collide with vetex 2.
//	Does player hitbox collide with vertex point closest to the wall.
static int	hitbox_collision(t_v3 dest, t_wall *wall, float hitbox_radius)
{
	t_v3	point;

	if (point_distance_v2(wall->v1.x, wall->v1.y, dest.x, dest.y)
		<= hitbox_radius)
		return (1);
	if (point_distance_v2(wall->v2.x, wall->v2.y, dest.x, dest.y)
		<= hitbox_radius)
		return (2);
	point = closest_point_on_segment_v2(dest, wall->v1, wall->v2);
	if (point_distance_v2(point.x, point.y, dest.x, dest.y) <= hitbox_radius)
		return (3);
	return (0);
}

// Player is walking up a slope
// Player is walking down a slope
// Player falling thru floor fix
// If player has reached the cealing.
// Let the player keep on rising/falling.
static int	vertical_collision(t_collision *entity, t_v3 dest)
{
	double		f;
	double		c;
	t_wall		*wall;
	t_sector	*sector;

	sector = &entity->sectors[*entity->sector];
	c = get_ceiling_at_pos(sector,
			new_v3(entity->where->x, entity->where->y, 0));
	f = get_floor_at_pos(sector,
			new_v3(entity->where->x, entity->where->y, 0));
	if ((entity->velocity->z >= 0 && dest.z < f && f - dest.z
			<= entity->step_height)
		|| (entity->velocity->z == 0 && dest.z > f && dest.z - f
			<= entity->step_height)
		|| (entity->velocity->z < 0 && dest.z < f))
	{
		entity->where->z = f;
		return (1);
	}
	else if (entity->velocity->z > 0 && dest.z + entity->hitbox_height > c)
		return (1);
	entity->where->z += entity->velocity->z;
	return (0);
}

static int	fit_in_portal(t_collision *entity, t_sector *sector,
	t_wall *wall, t_v3 dest)
{
	double	portal_top;
	double	portal_bot;

	portal_bot = ft_max(get_floor_at_pos(sector, *entity->where),
			get_floor_at_pos(&entity->sectors[wall->n], dest));
	portal_top = ft_min(get_ceiling_at_pos(sector, *entity->where),
			get_ceiling_at_pos(&entity->sectors[wall->n], dest));
	if (portal_top <= portal_bot + entity->hitbox_height)
		return (0);
	if (portal_top > entity->where->z + entity->hitbox_height
		&& portal_bot <= entity->where->z + entity->step_height)
		return (1);
	return (0);
}

// Dose path intersecta wall.
// Is wall solid || or cant fit through portal to next sector.
// Dose hitbox collide with solid surface
int	horizontal_collision(t_collision *entity, t_v3 dest)
{
	int			i;
	t_wall		*wall;
	t_sector	*sector;

	i = -1;
	sector = &entity->sectors[*entity->sector];
	while (++i < sector->npoints)
	{
		wall = sector->wall[i];
		if (intersect_check_v2(*entity->where, dest, wall->v1, wall->v2))
		{
			if (wall->solid || !fit_in_portal(entity, sector, wall, dest))
				return (1);
			*entity->sector = wall->n;
			break ;
		}
		else if ((wall->solid || !fit_in_portal(entity, sector, wall, dest))
			&& hitbox_collision(dest, wall, entity->hitbox_radius))
		{
			return (1);
		}
	}
	entity->where->x += entity->velocity->x;
	entity->where->y += entity->velocity->y;
	return (0);
}

int	collision_detection(t_collision *entity)
{
	t_v3	dest;

	dest = add_v3(*entity->where, *entity->velocity);
	if (entity->player && sprite_collision(entity, dest))
	{
		entity->velocity->x = 0.0f;
		entity->velocity->y = 0.0f;
		entity->velocity->z = 0.0f;
		return (1);
	}
	if (horizontal_collision(entity, dest))
	{
		entity->velocity->x = 0.0f;
		entity->velocity->y = 0.0f;
	}
	if (vertical_collision(entity, dest))
		entity->velocity->z = 0.0f;
	return (1);
}
