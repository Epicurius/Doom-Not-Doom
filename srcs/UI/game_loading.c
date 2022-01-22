/*
 * https://github.com/Epicurius/Doom-Not-Doom
 * 
 * Created: 2021/06/16 09:18:23 nneronin
 * Updated: 2022/01/14 10:55:50 nneronin
 */

#include "doom.h"

/*
 *	Creates the loading screen.
 *	Loads loading.bxpm and blits it to surface.
 *	Raises Window so that the loading is visible.
 */
void	game_loading(t_doom *doom)
{
	SDL_Event	event;
	t_bxpm		bxpm;

	Mix_HaltChannel(CHANNEL_STEPS);
	ft_strcpy(&doom->root[doom->rlen], "resources/BXPM/GameLoad.bxpm");
	read_bxpm(&bxpm, doom->root);
	blit_bxpm(doom->surface, &bxpm, doom->surface->w / 2 - bxpm.w / 2,
		doom->surface->h / 2 - bxpm.h / 2);
	update_screen(doom);
	SDL_RaiseWindow(doom->win);
	SDL_PollEvent(&event);
	free(bxpm.pix);
	free(bxpm.clr);
	ft_bzero(&doom->keys, 517);
	doom->time.curr = SDL_GetTicks();
}
