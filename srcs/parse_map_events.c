/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_events.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 09:00:24 by nneronin          #+#    #+#             */
/*   Updated: 2021/07/18 15:46:16 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

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
	event.time = 0;
	event.dir = 1;
	doom->events = ft_realloc(doom->events, sizeof(t_event) * doom->nb.events,
			sizeof(t_event) * ++doom->nb.events);
	doom->events[doom->nb.events - 1] = event;
}
