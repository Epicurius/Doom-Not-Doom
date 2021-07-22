/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 09:33:21 by nneronin          #+#    #+#             */
/*   Updated: 2021/07/22 15:19:09 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	move_plane(t_doom *doom, t_event *event)
{
	t_plane	*plane;

	if (event->type == FLOOR)
		plane = &doom->sectors[event->sector].floor;
	else
		plane = &doom->sectors[event->sector].ceiling;
	plane->y += 0.1 * event->dir;
	event->time = doom->time.curr;
	if (plane->y <= event->min)
		event->dir = 1;
	else if (plane->y >= event->max)
		event->dir = -1;
	else
		return ;
	if (event->wsprite != NULL)
		event->wsprite->trigger = 0;
	if (event->wsprite != NULL && event->wsprite->state == 2)
		event->wsprite->src = rect_xy2(0, 0, 64, 64);
}

void	scale_wall_height(t_doom *doom, t_wall *wall)
{
	wall->height = doom->sectors[wall->sect].ceiling.y
		- doom->sectors[wall->sect].floor.y;
	wall->scale_h = (doom->mtx[wall->wtx].h / wall->scale) * wall->height;
}

void	map_events(t_doom *doom)
{
	int	i;
	int	j;

	i = -1;
	while (++i < doom->nb.events)
	{
		if (doom->events[i].time + doom->events[i].speed > doom->time.curr)
			continue ;
		if (doom->events[i].wsprite != NULL && !doom->events[i].wsprite->trigger)
			continue ;
		if (doom->events[i].wsprite != NULL && doom->events[i].wsprite->state == 2)
			animate_wsprite(doom, doom->events[i].wsprite);
		move_plane(doom, &doom->events[i]);
		j = -1;
		while (++j < doom->sectors[doom->events[i].sector].npoints)
			scale_wall_height(doom, doom->sectors[doom->events[i].sector].wall[j]);
	}
}
