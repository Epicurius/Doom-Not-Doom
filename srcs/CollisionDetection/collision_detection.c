/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_detection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 15:32:29 by nneronin          #+#    #+#             */
/*   Updated: 2021/09/05 06:48:59 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
 *	Find the correct sector from the sectbool list of sectors
 *	that player hitbox has moved through.
 *	If none of the match, check all sectors.
 *	If that fails return -1, to kill the entity.
 */
int	find_from_sectbool(t_doom *doom, t_motion *motion)
{
	int		i;
	t_v3	where;

	i = -1;
	where = add_v3(motion->where, motion->velocity);
	while (++i < doom->nb.sectors)
	{
		if (doom->sectbool[i] && in_sector_area(&doom->sectors[i], where))
			return (i);
	}
	ft_printf("{RED}[ERROR]{RESET}\tWrong Sector\n");
	return (find_sector_no_z(doom->sectors, doom->nb.sectors, where));
}

/*
 *	Check map collision.
 *	Vertical -> Horizontal -> move entity z to be in sector.
 */
int	collision_detection(t_doom *doom, t_motion motion,
		t_v3 *where, t_v3 *velocity)
{
	double	gforce;

	motion.step = 2;
	motion.where = *where;
	motion.velocity = *velocity;
	if (vertical_collision(doom, &motion, &gforce))
		return (-1);
	if (velocity->x || velocity->y)
	{
		motion.dest = add_v3(motion.where, motion.velocity);
		reset_sectbool(doom, motion.sector);
		if (horizontal_collision(doom, &motion))
			return (-1);
	}
	*velocity = motion.velocity;
	*where = add_v3(*where, *velocity);
	velocity->z = gforce;
	if (where->z < floor_at(&doom->sectors[motion.sector], *where))
	{
		where->z = floor_at(&doom->sectors[motion.sector], *where);
		velocity->z = 0;
	}
	return (motion.sector);
}
