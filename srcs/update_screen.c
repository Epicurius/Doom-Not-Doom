/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_screen.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 16:16:37 by nneronin          #+#    #+#             */
/*   Updated: 2021/12/15 11:32:28 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
 *	Update window with new frame.
 *	surface -> texture -> renderer -> window.
 */
void	update_screen(t_doom *doom)
{
	if (SDL_UpdateTexture(doom->texture, NULL,
			doom->surface->pixels, doom->surface->pitch))
		error_msg("Failed to update screen: %s\n", SDL_GetError());
	if (SDL_RenderCopy(doom->renderer, doom->texture, NULL, NULL))
		error_msg("SDL_RenderCopy error: %s\n", SDL_GetError());
	SDL_RenderPresent(doom->renderer);
}
