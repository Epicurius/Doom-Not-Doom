/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_detection.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 15:32:29 by nneronin          #+#    #+#             */
/*   Updated: 2021/07/30 12:17:28 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int	hitbox_collision(t_v3 p, t_v3 v1, t_v3 v2, double radius)
{
	t_v3	point;

	point = closest_point_on_segment_v2(p, v1, v2);
	if (point_distance_v2(p.x, p.y, v1.x, v1.y) <= radius)
		return (2);
	if (point_distance_v2(p.x, p.y, v2.x, v2.y) <= radius)
		return (2);
	return ((point_distance_v2(point.x, point.y, p.x, p.y) <= radius));
}

int	collision_detection(t_doom *doom, t_motion motion,
	t_v3 *where, t_v3 *velocity)
{
	ft_printf("Anime:%s\n", "coll");
	motion.where = *where;
	motion.velocity = *velocity;
	motion.prev_sect = motion.curr_sect;
	motion.move = new_v3(0.0f, 0.0f, 0.0f);
	if (vertical_collision(doom, &motion))
		return (-1);
	motion.future = add_v3(motion.where, motion.velocity);
	ft_printf("Anime:%d\n", horizontal_collision(doom, &motion, TRUE));
	*velocity = motion.move;
	*where = add_v3(*where, *velocity);
	if (where->z < floor_at(&doom->sectors[motion.curr_sect], *where))
	{
		velocity->z = 0;
		where->z = floor_at(&doom->sectors[motion.curr_sect], *where);
	}
	if (!in_sector(&doom->sectors[motion.curr_sect], *where))
	{
		ft_printf("{RED}[ERROR]{RESET}\tWrong Sector\n");
		motion.curr_sect = find_sector(doom->sectors, doom->nb.sectors, *where);
	}
	ft_printf("Anime:%s\n", "123123");
	return (motion.curr_sect);
}
