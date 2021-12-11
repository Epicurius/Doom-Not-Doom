/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precompute_buy_menu.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/24 15:34:12 by nneronin          #+#    #+#             */
/*   Updated: 2021/12/11 09:52:36 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
 *	Precomputes the BuyMenu.
 *	Chenges music, releases the mouse and afterward flushes the events.
 */
void	precompute_buymenu(t_doom *doom)
{
	int	x;
	int	y;

	Mix_PlayChannel(CHANNEL_MUSIC, doom->sound[WAV_ELEVATOR_MUSIC], -1);
	SDL_GetMouseState(&x, &y);
	SDL_SetRelativeMouseMode(SDL_FALSE);
	buymenu(doom->win, doom->surface, &doom->inv);
	Mix_PlayChannel(-1, doom->sound[WAV_BIP], 0);
	ft_bzero(&doom->keys, 517);
	doom->player.action = NONE;
	SDL_WarpMouseInWindow(doom->win, x, y);
	SDL_SetRelativeMouseMode(SDL_TRUE);
	doom->time.curr = SDL_GetTicks();
	Mix_PlayChannel(CHANNEL_MUSIC, doom->sound[WAV_MAIN_THEME], -1);
}
