/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_events2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 09:00:24 by nneronin          #+#    #+#             */
/*   Updated: 2021/08/25 09:59:32 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	floor_ceiling_event(t_doom *doom, t_event *event, int nb, char **arr)
{
	if (nb < 7)
		error_msg("Invalid argument for event %s\n", arr[0]);
	event->event_sector = &doom->sectors[ft_atoi(arr[4])];
	event->min = ft_atof(arr[5]);
	event->max = ft_atof(arr[6]);
	event->speed = ft_atof(arr[7]);
}

void	spawn_event(t_doom *doom, t_event *event, int nb, char **arr)
{
	if (nb < 8)
		error_msg("Invalid argument for event %s\n", arr[0]);
	if (event->type == NONE)
		error_msg("Event 'Spawn' can`t have action NONE");
	event->entity = ft_atoi(arr[4]);
	event->pos = new_v3(ft_atof(arr[5]), ft_atof(arr[6]), ft_atof(arr[7]));
	event->pos = mult_v3(event->pos, doom->map_scale);
	event->yaw = ft_atoi(arr[8]);
}

void	audio_event(t_doom *doom, t_event *event, int nb, char **arr)
{
	if (nb < 4)
		error_msg("Invalid argument for event %s\n", arr[0]);
	if (event->action == NONE)
		error_msg("Event 'Audio' can`t have action NONE");
	event->path = ft_strdup(arr[4]);
}

void	hazard_event(t_doom *doom, t_event *event, int nb, char **arr)
{
	if (nb < 4)
		error_msg("Invalid argument for event %s\n", arr[0]);
	if (event->action != SECTOR)
		error_msg("Event 'Hazard' can only have SECTOR as an action.");
	event->speed = ft_atoi(arr[4]);
}