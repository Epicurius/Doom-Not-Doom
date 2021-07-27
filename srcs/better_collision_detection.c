/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   better_collision_detection.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 15:32:29 by nneronin          #+#    #+#             */
/*   Updated: 2021/07/27 17:27:17 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"


int	ss[100];

t_v3	update_move(t_doom *doom, t_v3 *velocity, t_motion motion, int sector, int wall);

int		check_ceiling(t_doom *doom, t_motion motion, int dest_sect)
{
	if (get_ceiling_at_pos(&doom->sectors[dest_sect], motion.future)
		< motion.future.z + motion.eyesight)
		return (0);
	return (1);
}

int		check_floor(t_doom *doom, t_motion motion, int dest_set)
{
	double	floor;

	floor = get_floor_at_pos(&doom->sectors[dest_set], motion.future);
	if (floor > motion.future.z + 2 && dest_set != motion.sector)
		return (0);
	if ((doom->sectors[dest_set].floor_slope != 0
		&& floor > motion.future.z + 1 && dest_set == motion.sector && !motion.flight)
		|| (floor > motion.future.z && dest_set == motion.sector && motion.flight))
		return (0);
	return (1);
}


t_v3	vertical_collision(t_doom *doom, t_v3 velocity, t_motion motion)
{
	if (get_ceiling_at_pos(&doom->sectors[motion.lowest_ceiling], motion.future)
		- get_floor_at_pos(&doom->sectors[motion.sector], motion.future)
			< motion.eyesight + 1)
		return (new_v3(0, 0, 0));
	if (!check_ceiling(doom, motion, motion.lowest_ceiling))
		velocity.z = get_ceiling_at_pos(&doom->sectors[motion.lowest_ceiling],
			motion.where) - 1 - (motion.where.z + motion.eyesight);
	
	if (!check_floor(doom, motion, motion.sector) && motion.flight)
		velocity.z = get_floor_at_pos(&doom->sectors[motion.sector], motion.where)
		- motion.where.z;
	else if (!(check_floor(doom, motion, motion.sector)))
		return (new_v3(0, 0, 0));
	return (velocity);
}

int		cross_wall(t_doom *doom, t_motion motion, t_wall *wall)
{
	t_v3	point;
	int		collision;

	if (!wall->solid && wall->n != -1)
		return (0);
	if (intersect_check_v2(motion.where, motion.future, wall->v1, wall->v2))
		return (1);
	point = closest_point_on_segment_v2(motion.future, wall->v1, wall->v2);
	if (point_distance_v2(point.x, point.y, motion.future.x, motion.future.y) <= 1.0)
		return (1);
	return (0);
}

int		cross_portal(t_doom *doom, t_motion motion, t_wall *wall)
{

	if (wall->solid || wall->n == -1)
		return (0);	
	if (ss[wall->n] == 1)
		return (0);
	if (intersect_check_v2(motion.where, motion.future, wall->v1, wall->v2))
		return (1);
	t_v3 point = closest_point_on_segment_v2(motion.future, wall->v1, wall->v2);
	if (point_distance_v2(point.x, point.y, motion.future.x, motion.future.y) <= 1.0)
		return (1);
	return (0);
}

void	testing_portal(t_doom *doom, t_v3 *velocity, t_motion *motion, int *s, int *v)
{
	if (!check_floor(doom, *motion, doom->sectors[*s].wall[*v]->n)
		|| !check_ceiling(doom, *motion, doom->sectors[*s].wall[*v]->n))
	{
		motion->future = update_move(doom, velocity, *motion, *s, *v);
	}
	else
	{
		*s = doom->sectors[*s].wall[*v]->n;
		*v = -1;
		ss[*s] = 1;
	}
}

t_v3	collision_detection2(t_doom *doom, t_v3 velocity, t_motion motion)
{
	int	i;
	int	sect;
	
	ft_bzero(&ss, sizeof(int) * 100);
	sect = motion.sector;
	ss[sect] = 1;
 	motion.future = add_v3(motion.where, velocity);
	velocity = vertical_collision(doom, velocity, motion);
	if (velocity.x == 0 && velocity.y == 0 && velocity.z == 0)
		return (velocity);
	i = 0;
	while (i < doom->sectors[sect].npoints)
	{
		if (cross_wall(doom, motion, doom->sectors[sect].wall[i]))
			motion.future = update_move(doom, &velocity, motion, sect, i);
		if (cross_portal(doom, motion, doom->sectors[sect].wall[i]))
			testing_portal(doom, &velocity, &motion, &sect, &i);
		if (++i >= doom->sectors[sect].npoints && sect != motion.sector)
		{
			i = 0;
			sect = motion.sector;
		}
		if (velocity.x == 0 && velocity.y == 0)
			break ;
	}
	return (velocity);
}

/* -------------------------------------------------------------------------- */

t_v3	parallel_movement(t_doom *doom, t_v3 velocity, int sect, int i)
{
	double	norm_velocity;
	double	norm_wall;
	double	scalar;
	t_v2	wall;

	wall.x = doom->sectors[sect].wall[i]->v2.x - doom->sectors[sect].wall[i]->v1.x;
	wall.y = doom->sectors[sect].wall[i]->v2.y - doom->sectors[sect].wall[i]->v1.y;
	norm_velocity = pythagoras(velocity.x, velocity.y);
	norm_wall = pythagoras(wall.x, wall.y);
	scalar = wall.x / norm_wall * velocity.x / norm_velocity +
		wall.y / norm_wall * velocity.y / norm_velocity;
	if (scalar != 0)
	{
		velocity.x = norm_velocity * wall.x / norm_wall * scalar;
		velocity.y = norm_velocity * wall.y / norm_wall * scalar;
	}
	else
		return (new_v3(0, 0, 0));
	return (velocity);
}

int		testing_portal_slide(t_doom *doom, t_motion motion, int *s, int *v)
{
	if (!check_floor(doom, motion, doom->sectors[*s].wall[*v]->n)
		|| !check_ceiling(doom, motion, doom->sectors[*s].wall[*v]->n))
		return (0);
	*s = doom->sectors[*s].wall[*v]->n;
	*v = -1;
	ss[*s] = 1;
	return (1);
}

t_v3	check_collision_slide(t_doom *doom, t_v3 velocity, t_motion motion, int sect)
{
	int		i;
	int		o_sect;

	o_sect = sect;
	motion.future = add_v3(motion.where, velocity);
	i = 0;
	while (i < doom->sectors[sect].npoints)
	{
		if (cross_wall(doom, motion, doom->sectors[sect].wall[i]))
			return (new_v3(0, 0, 0));
		if (cross_portal(doom, motion, doom->sectors[sect].wall[i]))
			if (!testing_portal_slide(doom, motion, &sect, &i))
				return (new_v3(0, 0, 0));
		if (++i >= doom->sectors[sect].npoints && sect != o_sect)
		{
			i = 0;
			sect = o_sect;
		}
	}
	return (velocity);
}

t_v3	update_move(t_doom *doom, t_v3 *velocity, t_motion motion, int sector, int wall)
{
	*velocity = parallel_movement(doom, *velocity, sector, wall);
	*velocity = check_collision_slide(doom, *velocity, motion, wall);
	return (add_v3(motion.where, *velocity));
}