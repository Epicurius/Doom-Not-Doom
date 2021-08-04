/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precompute_projectiles.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 13:12:25 by nneronin          #+#    #+#             */
/*   Updated: 2021/08/04 09:55:36 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static int	vertical_collision_lite(t_doom *doom, t_projectile *orb)
{
	if (orb->where.z + 2 > ceiling_at(&doom->sectors[orb->sector], orb->where)
		|| orb->where.z < floor_at(&doom->sectors[orb->sector], orb->where))
		return (1);
	return (0);
}

//			Maybe separate horizontal collision without slide?
static int	projectile_collision(t_doom *doom, t_projectile *orb)
{
	t_motion	motion;

	motion.future = add_v3(orb->where, orb->velocity);
	if (target_contact(doom, orb, orb->start, motion.future))
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
	if (horizontal_collision(doom, &motion, FALSE) > 0)
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
