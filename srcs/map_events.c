/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 09:33:21 by nneronin          #+#    #+#             */
/*   Updated: 2021/08/10 14:31:45 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	loop_events(t_doom *doom, t_event *event)
{
	int		i;
	t_plane	*plane;

	i = -1;
	if (event->type == FLOOR || event->type == CEILING)
	{
		if (event->time + 100 > doom->time.curr)
			return ;
		if (event->type == FLOOR)
			plane = &event->event_sector->floor;
		else
			plane = &event->event_sector->ceiling;
		plane->y += 0.1 * event->dir;
		event->time = doom->time.curr;
		if (plane->y <= event->min)
			event->dir = 1;
		else if (plane->y >= event->max)
			event->dir = -1;
		while (++i < event->event_sector->npoints)
			scale_wall_height(doom, event->event_sector->wall[i]);
	}
}

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
