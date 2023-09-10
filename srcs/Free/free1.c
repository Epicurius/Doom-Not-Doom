/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Niklas Neronin <niklas.neronin@gmail.com>
 */

#include "doom.h"

/*
 *	Frees everything that was allocated.
 *	And quits SDL, Mix and TTF.
 */
void	free_doom(t_doom *doom)
{
	free_tpool(&doom->tpool);
	free_map(doom);
	free_entities(doom);
	free_rifts(doom);
	free_sprites_pos(doom);
	free_projectiles(doom);
	free_textures(doom);
	free_icon(doom);
	free_weapons(doom);
	SDL_FreeSurface(doom->time.surf);
	free_render_utils(doom);
	free_font(doom);
	free_sounds(doom);
	SDL_FreeSurface(doom->surface);
	SDL_DestroyTexture(doom->texture);
	SDL_DestroyRenderer(doom->renderer);
	SDL_DestroyWindow(doom->win);
	SDL_Quit();
	Mix_Quit();
	TTF_Quit();
}
