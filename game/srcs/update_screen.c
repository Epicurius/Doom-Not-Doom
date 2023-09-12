/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Niklas Neronin <niklas.neronin@gmail.com>
 */

#include "doom.h"

/*
 *	Update window with new frame.
 *	surface -> texture -> renderer -> window.
 */
void	update_screen(t_doom *doom)
{
	if (SDL_UpdateTexture(doom->texture, NULL,
			doom->surface->pixels, doom->surface->pitch))
		LG_ERROR("Failed to update screen: %s.", SDL_GetError());
	if (SDL_RenderCopy(doom->renderer, doom->texture, NULL, NULL))
		LG_ERROR("SDL_RenderCopy error: %s.", SDL_GetError());
	SDL_RenderPresent(doom->renderer);
}
