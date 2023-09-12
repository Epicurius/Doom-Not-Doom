/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Niklas Neronin <niklas.neronin@gmail.com>
 */

#include "doom.h"

/*
 *	Check if player is less than 1.0 from neighbour portal.
 *	Hard to put into words, but idea is that the player should never reach the
 *	wall (hitbox can touch the wall).
 *	If player was stading on a cliff and walks less than 1.0 into the lower
 *	sector dont move him down, otherwise he would be to close to the wall.
 */
static int	portal_cliff(t_doom *doom, t_motion *motion, float z, int i)
{
	t_v3	p;
	t_wall	*wall;

	while (++i < doom->sectors[motion->sector].npoints)
	{
		wall = doom->sectors[motion->sector].wall[i];
		if (wall->solid || wall->n == -1)
			continue ;
		p = closest_point_on_segment_v2(motion->where, wall->v1, wall->v2);
		if (point_distance_v2(p.x, p.y, motion->where.x, motion->where.y)
			> DIAMETER)
			continue ;
		if (z <= floor_at(&doom->sectors[wall->n], p))
		{
			if (motion->velocity.z < 0)
				motion->velocity.z = 0;
			return (1);
		}
		if (z + motion->height >= ceiling_at(&doom->sectors[wall->n], p))
		{
			motion->velocity.z = 0;
			return (1);
		}
	}	
	return (0);
}

/*
 *	Checks vertical collision.
 *	Does the entity head hit ceiling.
 *	Is entity falling thru the floor.
 *	p is position, v is velocity, t is time factor, a = acceleration.
 *	p = p + v * t + t * (a + a * t) / 2
 *	v += a * t
 *	NOTE: Jumping into another sector will retain original sector gravity;
 */
int	vertical_collision(t_doom *doom, t_motion *motion, float *temp)
{
	t_fc	pos;

	pos.top = ceiling_at(&doom->sectors[motion->sector], motion->where);
	pos.bot = floor_at(&doom->sectors[motion->sector], motion->where);
	if (pos.top - pos.bot < motion->height)
		return (1);
	if (motion->where.z + motion->height + motion->velocity.z * doom->time.delta
		>= pos.top)
		motion->velocity.z = 0;
	*temp = motion->velocity.z;
	if (motion->flight == FALSE && motion->where.z > pos.bot
		&& !portal_cliff(doom, motion,
			motion->where.z + motion->velocity.z * doom->time.delta, -1))
		*temp -= doom->sectors[motion->sector].gravity * doom->time.delta;
	else
		*temp = motion->velocity.z;
	motion->velocity.z = *temp * doom->time.delta;
	motion->where.z += motion->velocity.z;
	return (0);
}
