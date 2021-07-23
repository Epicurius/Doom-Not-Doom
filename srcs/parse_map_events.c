/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_events.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 09:00:24 by nneronin          #+#    #+#             */
/*   Updated: 2021/07/22 09:30:03 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	find_event_trigger(t_doom *doom, t_event *event, int id)
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
	else
		error_msg("Map event %s is not valid", str);
}

void	get_event_action(t_event *event, char *str)
{
	if (ft_strequ(str, "CLICK"))
		event->action = CLICKING;
	else if (ft_strequ(str, "SHOOT"))
		event->action = SHOOTING;
	else
		event->action = NONE;
}

void	parse_events(t_doom *doom, char **arr)
{
	t_event	event;

	get_event_type(&event, arr[1]);
	get_event_action(&event, arr[2]);
	event.wsprite = NULL;
	if (event.action != NONE)
	{
		find_event_trigger(doom, &event, ft_atoi(arr[3]));
		event.wsprite->action = event.action;
	}
	if (event.type != 2)
	{
		event.sector = ft_atoi(arr[4]);
		if (event.sector > doom->nb.sectors || event.sector < 0)
			error_msg("Map event %s: %s is not valid sector", arr[0], arr[4]);	
		event.min = ft_atof(arr[5]);
		event.max = ft_atof(arr[6]);
		event.speed = ft_atof(arr[7]) * 10.0f;
	}
	event.time = 0;
	doom->events = ft_realloc(doom->events, sizeof(t_event) * doom->nb.events,
			sizeof(t_event) * ++doom->nb.events);
	doom->events[doom->nb.events - 1] = event;
}
