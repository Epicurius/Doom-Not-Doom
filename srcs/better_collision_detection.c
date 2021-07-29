/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   better_collision_detection.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 15:32:29 by nneronin          #+#    #+#             */
/*   Updated: 2021/07/29 11:25:43 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

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
		- get_floor_at_pos(&doom->sectors[motion.sector], motion.future) < motion.eyesight + 1)
		return (new_v3(0, 0, 0));
		
	if (!check_ceiling(doom, motion, motion.lowest_ceiling))
		velocity.z = get_ceiling_at_pos(&doom->sectors[motion.lowest_ceiling],
			motion.where) - 1 - (motion.where.z + motion.eyesight);
	
	if (!check_floor(doom, motion, motion.sector) && motion.flight)
		velocity.z = get_floor_at_pos(&doom->sectors[motion.sector], motion.where) - motion.where.z;
	if (!(check_floor(doom, motion, motion.sector)))
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
	if (doom->sect_list[wall->n])
		return (0);
	//ft_printf("%d\n", wall->n);
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
		doom->sect_list[*s] = 1;
	}
}

t_v3	better_collision_detection(t_doom *doom, t_v3 velocity, t_motion motion)
{
	int	i;
	int	sect;
	
	ft_bzero(&doom->sect_list, sizeof(int) * 100);
	sect = motion.sector;
	doom->sect_list[sect] = 1;
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
	doom->player.sector = sect;
	return (velocity);
}


/* -------------------------------------------------------------------------- */
/* -------------------------------------------------------------------------- */
/* -------------------------------------------------------------------------- */
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
	doom->sect_list[*s] = 1;
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

/*
** Returns the distance between two points in two dimensions
** x1 y1 are the coordinates of the first point
** x2 y2 are the coordinates of the second point
*/

double	distance_two_points_2d(double x1, double y1, double x2, double y2)
{
	double	d;
	double	x_sub;
	double	y_sub;

	x_sub = x2 - x1;
	y_sub = y2 - y1;
	d = sqrt(x_sub * x_sub + y_sub * y_sub);
	return (d);
}

int		point_on_segment(t_v3 v1, t_v3 v2, t_v3 p)
{
	double d1;
	double d2;
	double linelen;
	double buffer;

	d1 = distance_two_points_2d(p.x, p.y, v1.x, v1.y);
	d2 = distance_two_points_2d(p.x, p.y, v2.x, v2.y);
	linelen = distance_two_points_2d(v1.x, v1.y, v2.x, v2.y);
	buffer = 0.1;
	if (d1 + d2 >= linelen - buffer && d1 + d2 <= linelen + buffer)
		return (1);
	return (0);
}


/*
**	Checks if there's an intersection between a circle and a segment
**	v1 and v2 being the two extremities of the circle
**	p being the center of the circle, size being the radius of the circle
** The function returns 1 if there's an intersection
*/

int		hitbox_collision2(t_v3 p, t_v3 v1, t_v3 v2, double radius)
{
	double	len;
	double	dot;
	double	closestx;
	double	closesty;
	double	distance;

	if (distance_two_points_2d(v1.x, v1.y, p.x, p.y) <= radius ||
		distance_two_points_2d(v2.x, v2.y, p.x, p.y) <= radius)
		return (1);
	len = distance_two_points_2d(v1.x, v1.y, v2.x, v2.y);
	dot = (((p.x - v1.x) * (v2.x - v1.x))
		+ ((p.y - v1.y) * (v2.y - v1.y))) / (len * len);
	closestx = v1.x + (dot * (v2.x - v1.x));
	closesty = v1.y + (dot * (v2.y - v1.y));
	if (!point_on_segment(v1, v2, new_v3(closestx, closesty, 0)))
		return (0);
	distance = distance_two_points_2d(closestx, closesty, p.x, p.y);
	if (distance <= radius)
		return (1);
	return (0);
}

int		direction_point(t_v3 s1, t_v3 s2, t_v3 p)
{
	double	cross_product;

	s2.x -= s1.x;
	s2.y -= s1.y;
	p.x -= s1.x;
	p.y -= s1.y;
	cross_product = s2.x * p.y - s2.y * p.x;
	if (cross_product > 0)
		return (1);
	if (cross_product < 0)
		return (-1);
	return (0);
}

int		intersection_check(t_v3 w1, t_v3 w2, t_v3 p1, t_v3 p2)
{
	int p1_direction;
	int p2_direction;
	int w1_direction;
	int	w2_direction;

	p1_direction = direction_point(w1, w2, p1);
	p2_direction = direction_point(w1, w2, p2);
	w1_direction = direction_point(p1, p2, w1);
	w2_direction = direction_point(p1, p2, w2);
	if ((p1_direction == 0 || p1_direction == -1 * p2_direction) &&
		(w1_direction == 0 || w1_direction == -1 * w2_direction))
		return (1);
	return (0);
}
