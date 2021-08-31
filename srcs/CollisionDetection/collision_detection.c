/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_detection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 15:32:29 by nneronin          #+#    #+#             */
/*   Updated: 2021/08/31 11:52:09 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"


/*
 *	Check map collision.
 *	Vertical -> Horizontal -> move entity z to be in sector.
 */
int	collision_detection(t_doom *doom, t_motion motion,
	t_v3 *where, t_v3 *velocity)
{
	double temp;
	
	motion.step = 2;
	motion.where = *where;
	motion.velocity = *velocity;
	if (vertical_collision(doom, &motion, &temp))
		return (-1);
	if (velocity->x || velocity->y)
	{
		motion.dest = add_v3(motion.where, motion.velocity);
		reset_sectbool(doom, motion.sector);
		if (horizontal_collision(doom, &motion, motion.sector))
			return (-1);
	}
	*velocity = motion.velocity;
	*where = add_v3(*where, *velocity);	
	velocity->z = temp;
	if (where->z < floor_at(&doom->sectors[motion.sector], *where))
	{
		velocity->z = 0;
		where->z = floor_at(&doom->sectors[motion.sector], *where);
	}
	return (motion.sector);
}

//int	collision_detection1(t_doom *doom, t_motion motion,
//	t_v3 *where, t_v3 *velocity)
//{
//	motion.step = 2;//fix
//	motion.where = *where;
//	motion.velocity = *velocity;
//	if (1)
//	{
//		if (vertical_collision(doom, &motion))
//			return (-1);
//		velocity->z = motion.velocity.z;
//		where->z = motion.where.z;
//		
//	}
//	if (!(velocity->x == 0 && velocity->y == 0))
//	{
//		motion.dest.x = motion.where.x + motion.velocity.x;
//		motion.dest.z = motion.where.z;
//		motion.dest.y = motion.where.y + motion.velocity.y;
//		reset_sectbool(doom, motion.sector);
//		if (!horizontal_collision(doom, &motion, motion.sector))
//		{
//			motion.sector = find_from_sectbool(doom, motion);
//			velocity->x = motion.velocity.x;
//			velocity->y = motion.velocity.y;
//			where->x += velocity->x;
//			where->y += velocity->y;
//		}
//	}
//	if (motion.sector == -1)
//		return (-1);
//	//*velocity = motion.velocity;
//	//*where = add_v3(*where, *velocity);
//	if (where->z < floor_at(&doom->sectors[motion.sector], *where))
//	{
//		velocity->z = 0;
//		where->z = floor_at(&doom->sectors[motion.sector], *where);
//	}
//	//ft_printf("%f\n", where->z);
//	return (motion.sector);
//}