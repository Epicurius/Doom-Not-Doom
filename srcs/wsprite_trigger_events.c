/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wsprite_trigger_events.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 13:59:58 by nneronin          #+#    #+#             */
/*   Updated: 2021/08/11 08:16:49 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	move_plane(t_doom *doom, t_event *event)
{
	int		i;
	t_plane	*plane;

	i = -1;
	if (event->type == FLOOR)
		plane = &event->event_sector->floor;
	else
		plane = &event->event_sector->ceiling;
	plane->y += 0.1 * event->dir;
	event->time = doom->time.curr;
	while (++i < event->event_sector->npoints)
		scale_wall_height(doom, event->event_sector->wall[i]);
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

static void	preform_wsprite_trigger_events(t_doom *doom, t_event *event, int i)
{
	if (event->type == FLOOR || event->type == CEILING)
	{
		if (event->time + 10 > doom->time.curr)
			return ;
		if (event->wsprite->state == ACTION)
			animate_wsprite(doom, event->wsprite);
		move_plane(doom, event);
	}
	else if (event->type == STORE && event->wsprite->trigger
		&& doom->player.store_access)
	{
		precompute_buy_menu(doom);
		event->wsprite->trigger = 0;
	}
	else if (event->type == AUDIO)
	{
		Mix_PlayChannel(CHANNEL_TTS, event->audio, 0);
		event->wsprite->trigger = 0;
	}
}

void	wsprite_trigger_events(t_doom *doom, t_event *event)
{
	if (!event->wsprite->trigger)
		return ;
	if (event->wsprite->trigger == 1)
	{
		Mix_PlayChannel(-1, doom->sound[WAV_BIP], 0);
		event->wsprite->trigger = 2;
	}
	preform_wsprite_trigger_events(doom, event, -1);
}
