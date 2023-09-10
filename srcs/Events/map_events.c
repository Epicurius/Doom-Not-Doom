/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Niklas Neronin <niklas.neronin@gmail.com>
 */

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
		&& event->time + event->speed < doom->time.curr)
	{
		if (event->type == FLOOR)
			plane = &event->sector->floor;
		else
			plane = &event->sector->ceiling;
		plane->height = ft_fclamp(plane->height + 0.1 * event->dir,
			event->min, event->max);
		event->time = doom->time.curr;
		if (plane->height == event->min || plane->height == event->max)
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
