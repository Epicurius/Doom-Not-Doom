/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_events.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 09:00:24 by nneronin          #+#    #+#             */
/*   Updated: 2021/07/20 16:59:33 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	find_map_event_trigger(t_doom *doom, t_event *event, int id)
{
	int	i;
	int	j;

	i = -1;
	if (id < 0)
	{
		event->wsprite = NULL;
		return ;
	}
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

void	parse_events(t_doom *doom, char **arr)
{
	t_event	event;

	event.sector = ft_atoi(arr[1]);
	if (event.sector > doom->nb.sectors || event.sector < 0)
		error_msg("Map event %s: %s is not valid sector", arr[0], arr[1]);
	if (ft_strequ(arr[2], "Floor"))
		event.type = BOT;
	else if (ft_strequ(arr[2], "Ceiling"))
		event.type = TOP;
	else
		error_msg("Map event %s: %s is not valid", arr[0], arr[2]);
	event.min = ft_atof(arr[3]);
	event.max = ft_atof(arr[4]);
	event.speed = ft_atof(arr[5]) * 10.0f;	
	find_map_event_trigger(doom, &event, ft_atoi(arr[6]));
	event.time = 0;
	event.dir = 1;
	doom->events = ft_realloc(doom->events, sizeof(t_event) * doom->nb.events,
			sizeof(t_event) * ++doom->nb.events);
	doom->events[doom->nb.events - 1] = event;
}
