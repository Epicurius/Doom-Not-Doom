/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   endless.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 10:58:23 by nneronin          #+#    #+#             */
/*   Updated: 2021/08/03 17:51:34 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int	endless_round(t_doom *doom)
{
	if (doom->game.spawns == 0)
	{
		doom->game.round++;
		doom->game.spawn_rate = 5000 - doom->game.round * 2;
		doom->game.cool_down = 10;
		doom->player.health = 1100 - doom->settings.difficulty * 100;
		doom->inv.dosh += 100 + doom->game.round * 10;
		doom->player.store_access = 1;
		Mix_PlayChannel(-1, doom->sound[WAV_DOSH], 0);
		Mix_PlayChannel(-1, doom->sound[WAV_ROUND_END], 0);
		return (1);
	}
	else if (doom->time.curr - doom->game.time > doom->game.spawn_rate)
	{
		rift_spawn(doom);
		doom->game.time = doom->time.curr;
	}
	return (0);
}

//		ft_printf("%f\n", doom->game.cool_down);
void	game_mode_endless(t_doom *doom)
{
	int	i;

	i = -1;
	if (doom->game.cool_down > 0)
	{
		doom->game.cool_down -= 1 * doom->time.delta;
		if (doom->game.cool_down <= 0)
		{
			doom->player.store_access = 0;
			while (++i < doom->nb.events)
				if (doom->events[i].type == STORE)
					doom->events[i].wsprite->src = rect_xy2(662, 0, 1324, 550);
			respawn_rifts(doom);
			Mix_PlayChannel(CHANNEL_MUSIC, doom->sound[WAV_NEW_ROUND], 0);
		}
	}
	else if (!Mix_Playing(CHANNEL_TTS) && endless_round(doom))
	{
		while (++i < doom->nb.events)
			if (doom->events[i].type == STORE)
				doom->events[i].wsprite->src = rect_xy2(0, 0, 662, 550);
	}
}

void	game_mode(t_doom *doom)
{
	if (doom->game.mode == ENDLESS)
		game_mode_endless(doom);
}
