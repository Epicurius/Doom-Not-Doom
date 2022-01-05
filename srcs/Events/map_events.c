/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 09:33:21 by nneronin          #+#    #+#             */
/*   Updated: 2021/12/14 15:16:18 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
 *	Hanfle loop events, atm only Floor and Ceiling can be loop events.
 *	"mmamammmmammamamaaamammma"
 */
static void	loop_events(t_doom *doom, t_event *event)
{
	int		i;
	t_plane	*plane;

	i = -1;
	if (event->type == LIGHT && event->time + event->speed < doom->time.curr)
	{
		event->speed = 100 + (rand() % 1000);
		event->time = doom->time.curr;
		ft_swap(&event->sector->light, &event->light);
	}
	else if ((event->type == FLOOR || event->type == CEILING)
		&& event->time + 100 < doom->time.curr)
	{
		if (event->type == FLOOR)
			plane = &event->sector->floor;
		else
			plane = &event->sector->ceiling;
		plane->height += 0.1 * event->dir;
		event->time = doom->time.curr;
		if (plane->height <= event->min || plane->height >= event->max)
			event->dir *= -1;
		while (++i < event->sector->npoints)
			scale_wall_height(doom, event->sector->wall[i]);
	}
}

/*
 *	Checks the type of map event.
 */
void	map_events(t_doom *doom)
{
	int	i;

	i = -1;
	while (++i < doom->nb.events)
	{
		if (doom->events[i].action == NONE)
			loop_events(doom, &doom->events[i]);
		else if (doom->events[i].action == SECTOR)
			sector_trigger_events(doom, &doom->events[i]);
		else
			wsprite_trigger_events(doom, &doom->events[i]);
	}
}