/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 09:33:21 by nneronin          #+#    #+#             */
/*   Updated: 2021/07/21 11:44:34 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	move_ceiling(t_doom *doom, t_event *event)
{
	t_sector	*sector;

	sector = &doom->sectors[event->sector];
	sector->ceiling.y += 0.1 * event->dir;
	if (sector->ceiling.y <= event->min)
		event->dir = 1;
	else if (sector->ceiling.y >= event->max)
		event->dir = -1;
	event->time = doom->time.curr;
}

void	move_floor(t_doom *doom, t_event *event)
{
	t_sector	*sector;

	sector = &doom->sectors[event->sector];
	sector->floor.y += 0.1 * event->dir;
	if (sector->floor.y <= event->min)
	{
		event->dir = 1;
		if (event->wsprite != NULL)
			event->wsprite->trigger = 0;
		if (event->wsprite != NULL && event->wsprite->state == 2)
		{
			event->wsprite->src.x1 = 0;
			event->wsprite->src.y1 = 0;
			event->wsprite->src.x2 = 64;
			event->wsprite->src.y2 = 64;
		}
	}
	else if (sector->floor.y >= event->max)
	{
		event->dir = -1;
		if (event->wsprite != NULL)
			event->wsprite->trigger = 0;
		if (event->wsprite != NULL && event->wsprite->state == 2)
		{
			event->wsprite->src.x1 = 0;
			event->wsprite->src.y1 = 0;
			event->wsprite->src.x2 = 64;
			event->wsprite->src.y2 = 64;
		}
	}
	event->time = doom->time.curr;
}

void	map_events(t_doom *doom)
{
	int			i;

	i = -1;
	while (++i < doom->nb.events)
	{
		if (doom->events[i].time + doom->events[i].speed > doom->time.curr)
			continue ;
		if (doom->events[i].wsprite != NULL && !doom->events[i].wsprite->trigger)
			continue ;
		if (doom->events[i].wsprite != NULL && doom->events[i].wsprite->state == 2)
			animate_wsprite(doom, doom->events[i].wsprite);
		if (doom->events[i].type == BOT)
			move_floor(doom, &doom->events[i]);
		else
			move_ceiling(doom, &doom->events[i]);
	}
}
