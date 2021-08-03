/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game_mode.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/20 11:32:29 by nneronin          #+#    #+#             */
/*   Updated: 2021/08/03 11:33:45 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	init_endless(t_doom *doom)
{
	int		i;
	t_list	*curr;

	doom->game.round = 0;
	doom->game.spawn_rate = 5000;
	doom->game.cool_down = 0;
	doom->game.spawns = 0;
	curr = doom->entity;
	while (curr)
	{
		if (((t_entity *)curr->content)->type == ALFRED
			|| ((t_entity *)curr->content)->type == SPOOKY
			|| ((t_entity *)curr->content)->type == GHOST
			|| ((t_entity *)curr->content)->type == RIFT)
			doom->game.spawns += 1;
		curr = curr->next;
	}
	doom->player.store_access = 0;
	i = -1;
	while (++i < doom->nb.events)
		if (doom->events[i].type == STORE)
			doom->events[i].wsprite->src = rect_xy2(662, 0, 1324, 550);
}

void	init_game_mode(t_doom *doom)
{
	doom->game.time = doom->time.curr;
	if (doom->game.mode == ENDLESS)
		init_endless(doom);
}
