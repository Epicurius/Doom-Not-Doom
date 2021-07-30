/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precompute_buy_menu.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/24 15:34:12 by nneronin          #+#    #+#             */
/*   Updated: 2021/07/30 16:47:26 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	precompute_buy_menu(t_doom *doom)
{
	Mix_PlayChannel(CHANNEL_MUSIC, doom->sound[WAV_ELEVATOR_MUSIC], -1);
	SDL_SetRelativeMouseMode(SDL_FALSE);
	buymenu_new(doom->win, doom->renderer, doom->surface, &doom->inv);
	ft_bzero(&doom->keys, 517);
	doom->player.action = NONE;
	SDL_SetRelativeMouseMode(SDL_TRUE);
	doom->time.curr = SDL_GetTicks();
	Mix_PlayChannel(CHANNEL_MUSIC, doom->sound[WAV_MAIN_THEME], -1);
}
