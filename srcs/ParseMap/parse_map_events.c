/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_events.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 09:00:24 by nneronin          #+#    #+#             */
/*   Updated: 2021/08/10 13:41:39by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	find_wsprite_trigger(t_doom *doom, t_event *event, int id)
{
	int	i;
	int	j;

	i = -1;
	while (++i < doom->nb.walls)
	{
		if (doom->walls[i].wsprite.total == 0)
			continue ;
		j = -1;
		while (++j < doom->walls[i].wsprite.total)
		{
			if (doom->walls[i].wsprite.num[j].id == id)
			{
				event->wsprite = &doom->walls[i].wsprite.num[j];
				event->wsprite->trigger = 0;
				event->wsprite->action = event->action;
				return ;
			}
		}
	}
	error_msg("No wsprite wspprite with id:%d found.\n", id);
}

void	get_event_type(t_event *event, char *str)
{
	if (ft_strequ(str, "Ceiling"))
	{
		event->dir = -1;
		event->type = CEILING;
	}
	else if (ft_strequ(str, "Floor"))
	{
		event->dir = 1;
		event->type = FLOOR;
	}
	else if (ft_strequ(str, "Store"))
		event->type = STORE;
	else if (ft_strequ(str, "Hazard"))
		event->type = HAZARD;
	else if (ft_strequ(str, "Audio"))
		event->type = AUDIO;
	else
		error_msg("Map event %s is not valid", str);
}

void	get_event_action(t_event *event, char *str)
{
	if (ft_strequ(str, "CLICK"))
		event->action = CLICKING;
	else if (ft_strequ(str, "SHOOT"))
		event->action = SHOOTING;
	else if (ft_strequ(str, "SECTOR"))
		event->action = SECTOR;
	else
		event->action = NONE;
}

//	if (event.type == HAZARD && event.action != SECTOR)
//	if (event.action == NONE && (event.type == STORE || event.type == AUDIO))
void	parse_events(t_doom *doom, char **arr)
{
	t_event	event;

	ft_bzero(&event, sizeof(t_event));
	get_event_type(&event, arr[1]);
	get_event_action(&event, arr[2]);
	if (event.action == CLICKING || event.action == SHOOTING)
		find_wsprite_trigger(doom, &event, ft_atoi(arr[3]));
	else if (event.action == SECTOR)
		event.trigger_sector = ft_atoi(arr[3]);
	if (event.type == FLOOR || event.type == CEILING)
	{
		event.event_sector = &doom->sectors[ft_atoi(arr[4])];
		event.min = ft_atof(arr[5]);
		event.max = ft_atof(arr[6]);
	}
	else if (event.type == AUDIO)
		event.path = ft_strdup(arr[4]);
	event.speed = 10;
	doom->events = ft_realloc(doom->events, sizeof(t_event) * doom->nb.events,
			sizeof(t_event) * ++doom->nb.events);
	doom->events[doom->nb.events - 1] = event;
}
