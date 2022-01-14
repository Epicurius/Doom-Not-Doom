/*
 * https://github.com/Epicurius/Doom-Not-Doom
 * 
 * Created: 2021/05/20 16:16:37 nneronin
 * Updated: 2022/01/07 16:16:05 nneronin
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
		LG_ERROR("Failed to update screen: %s\n", SDL_GetError());
	if (SDL_RenderCopy(doom->renderer, doom->texture, NULL, NULL))
		LG_ERROR("SDL_RenderCopy error: %s\n", SDL_GetError());
	SDL_RenderPresent(doom->renderer);
}
