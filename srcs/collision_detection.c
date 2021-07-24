/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_detection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 15:32:29 by nneronin          #+#    #+#             */
/*   Updated: 2021/07/24 17:33:26 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

// Player is walking up a slope
// Player is walking down a slope
// Player falling thru floor fix
// If player has reached the cealing.
// Let the player keep on rising/falling.
static int	vertical_collision(t_collision *entity, t_v3 dest)
{
	t_fc		y;
	t_wall		*wall;
	t_sector	*sector;

	sector = &entity->sectors[*entity->sector];
	y.ceiling = get_ceiling_at_pos(sector, *entity->where);
	y.floor = get_floor_at_pos(sector, *entity->where);
	if (y.ceiling - y.floor <= entity->hitbox_height)
		return ((entity->suffocate = 1));
	if ((entity->velocity->z >= 0 && dest.z < y.floor && y.floor - dest.z
			<= entity->step_height)
		|| (entity->velocity->z == 0 && dest.z > y.floor && dest.z - y.floor
			<= entity->step_height)
		|| (entity->velocity->z < 0 && dest.z < y.floor))
	{
		entity->where->z = y.floor;
		return (1);
	}
	else if (entity->velocity->z > 0 && dest.z
		+ entity->hitbox_height > y.ceiling)
		return (1);
	entity->where->z += entity->velocity->z;
	return (0);
}

static int	portal(t_collision *entity, t_sector *sector,
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
// intersect = ft_clamp(point_side_v2(wall->v2, wall->v1, dest), 0, 1);
int	horizontal_collision(t_collision *coll, t_v3 dest, int curr, int i)
{
	int			intersect;
	int			collision;
	t_sector	*sect;
	t_wall		*wall;
	t_v3		point;

	sect = &coll->sectors[*coll->sector];
	while (++i < sect->npoints)
	{
		wall = sect->wall[i];
		point = closest_point_on_segment_v2(dest, wall->v1, wall->v2);
		intersect = intersect_check_v2(*coll->where, dest, wall->v1, wall->v2);
		collision = (point_distance_v2(point.x, point.y, dest.x, dest.y) <= 1);
		if (!collision && !intersect)
			continue ;
		if (wall->solid || (intersect && !portal(coll, sect, wall, dest)))
			return (1);
		if (intersect)
			curr = wall->n;
		else if (collision && !wall->solid && !portal(coll, sect, wall, point))
			return (2);
	}
	coll->where->x += coll->velocity->x;
	coll->where->y += coll->velocity->y;
	*coll->sector = curr;
	return (0);
}

int	collision_detection(t_collision *entity)
{
	t_v3	dest;

	dest = add_v3(*entity->where, *entity->velocity);
	if (entity->player && sprite_collision(entity, dest))
	{
		ft_bzero(&entity->velocity, sizeof(t_v3));
		return (1);
	}
	if (horizontal_collision(entity, dest, *entity->sector, -1))
	{
		entity->velocity->x = 0.0f;
		entity->velocity->y = 0.0f;
	}
	if (vertical_collision(entity, dest))
	{
		entity->velocity->z = 0.0f;
	}
	return (1);
}
