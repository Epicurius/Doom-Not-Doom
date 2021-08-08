/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precompute_projectiles.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 13:12:25 by nneronin          #+#    #+#             */
/*   Updated: 2021/08/08 16:08:11 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static int	vertical_collision_lite(t_doom *doom, t_projectile *orb)
{
	if (orb->where.z + orb->velocity.z + 2
		> ceiling_at(&doom->sectors[orb->sector], orb->where)
		|| orb->where.z + orb->velocity.z
		< floor_at(&doom->sectors[orb->sector], orb->where))
		return (1);
	return (0);
}

static int	projectile_collision(t_doom *doom, t_projectile *orb)
{
	t_motion	motion;

	motion.future = add_v3(orb->where, orb->velocity);
	if (target_contact(doom, orb, orb->start, motion.future))
		return (1);
	if (vertical_collision_lite(doom, orb))
		return (2);
	motion.flight = TRUE;
	motion.height = 2;
	motion.curr_sect = orb->sector;
	motion.where = orb->where;
	motion.velocity = orb->velocity;
	motion.prev_sect = motion.curr_sect;
	motion.move = new_v3(0, 0, 0);
	motion.move.z += motion.velocity.z;
	//print_v3("POS: ", motion.where);
	//print_v3("VELO: ", motion.velocity);
	//int asd = horizontal_collision(doom, &motion, FALSE);
	//ft_printf("%d\n", asd)
	//if (asd > 0)
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
		//ft_printf("Is it here?\n");
		if (projectile_collision(doom, orb))
		{
			//ft_printf("DEL?\n");
			doom->nb.projectiles -= 1;
			curr = ft_dellstnode(&doom->orb, curr);
		}
		else
		{
			//ft_printf("NO?\n");
			curr = curr->next;
		}
	}
}
