/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_events1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 09:00:24 by nneronin          #+#    #+#             */
/*   Updated: 2021/12/13 16:04:16 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
 *	Find the wall sprite that is the trigger for the event.
 */
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
				event->wsprite->action = event->action;
				event->wsprite->trigger = FALSE;
				return ;
			}
		}
	}
	error_msg("No wsprite wsprite with id:%d found.\n", id);
}

/*
 *	Parse event type.
 */
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
	else if (ft_strequ(str, "Spawn"))
		event->type = SPAWN;
	else if (ft_strequ(str, "Light"))
		event->type = LIGHT;
	else
		error_msg("Map event %s is not valid", str);
}

/*
 *	Parse event action.
 */
void	get_event_action(t_event *event, char *str)
{
	if (ft_strequ(str, "CLICK"))
		event->action = CLICKING;
	else if (ft_strequ(str, "SHOOT"))
		event->action = SHOOTING;
	else if (ft_strequ(str, "SECTOR"))
		event->action = SECTOR;
	//else if (ft_strequ(str, "ROUNDSTART"))
	//	event->action = ROUNDSTART;
	//else if (ft_strequ(str, "ROUNDEND"))
	//	event->action = ROUNDEND;
	else
		event->action = NONE;
}

/*
 *	Parse type:events
 *	Type HAZARD can only have action SECTOR.
 * 	Actions STORE and AUDIO cant have type NONE.
 * 	It will not break instead not do anything.
 */
void	parse_events(t_doom *doom, int nb, char **arr)
{
	t_event	event;

	if (nb < 3)
		error_msg("Invalid amount of event arguments");
	ft_bzero(&event, sizeof(t_event));
	get_event_type(&event, arr[1]);
	get_event_action(&event, arr[2]);
	if (event.action == CLICKING || event.action == SHOOTING)
		find_wsprite_trigger(doom, &event, ft_atoi(arr[3]));
	else if (event.action == SECTOR)
		event.trigger_sector = correct_sector_index(doom, ft_atoi(arr[3]));
	if (event.type == FLOOR || event.type == CEILING)
		floor_ceiling_event(doom, &event, nb, arr);
	else if (event.type == SPAWN)
		spawn_event(doom, &event, nb, arr);
	else if (event.type == AUDIO)
		audio_event(&event, nb, arr);
	else if (event.type == HAZARD)
		hazard_event(doom, &event, nb, arr);
	else if (event.type == LIGHT)
		light_event(doom, &event, nb, arr);
	doom->events = ft_realloc(doom->events, sizeof(t_event) * doom->nb.events,
			sizeof(t_event) * ++doom->nb.events);
	doom->events[doom->nb.events - 1] = event;
}
