/*
 * https://github.com/Epicurius/Doom-Not-Doom
 * 
 * Created: 2021/05/20 15:25:14 nneronin
 * Updated: 2022/01/14 10:56:33 nneronin
 */

#include "doom.h"

/*
 *	Creates a BMP of the game and save it in ./ScreenShots/.
 *	NOTE: All pause menu text will not be written to screen shot.
 */
static t_bmp	*s_to_save_screen_shot(t_doom *doom)
{
	SDL_Rect	dstr;
	TTF_Font	*amaz;
	SDL_Surface	*surface;

	ft_strcpy(&doom->root[doom->rlen], "resources/TTF/AmazDoom.ttf");
	amaz = TTF_OpenFont(doom->root, 25);
	surface = TTF_RenderText_Blended(amaz, "'S' to Save Screen Shot",
			hex_to_sdl_color(0xFFFFFFFF));
	dstr = (SDL_Rect){doom->surface->w - surface->w - 10,
		doom->surface->h - surface->h, surface->w, surface->h};
	SDL_BlitSurface(surface, NULL, doom->surface, &dstr);
	SDL_FreeSurface(surface);
	TTF_CloseFont(amaz);
	return (pix_to_bmp(doom->surface->w, doom->surface->h, 3,
			doom->surface->pixels));
}

/*
 *	Blits Y/N to surface.
 */
static void	y_or_n(t_doom *doom, int y)
{
	SDL_Rect	dstr;
	SDL_Surface	*surface;

	surface = TTF_RenderText_Blended(doom->font.amaz,
			"Y/N", hex_to_sdl_color(0xFFFFFFFF));
	dstr = (SDL_Rect){doom->c.x - surface->w / 2, y, surface->w, surface->h};
	SDL_BlitSurface(surface, NULL, doom->surface, &dstr);
	SDL_FreeSurface(surface);
}

/*
 *	Quit? loop wait for player to press y, n, esc or q.
 */
static void	quit_loop(t_doom *doom, t_bmp *bmp, int i)
{
	SDL_Event	event;
	char		*name;

	while (1)
	{
		SDL_PollEvent(&event);
		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_n)
		{
			doom->quit = FALSE;
			break ;
		}
		if ((event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_y)
			|| (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_q))
			break ;
		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_s && !i)
		{
			name = ft_sprintf("%s/Doom%d%d%d.bmp", doom->root, rand() % 0xFFFF);
			write_bmp(name, bmp);
			free(name);
			Mix_PlayChannel(CHANNEL_TTS, doom->sound[WAV_SCREEN_SHOT], 0);
			Mix_VolumeChunk(doom->sound[WAV_SCREEN_SHOT], 128);
			i = TRUE;
		}
	}
	free_bmp(bmp);
}

/*
 *	Draws Quit? screen aswell as handling events.
 */
void	game_quit(t_doom *doom)
{
	t_bxpm	bxpm;
	t_bmp	*bmp;

	if (doom->quit != 1)
		return ;
	Mix_HaltChannel(CHANNEL_STEPS);
	SDL_ShowCursor(SDL_ENABLE);
	SDL_SetRelativeMouseMode(SDL_FALSE);
	SDL_WarpMouseInWindow(doom->win, doom->c.x, doom->c.y);
	bmp = s_to_save_screen_shot(doom);
	ft_strcpy(&doom->root[doom->rlen], "resources/BXPM/GameQuit.bxpm");
	read_bxpm(&bxpm, doom->root);
	blit_bxpm(doom->surface, &bxpm, doom->c.x - bxpm.w / 2,
		doom->c.y - bxpm.h / 2);
	free(bxpm.pix);
	free(bxpm.clr);
	y_or_n(doom, doom->c.y + bxpm.h / 2);
	update_screen(doom);
	doom->root[doom->rlen] = '\0';
	quit_loop(doom, bmp, FALSE);
	ft_bzero(&doom->keys, 517);
	SDL_ShowCursor(SDL_DISABLE);
	SDL_SetRelativeMouseMode(SDL_TRUE);
	SDL_GetRelativeMouseState(NULL, NULL);
	doom->time.curr = SDL_GetTicks();
}
