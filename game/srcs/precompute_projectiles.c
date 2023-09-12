/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Niklas Neronin <niklas.neronin@gmail.com>
 */

#include "doom.h"

/*
 *	A simple version of vertical collision.
 *	Projectile cant chenche its velocity after start,
 *	so it need only a simple vertical collision check.
 */
static int	vertical_collision_lite(t_doom *doom, t_projectile *orb)
{
	if (orb->where.z > ceiling_at(&doom->sectors[orb->sector], orb->where)
		|| orb->where.z < floor_at(&doom->sectors[orb->sector], orb->where))
		return (1);
	return (0);
}

/*
 *	Handles projectile collision. Entity contace -> veertical -> horizontal
 *	return (0) is projectile wil continue.
 */
static int	projectile_collision(t_doom *doom, t_projectile *orb)
{
	t_motion	motion;

	motion.where = orb->where;
	motion.velocity = mult_v3(orb->velocity, doom->time.delta);
	motion.dest = add_v3(motion.where, motion.velocity);
	if (target_contact(doom, orb, orb->start, motion.dest))
		return (1);
	if (vertical_collision_lite(doom, orb))
		return (2);
	motion.flight = TRUE;
	motion.height = 1;
	motion.step = 0;
	reset_sectbool(doom, orb->sector);
	if (check_solid_surfaces_no_slide(doom, &motion, orb->sector))
		return (3);
	motion.sector = find_from_sectbool(doom, &motion);
	if (motion.sector == -1)
		return (4);
	orb->where = add_v3(motion.where, motion.velocity);
	orb->sector = motion.sector;
	return (0);
}

/*
 *	Check all projectiles paths one collides then delets it.
 */
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
