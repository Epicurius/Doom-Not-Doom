/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_detection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 15:32:29 by nneronin          #+#    #+#             */
/*   Updated: 2021/06/17 13:40:38 by nneronin         ###   ########.fr       */
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
static int	vertical_collision(t_collision *sprite, t_v3 dest)
{
	double		f;
	double		c;
	t_wall		*wall;
	t_sector	*sector;

	sector = &sprite->sectors[*sprite->sector];
	c = get_ceiling_at_pos(sector,
			new_v3(sprite->where->x, sprite->where->y, 0));
	f = get_floor_at_pos(sector,
			new_v3(sprite->where->x, sprite->where->y, 0));
	if ((sprite->velocity->z >= 0 && dest.z < f && f - dest.z
			<= sprite->step_height)
		|| (sprite->velocity->z == 0 && dest.z > f && dest.z - f
			<= sprite->step_height)
		|| (sprite->velocity->z < 0 && dest.z < f))
	{
		sprite->where->z = f;
		return (1);
	}
	else if (sprite->velocity->z > 0 && dest.z + sprite->hitbox_height > c)
		return (1);
	sprite->where->z += sprite->velocity->z;
	return (0);
}

static int	fit_in_portal(t_collision *sprite, t_sector *sector,
	t_wall *wall, t_v3 dest)
{
	double	portal_top;
	double	portal_bot;

	portal_bot = ft_max(get_floor_at_pos(sector, *sprite->where),
			get_floor_at_pos(&sprite->sectors[wall->n], dest));
	portal_top = ft_min(get_ceiling_at_pos(sector, *sprite->where),
			get_ceiling_at_pos(&sprite->sectors[wall->n], dest));
	if (portal_top <= portal_bot + sprite->hitbox_height)
		return (0);
	if (portal_top > sprite->where->z + sprite->hitbox_height
		&& portal_bot <= sprite->where->z + sprite->step_height)
		return (1);
	return (0);
}

// Dose path intersecta wall.
// Is wall solid || or cant fit through portal to next sector.
// Dose hitbox collide with solid surface
int	horizontal_collision(t_collision *sprite, t_v3 dest)
{
	int			i;
	t_wall		*wall;
	t_sector	*sector;

	i = -1;
	sector = &sprite->sectors[*sprite->sector];
	while (++i < sector->npoints)
	{
		wall = sector->wall[i];
		if (intersect_check_v2(*sprite->where, dest, wall->v1, wall->v2))
		{
			if (wall->solid || !fit_in_portal(sprite, sector, wall, dest))
				return (1);
			*sprite->sector = wall->n;
			break ;
		}
		else if ((wall->solid || !fit_in_portal(sprite, sector, wall, dest))
			&& hitbox_collision(dest, wall, sprite->hitbox_radius))
		{
			return (1);
		}
	}
	sprite->where->x += sprite->velocity->x;
	sprite->where->y += sprite->velocity->y;
	return (0);
}

int	collision_detection(t_collision *sprite)
{
	t_v3	dest;

	dest = add_v3(*sprite->where, *sprite->velocity);
	if (sprite->player && sprite_collision(sprite, dest))
	{
		sprite->velocity->x = 0.0f;
		sprite->velocity->y = 0.0f;
		sprite->velocity->z = 0.0f;
		return (1);
	}
	if (horizontal_collision(sprite, dest))
	{
		sprite->velocity->x = 0.0f;
		sprite->velocity->y = 0.0f;
	}
	if (vertical_collision(sprite, dest))
		sprite->velocity->z = 0.0f;
	return (1);
}
