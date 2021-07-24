/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_endless.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/20 11:32:29 by nneronin          #+#    #+#             */
/*   Updated: 2021/07/24 10:13:07 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	init_wave_mode(t_doom *doom)
{
	t_list	*curr;
	int		i;

	doom->game.round = 0;
	doom->game.time = doom->time.curr;
	doom->game.spawn_rate = 5000;
	doom->game.cool_down = 0;
	doom->game.spawns = 0;
	curr = doom->entity;
	while (curr)
	{
		if (((t_entity *)curr->content)->type == 0
			|| ((t_entity *)curr->content)->type == 1
			|| ((t_entity *)curr->content)->type == 2)
			doom->game.spawns += 1;
		curr = curr->next;
	}
	doom->player.store_access = 0;
	i = -1;
	while (++i < doom->nb.events)
		if (doom->events[i].type == STORE)
			doom->events[i].wsprite->src = rect_xy2(662, 0, 1324, 550);
}
