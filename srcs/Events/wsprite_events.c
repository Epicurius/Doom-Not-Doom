/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wsprite_trigger_events.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 13:59:58 by nneronin          #+#    #+#             */
/*   Updated: 2021/12/14 14:52:16 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
 *	Move plane up or down.
 *	Dont reset to original position.
 *	When finished update wall sprite if needed.
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
	plane->height += 0.1 * event->dir;
	event->time = doom->time.curr;
	while (++i < event->sector->npoints)
		scale_wall_height(doom, event->sector->wall[i]);
	if (plane->height <= event->min)
		event->dir = 1;
	else if (plane->height >= event->max)
		event->dir = -1;
	else
		return ;
	if (event->wsprite != NULL)
		event->wsprite->trigger = FALSE;
	if (event->wsprite != NULL && event->wsprite->state == 2)
		event->wsprite->src = rect_xy2(0, 0, 64, 64);
}

/*
 *	Preform the wall sprite trigger event.
 */
static void	preform_wsprite_trigger_events(t_doom *doom, t_event *event)
{
	if (event->type == FLOOR || event->type == CEILING)
	{
		if (event->time + 10 > doom->time.curr)
			return ;
		if (event->wsprite->state == ACTION)
			animate_wsprite(doom, event->wsprite);
		move_plane(doom, event);
	}
	else
	{
		if (event->type == STORE && doom->player.store_access)
			precompute_buymenu(doom);
		else if (event->type == AUDIO)
			Mix_PlayChannel(CHANNEL_TTS, event->audio, 0);
		else if (event->type == SPAWN)
			spawn_entity(doom, event->entity, event->pos, event->yaw);
		else if (event->type == LIGHT)
			ft_swap(&event->sector->light, &event->light);
		event->wsprite->trigger = FALSE;
	}
	doom->player.action = NONE;
	doom->keys[SDL_SCANCODE_E] = FALSE;
}

/*
 *	Main functions for wall sprite triggered events.
 *	Check if wall sprite has been triggered and play sound.
 *	Then preform the event action.
 */
void	wsprite_trigger_events(t_doom *doom, t_event *event)
{
	if (!event->wsprite->trigger)
		return ;
	if (event->wsprite->trigger == 1)
	{
		Mix_PlayChannel(-1, doom->sound[WAV_BIP], 0);
		event->wsprite->trigger = 2;
	}
	preform_wsprite_trigger_events(doom, event);
}
