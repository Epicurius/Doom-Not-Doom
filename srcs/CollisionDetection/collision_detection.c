/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_detection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 15:32:29 by nneronin          #+#    #+#             */
/*   Updated: 2021/08/10 11:57:26 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

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

int	collision_detection(t_doom *doom, t_motion motion,
	t_v3 *where, t_v3 *velocity)
{
	motion.step = 2;
	motion.where = *where;
	motion.velocity = *velocity;
	if (vertical_collision(doom, &motion))
		return (-1);
	if (!(velocity->x == 0 && velocity->y == 0))
	{
		motion.dest = add_v3(motion.where, motion.velocity);
		reset_sectbool(doom, motion.curr_sect);
		if (!check_solid_surfaces(doom, &motion, motion.curr_sect))
			motion.curr_sect = find_from_sectbool(doom, motion);
		else
			motion.velocity = new_v3(0, 0, motion.velocity.z);
	}
	if (motion.curr_sect == -1)
		return (-1);
	*velocity = motion.velocity;
	*where = add_v3(*where, *velocity);
	if (where->z < floor_at(&doom->sectors[motion.curr_sect], *where))
	{
		velocity->z = 0;
		where->z = floor_at(&doom->sectors[motion.curr_sect], *where);
	}
	return (motion.curr_sect);
}
