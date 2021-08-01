/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loading.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 09:18:23 by nneronin          #+#    #+#             */
/*   Updated: 2021/08/01 09:07:49 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	game_loading(t_doom *doom)
{
	SDL_Event	event;
	t_bxpm		*bxpm;

	bxpm = protalloc(sizeof(t_bxpm), "Game_loading bxpm.");
	read_bxpm(bxpm, BXPM_PATH"game_loading.bxpm");
	blit_bxpm(doom->surface, bxpm, doom->surface->w / 2 - bxpm->w / 2,
		doom->surface->h / 2 - bxpm->h / 2);
	update_screen(doom, doom->surface);
	SDL_PollEvent(&event);
	SDL_RaiseWindow(doom->win);
	free_bxpm(bxpm);
	ft_bzero(&doom->keys, sizeof(char) * (SDL_NUM_SCANCODES + 5));
	//ft_bzero(&doom->key, sizeof(doom->key));
	doom->time.curr = SDL_GetTicks();
}
