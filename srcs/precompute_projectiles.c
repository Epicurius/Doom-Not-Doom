/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precompute_projectiles.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 13:12:25 by nneronin          #+#    #+#             */
/*   Updated: 2021/07/31 12:02:51 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int	player_contact(t_doom *doom, t_v3 start, t_v3 dest)
{
	if (point_distance_v3(doom->player.where, dest) <= 5)
	{
		doom->player.health -= 10;
		return (1);
	}
	if (point_distance_v3(start, dest) > PROJECTILE_MAX_RANGE)
		return (1);
	return (0);
}

static int	vertical_collision_lite(t_doom *doom, t_projectile *orb)
{
	if (orb->where.z + 2 > ceiling_at(&doom->sectors[orb->sector], orb->where)
		|| orb->where.z < floor_at(&doom->sectors[orb->sector], orb->where))
		return (1);
	return (0);
}

static int	projectile_collision(t_doom *doom, t_projectile *orb)
{
	t_motion	motion;

	motion.future = add_v3(orb->where, orb->velocity);
	if (player_contact(doom, orb->start, motion.future))
		return (1);
	if (vertical_collision_lite(doom, orb))
		return (2);
	motion.flight = 1;
	motion.height = 2;
	motion.curr_sect = orb->sector;
	motion.where = orb->where;
	motion.velocity = orb->velocity;
	motion.prev_sect = motion.curr_sect;
	motion.move = new_v3(0.0f, 0.0f, 0.0f);
	motion.move.z += motion.velocity.z;
	if (horizontal_collision(doom, &motion) > 0)
		return (3);
	orb->where = add_v3(orb->where, motion.move);
	orb->sector = motion.curr_sect;
	if (!in_sector(&doom->sectors[orb->sector], orb->where))
		return (4);
	return (0);
}

void	precompute_projectiles(t_doom *doom)
{
	t_list			*curr;
	t_projectile	*orb;

	curr = doom->orb;
	while (curr)
	{
		orb = curr->content;
		if (projectile_collision(doom, orb))
		{
			doom->nb.projectiles -= 1;
			curr = ft_dellstnode(&doom->orb, curr);
		}
		else
			curr = curr->next;
	}
}
