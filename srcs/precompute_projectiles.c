/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precompute_projectiles.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 13:12:25 by nneronin          #+#    #+#             */
/*   Updated: 2021/06/16 16:23:24 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int	player_contact(t_doom *doom, t_v3 start, t_v3 dest)
{
	if (point_distance_3d(doom->player.where, dest) <= 5)
	{
		doom->player.hp -= 10;
		return (1);
	}
	if (point_distance_3d(start, dest) > PROJECTILE_MAX_RANGE)
		return (1);
	return (0);
}

static int		vertical_collision(t_doom *doom, t_project *orb, t_v3 dest)
{
	t_sector sector;

	sector = doom->sectors[orb->sector];
	if (dest.z < sector.floor.y || dest.z > sector.ceiling.y)
		return (1);
	orb->where.z += orb->velocity.z;
	return (0);
}

int		projectile_collision(t_doom *doom, t_project *orb, t_v3 dest)
{
	t_collision o;

	o.where				= &orb->where;
	o.velocity			= &orb->velocity;
	o.sector			= &orb->sector;
	o.sectors			= doom->sectors;
	o.hitbox_height		= 5;
	o.hitbox_radius		= 5;
	o.step_height		= 0;
	if (player_contact(doom, orb->start, dest) ||
		vertical_collision(doom, orb, dest) ||
		horizontal_collision(&o, dest))
		return (1);
	return (0);
}

void	precompute_projectiles(t_doom *doom)
{
	t_v3 dest;
	t_list *curr;
	t_project *orb;

	curr = doom->orb;
	while (curr)
	{
		orb = curr->content;
		dest = add_vec(orb->where, orb->velocity);
		if (projectile_collision(doom, orb, dest))
			curr = ft_dellstnode(&doom->orb, curr);
		else
			curr = curr->next;
	}
}
