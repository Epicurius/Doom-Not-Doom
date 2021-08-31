/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_detection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 15:32:29 by nneronin          #+#    #+#             */
/*   Updated: 2021/08/31 10:16:55 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
 *	Find the correct sector from the sectbool list of sectors
 *	that player hitbox has moved through.
 *	If none of the match, check all sectors.
 *	If that fales return -1, to kill the entity.
 */
int	find_from_sectbool(t_doom *doom, t_motion motion)
{
	int		i;
	t_v3	where;

	i = -1;
	where = add_v3(motion.where, motion.velocity);
	while (++i < doom->nb.sectors)
	{
		if (doom->sectbool[i] && in_sector_area(&doom->sectors[i], where))
			return (i);
	}
	ft_printf("{RED}[ERROR]{RESET}\tWrong Sector\n");
	return (find_sector_no_z(doom->sectors, doom->nb.sectors, where));
}

//double	gforce(double velocity, float g, float delta)
//{
//	return (velocity * delta + delta * (g + g * delta) / 2);
//}

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
	if (!(velocity->x == 0 && velocity->y == 0))
	{
		motion.dest = add_v3(motion.where, motion.velocity);
		reset_sectbool(doom, motion.sector);
		if (!check_solid_surfaces(doom, &motion, motion.sector))
			motion.sector = find_from_sectbool(doom, motion);
		else
			motion.velocity = new_v3(0, 0, motion.velocity.z);
	}
	if (motion.sector == -1)
		return (-1);
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
//		if (!check_solid_surfaces(doom, &motion, motion.sector))
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