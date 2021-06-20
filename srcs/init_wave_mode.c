/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_wave_mode.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/20 11:32:29 by nneronin          #+#    #+#             */
/*   Updated: 2021/06/20 13:10:48 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	init_gamemode(t_doom *doom)
{
	t_list	*curr;

	doom->game.round = 0;
	doom->game.time = doom->time.curr;
	doom->game.spawn_rate = 5000;
	doom->game.cool_down = 0;
	doom->game.spawns = 0;
	curr = doom->sprite;
	while (curr)
	{
		if (((t_entity *)curr->content)->type == 0
			|| ((t_entity *)curr->content)->type == 1
			|| ((t_entity *)curr->content)->type == 2)
			doom->game.spawns += 1;
		curr = curr->next;
	}
}
