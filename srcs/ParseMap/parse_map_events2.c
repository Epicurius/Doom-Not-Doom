/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_events2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 09:00:24 by nneronin          #+#    #+#             */
/*   Updated: 2021/12/17 10:35:16 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
 *	Parse Floor or Ceiling event args.
 */
void	floor_ceiling_event(t_event *event, int nb, char **arr)
{
	if (nb < 7)
		error_msg("Invalid argument for event %s\n", arr[0]);
	event->event_sector = ft_atoi(arr[4]);
	event->dir = 1;
	if (event->type == CEILING)
		event->dir = -1;
	event->min = ft_atof(arr[5]);
	event->max = ft_atof(arr[6]);
	event->speed = ft_atof(arr[7]);
}

/*
 *	Parse Spawn event args.
 *	event->yaw = ft_atoi(arr[8]) * CONVERT_TO_RADIANS;
 */
void	spawn_event(t_doom *doom, t_event *event, int nb, char **arr)
{
	if (nb < 8)
		error_msg("Invalid argument for event %s\n", arr[0]);
	if (event->type == NONE)
		error_msg("Event 'Spawn' can`t have action NONE");
	event->entity = ft_atoi(arr[4]);
	event->pos = mult_v3(new_v3(ft_atof(arr[5]),
				ft_atof(arr[6]), ft_atof(arr[7])), doom->map_scale);
}

/*
 *	Parse Audio event args.
 */
void	audio_event(t_event *event, int nb, char **arr)
{
	if (nb < 4)
		error_msg("Invalid argument for event %s\n", arr[0]);
	if (event->action == NONE)
		error_msg("Event 'Audio' can`t have action NONE");
	event->path = ft_strdup(arr[4]);
}

/*
 *	Parse Hazard event args.
 */
void	hazard_event(t_event *event, int nb, char **arr)
{
	if (nb < 7)
		error_msg("Invalid argument for event %s\n", arr[0]);
	if (event->action != SECTOR)
		error_msg("Event 'Hazard' can only have SECTOR as an action.\n");
	event->event_sector = ft_atoi(arr[4]);
	event->speed = ft_atoi(arr[7]);
	ft_printf("%d %f\n", event->event_sector, event->speed);
}

/*
 *	Parse Light event args.
 */
void	light_event(t_event *event, int nb, char **arr)
{
	if (nb < 5)
		error_msg("Invalid argument for event %s\n", arr[0]);
	event->event_sector = ft_atoi(arr[4]);
	event->light = ft_atoi(arr[5]);
}
