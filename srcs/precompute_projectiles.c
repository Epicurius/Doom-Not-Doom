/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precompute_projectiles.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 13:12:25 by nneronin          #+#    #+#             */
/*   Updated: 2021/08/09 11:09:11 by nneronin         ###   ########.fr       */
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

static int	portal_intersect_lite(t_doom *doom, t_motion *motion, t_wall *wall)
{
	t_v3	point;
	double	portal_top;
	double	portal_bot;

	point = closest_point_on_segment_v2(motion->where, wall->v1, wall->v2);
	portal_bot = ft_max(floor_at(&doom->sectors[motion->curr_sect], point),
			floor_at(&doom->sectors[wall->n], point));
	portal_top = ft_min(ceiling_at(&doom->sectors[motion->curr_sect], point),
			ceiling_at(&doom->sectors[wall->n], point));
	if (portal_top <= portal_bot + motion->height)
		return (0);
	if (portal_top > motion->where.z + motion->height
		&& portal_bot <= motion->where.z + STEP_HEIGHT)
	{
		motion->move.x += point.x - motion->where.x;
		motion->move.y += point.y - motion->where.y;
		motion->where.x = point.x;
		motion->where.y = point.y;
		motion->velocity.x = motion->future.x - motion->where.x;
		motion->velocity.y = motion->future.y - motion->where.y;
		doom->sectbool[motion->curr_sect] = TRUE;
		motion->curr_sect = wall->n;
		return (1);
	}
	return (0);
}

//	If issuess re-enable solid corner check
static int	horizontal_collision_lite(t_doom *doom, t_motion *motion)
{
	int		i;
	t_wall	*wall;

	i = -1;
	while (++i < doom->sectors[motion->curr_sect].npoints)
	{
		wall = doom->sectors[motion->curr_sect].wall[i];
		if ((wall->solid || wall->n == -1) && intersect_v2(
				motion->where, motion->future, wall->v1, wall->v2))
			return (1);
	}
	i = -1;
	while (++i < doom->sectors[motion->curr_sect].npoints)
	{
		wall = doom->sectors[motion->curr_sect].wall[i];
		if (!wall->solid && wall->n != -1 && doom->sectbool[wall->n] != TRUE
			&& intersect_v2(motion->where, motion->future, wall->v1, wall->v2)
			&& portal_intersect_lite(doom, motion, wall))
		{
			horizontal_collision_lite(doom, motion);
			return (-1);
		}
	}
	motion->move.x += motion->velocity.x;
	motion->move.y += motion->velocity.y;
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
	motion.move = new_v3(0, 0, 0);
	motion.move.z += motion.velocity.z;
	ft_bzero(doom->sectbool, sizeof(int) * doom->nb.sectors);
	doom->sectbool[motion.curr_sect] = TRUE;
	if (horizontal_collision_lite(doom, &motion) > 0)
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
		//ft_printf("PROJECTLE Is it here?\n");
		if (projectile_collision(doom, orb))
		{
			//ft_printf("PROJECTLE DEL?\n");
			doom->nb.projectiles -= 1;
			curr = ft_dellstnode(&doom->orb, curr);
		}
		else
		{
			//ft_printf("PROJECTLE NO?\n");
			curr = curr->next;
		}
	}
}
