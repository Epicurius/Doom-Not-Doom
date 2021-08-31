/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical_collision.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/01 14:52:17 by nneronin          #+#    #+#             */
/*   Updated: 2021/08/31 11:29:16 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
 *	Check if player is less than 1.0 from neighbour portal.
 *	Hard to put into words, but idea is that the player should never reach the
 *	wall (hitbox can touch the wall).
 *	If player was stading on a cliff and walks less than 1.0 into the lower
 *	sector dont move him down, otherwise he would be to close to the wall.
 */
static int	portal_cliff(t_doom *doom, t_motion *motion, t_v3 pos, int i)
{
	t_v3	p;
	t_wall	*wall;

	while (++i < doom->sectors[motion->sector].npoints)
	{
		wall = doom->sectors[motion->sector].wall[i];
		if (wall->solid || wall->n == -1)
			continue ;
		p = closest_point_on_segment_v2(pos, wall->v1, wall->v2);
		if (point_distance_v2(p.x, p.y, pos.x, pos.y) > DIAMETER)
			continue ;
		if (pos.z + motion->velocity.z * doom->time.delta <= floor_at(&doom->sectors[wall->n], p))
		{
			if (motion->velocity.z < 0)
				motion->velocity.z = 0;
			return (1);
		}
		if (pos.z + motion->velocity.z * doom->time.delta + motion->height
			>= ceiling_at(&doom->sectors[wall->n], p))
		{
			motion->velocity.z = 0;
			return (1);
		}
	}	
	return (0);
}

double	g_force(double velocity, float g, float delta)
{
	return (velocity * delta + delta * (g + g * delta) / 2);
}

//int	vertical_collision(t_doom *doom, t_motion *motion)
//{
//	t_fc			pos;
//	//double			g;
//
//	pos.ceiling = ceiling_at(&doom->sectors[motion->sector], motion->where);
//	pos.floor = floor_at(&doom->sectors[motion->sector], motion->where);
//	if (pos.ceiling - pos.floor < motion->height)
//		return (1);
//	//z = g_force(motion->velocity.z,	doom->sectors[motion->sector].gravity, doom->time.delta);
//	if (motion->flight == FALSE && motion->where.z > pos.floor
//		&& !portal_cliff(doom, motion, motion->where, -1))
//	{
//		//ft_printf("1 %f %f\n", motion->velocity.z, g_force(motion->velocity.z, doom->sectors[motion->sector].gravity, doom->time.delta));
//		//motion->where.z += g_force(motion->velocity.z, doom->sectors[motion->sector].gravity, doom->time.delta);
//		//motion->velocity.z -= doom->sectors[motion->sector].gravity * doom->time.delta;
//
//		//motion->where.z += motion->velocity.z * doom->time.delta
//		//	+ doom->time.delta * (doom->sectors[motion->sector].gravity
//		//		+ doom->sectors[motion->sector].gravity * doom->time.delta) / 2;
//		//motion->velocity.z -= doom->sectors[motion->sector].gravity * doom->time.delta;
//	
//		//if (temp == 0)
//		//	temp = motion->velocity.z;
//		//motion->velocity.z = temp * doom->time.delta
//		//	+ doom->time.delta * (doom->sectors[motion->sector].gravity
//		//		+ doom->sectors[motion->sector].gravity * doom->time.delta) / 2;
//		//temp -= doom->sectors[motion->sector].gravity * doom->time.delta;
//	}
//	//else
//	//{
//	//	ft_printf("2\n");
//	//	motion->where.z += g_force(motion->velocity.z, 0, doom->time.delta);
//	//}
//	if (motion->where.z + motion->velocity.z + motion->height >= pos.ceiling)
//		motion->velocity.z = 0;
//	return (0);
//}

/*
 *	Checks vertical collision.
 *	Does the entity head hit ceiling.
 *	Is entity falling thru the floor.
 *	p is position, v is velocity, t is time factor, a = acceleration.
 *	p = p + v * t + t * (a + a * t) / 2
 *	v += a * t
 *	NOTE: Jumping into another sector will retain original sector gravity;
 */
int	vertical_collision(t_doom *doom, t_motion *motion, double *temp)
{
	t_fc	pos;

	pos.ceiling = ceiling_at(&doom->sectors[motion->sector], motion->where);
	pos.floor = floor_at(&doom->sectors[motion->sector], motion->where);
	if (pos.ceiling - pos.floor < motion->height)
		return (1);
	if (motion->where.z + motion->velocity.z * doom->time.delta + motion->height >= pos.ceiling)
		motion->velocity.z = 0;
	*temp = motion->velocity.z;
	if (motion->flight == FALSE && motion->where.z > pos.floor
		&& !portal_cliff(doom, motion, motion->where, -1))
		*temp -= doom->sectors[motion->sector].gravity * doom->time.delta;
	motion->velocity.z = *temp * doom->time.delta;
	motion->where.z += motion->velocity.z;
	return (0);
}