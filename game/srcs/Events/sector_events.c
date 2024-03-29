/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Niklas Neronin <niklas.neronin@gmail.com>
 */

#include "doom.h"

/*
 *	Move plane up or down.
 *	Always reset to original position.
 */
static void	move_plane(t_doom *doom, t_event *event)
{
	int		i;
	t_plane	*plane;

	i = -1;
	if (event->type == FLOOR)
		plane = &event->sector->floor;
	else
		plane = &event->sector->ceiling;
	plane->height = ft_fclamp(plane->height + 0.1 * event->dir,
		event->min, event->max);
	event->time = doom->time.curr;
	if (plane->height == event->min || plane->height == event->max)
	{
		event->dir *= -1;
		event->speed += 1000;
		event->trigger++;
	}
	else
		event->speed = 10;
	while (++i < event->sector->npoints)
		scale_wall_height(doom, event->sector->wall[i]);
	if (event->trigger > 2)
		event->trigger = FALSE;
}

/*
 *	Preform the sector trigger event.
 */
static void	preform_sector_trigger_event(t_doom *doom, t_event *event)
{
	if (event->type == FLOOR || event->type == CEILING)
	{
		if (event->time + event->speed < doom->time.curr)
			move_plane(doom, event);
	}
	else if (event->type == HAZARD)
	{
		if (floor_at(event->sector, doom->player.where)
			+ 0.1 >= doom->player.where.z)
			doom->player.damage += event->speed;
		event->trigger = FALSE;
	}
	else
	{
		if (event->type == STORE && doom->player.store_access)
			precompute_buymenu(doom);
		else if (event->type == AUDIO && event->audio)
			Mix_PlayChannel(CHANNEL_TTS, event->audio, 0);
		else if (event->type == SPAWN)
			spawn_entity(doom, event->entity, event->pos, event->yaw);
		else if (event->type == LIGHT)
			ft_swap(&event->sector->light, &event->light);
		event->trigger_sector = -1;
		event->trigger = FALSE;
	}
}

/*
 *	Main functions for sector triggered events.
 *	Check if player is in sector or the event is already triggered.
 */
void	sector_trigger_events(t_doom *doom, t_event *event)
{
	if (event->trigger_sector == doom->player.sector || event->trigger)
	{
		if (event->type == WIN)
			doom->quit = 2;
		else
		{
			if (event->trigger == FALSE)
				event->trigger = TRUE;
			preform_sector_trigger_event(doom, event);
		}
	}
}
