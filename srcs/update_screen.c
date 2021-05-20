/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_screen.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 16:16:37 by nneronin          #+#    #+#             */
/*   Updated: 2021/05/20 16:20:29 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	update_screen(t_doom *doom, SDL_Surface *surface)
{
	if (SDL_UpdateTexture(doom->texture, NULL, surface->pixels, surface->pitch))
		error_msg("Failed to update screen: %s\n", SDL_GetError());
	if (SDL_RenderCopy(doom->renderer, doom->texture, NULL, NULL))
		error_msg("SDL_RenderCopy error: %s\n", SDL_GetError());
	SDL_RenderPresent(doom->renderer);
}
