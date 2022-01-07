/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_events1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 09:00:24 by nneronin          #+#    #+#             */
/*   Updated: 2022/01/07 16:16:05 by nneronin         ###   ########.fr       */
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
	LG_ERROR("No wsprite wsprite with id:%d found.\n", id);
}

/*
 *	Parse event action.
 */
static void	get_event_action(t_doom *doom, t_event *event, char **arr)
{
	int	i;

	i = -1;
	while (++i < EVENT_ACTION_AMOUNT)
		if (ft_strequ(arr[2], g_event_action[i]))
			break ;
	if (i >= EVENT_ACTION_AMOUNT)
		LG_ERROR("Map event %s is not valid", arr[2]);
	event->action = i;
	if (event->action == CLICKING)
		find_wsprite_trigger(doom, event, ft_atoi(arr[3]));
	else if (event->action == SHOOTING)
		find_wsprite_trigger(doom, event, ft_atoi(arr[3]));
	else if (event->action == SECTOR)
		event->trigger_sector = ft_atoi(arr[3]);
}

/*
 *	Parse event type.
 */
static void	get_event_type(t_doom *doom, t_event *event, char **arr, int nb)
{
	int	i;

	i = -1;
	while (++i < EVENT_TYPE_AMOUNT)
		if (ft_strequ(arr[1], g_event_type[i]))
			break ;
	if (i >= EVENT_TYPE_AMOUNT || i == 0)
		LG_ERROR("Map event %s is not valid", arr[1]);
	event->type = i;
	if (event->type == FLOOR)
		floor_ceiling_event(event, nb, arr);
	else if (event->type == CEILING)
		floor_ceiling_event(event, nb, arr);
	else if (event->type == SPAWN)
		spawn_event(doom, event, nb, arr);
	else if (event->type == AUDIO)
		audio_event(event, nb, arr);
	else if (event->type == HAZARD)
		hazard_event(event, nb, arr);
	else if (event->type == LIGHT)
		light_event(event, nb, arr);
	else if (event->type == WIN && event->action == 0)
		LG_ERROR("Event WIN cant have NONE as an event trigger.");
	else if (event->type == STORE && (event->action == 0 || event->action == 3))
		LG_ERROR("Event STORE can only have SHOOT/CLICK as an event trigger.");
}

/*
 *	Parse type:events
 *	Type HAZARD can only have action SECTOR.
 * 	Actions STORE and AUDIO cant have type NONE.
 * 	It will not break instead not do anything.
 */
void	parse_events(t_doom *doom, int nb, char **arr)
{
	static int	i = 0;

	if (nb < 3)
		LG_ERROR("Invalid amount of event arguments.");
	if (i >= doom->nb.events)
		LG_ERROR("Invalid amount of events.");
	ft_bzero(&doom->events[i], sizeof(t_event));
	get_event_action(doom, &doom->events[i], arr);
	get_event_type(doom, &doom->events[i], arr, nb);
	i++;
}
