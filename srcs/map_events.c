/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 09:33:21 by nneronin          #+#    #+#             */
/*   Updated: 2021/08/01 09:19:51 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	move_plane(t_doom *doom, t_event *event)
{
	t_plane	*plane;

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
	else
		return ;
	if (event->wsprite != NULL)
		event->wsprite->trigger = 0;
	if (event->wsprite != NULL && event->wsprite->state == 2)
		event->wsprite->src = rect_xy2(0, 0, 64, 64);
	if (event->trigger_sector != NULL)
		event->trigger_sector->trigger = 0;
}

void	loop_events(t_doom *doom, t_event *event)
{
	int	i;

	if (event->type == FLOOR || event->type == CEILING)
	{
		if (event->time + 100 > doom->time.curr)
			return ;
		move_plane(doom, event);
		i = -1;
		while (++i < event->event_sector->npoints)
			scale_wall_height(doom, event->event_sector->wall[i]);
	}
}

void	wsprite_trigger_events(t_doom *doom, t_event *event)
{
	int	i;

	if (!event->wsprite->trigger)
		return ;
	if (event->wsprite->trigger == 1)
	{
		Mix_PlayChannel(-1, doom->sound[WAV_BIP], 0);
		event->wsprite->trigger = 2;
	}
	if (event->type == FLOOR || event->type == CEILING)
	{
		if (event->time + 10 > doom->time.curr)
			return ;
		if (event->wsprite->state == ACTION)
			animate_wsprite(doom, event->wsprite);
		move_plane(doom, event);
		i = -1;
		while (++i < event->event_sector->npoints)
			scale_wall_height(doom, event->event_sector->wall[i]);
	}
	else if (event->type == STORE && doom->player.store_access)
	{
		if (event->wsprite->trigger)
		{
			precompute_buy_menu(doom);
			event->wsprite->trigger = 0;
		}
	}
}

//	Fix sector trigger Store
void	sector_trigger_events(t_doom *doom, t_event *event)
{
	int	i;

	i = -1;
	if ((event->trigger_sector->id != doom->player.sector)
		&& !event->trigger_sector->trigger)
		return ;
	event->trigger_sector->trigger = 1;
	if (event->type == FLOOR || event->type == CEILING)
	{
		if (event->time + 10 > doom->time.curr)
			return ;
		move_plane(doom, event);
		while (++i < event->event_sector->npoints)
			scale_wall_height(doom, event->event_sector->wall[i]);
	}
	else if (event->type == STORE && doom->player.store_access)
	{
		precompute_buy_menu(doom);
		event->trigger_sector->trigger = 0;
	}
	else if (event->type == HAZARD && floor_at(event->trigger_sector,
			doom->player.where) + 0.1 >= doom->player.where.z)
		doom->player.health -= event->speed;
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
