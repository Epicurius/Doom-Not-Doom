/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_over.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 18:28:56 by nneronin          #+#    #+#             */
/*   Updated: 2022/01/11 13:56:46 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
 *	Creates a BMP of the game over screen and save it in root
 */
static void	print_screen_shot(t_doom *doom, int *i)
{
	char	*name;
	t_bmp	*bmp;

	GET_ROOT();
	name = ft_sprintf("%s/Doom%d.bmp", doom->root, rand() % 0xFFFF);
	bmp = pix_to_bmp(doom->surface->w, doom->surface->h, 3,
			doom->surface->pixels);
	write_bmp(name, bmp);
	free_bmp(bmp);
	free(name);
	*i = TRUE;
	Mix_PlayChannel(CHANNEL_TTS, doom->sound[WAV_SCREEN_SHOT], 0);
	Mix_VolumeChunk(doom->sound[WAV_SCREEN_SHOT], 128);
}

/*
 *	Blits game_over.bxmp to screen.
 */
static void	blit_title(t_doom *doom, SDL_Rect *dst, int i)
{
	t_bxpm	bxpm;

	if (i > 0)
	{
		Mix_PlayChannel(CHANNEL_MUSIC, doom->sound[WAV_NEW_ROUND], 0);
		GET_PATH("resources/BXPM/GameOver.bxpm");//fix
	}
	else
	{
		Mix_PlayChannel(CHANNEL_MUSIC, doom->sound[WAV_PLAYER_DEATH], 0);
		GET_PATH("resources/BXPM/GameOver.bxpm");
	}
	if (!read_bxpm(&bxpm, doom->root))
		LG_ERROR("Failed to open: %s\n", doom->root);
	*dst = (SDL_Rect){doom->surface->w * 0.05, doom->surface->h * 0.05,
		bxpm.w, bxpm.h};
	blit_bxpm(doom->surface, &bxpm, dst->x, dst->y);
	dst->x += 20;
	free(bxpm.pix);
	free(bxpm.clr);
}

/*
 *	Draws the game stats: Rounds Survived and Enemies Killed.
 *	TODO: Find a better colour for "Press Enter..."
 */
static void	blit_stats(t_doom *doom, SDL_Rect *dst, char *str)
{
	SDL_Color	clr;
	SDL_Surface	*surface;

	clr = hex_to_sdl_color(0xFFFFFFFF);
	if (doom->game.mode == ENDLESS)
	{
		str = ft_sprintf("Rounds Survived %d", doom->game.round);
		surface = TTF_RenderText_Blended(doom->font.amaz, str, clr);
		free(str);
		*dst = (SDL_Rect){dst->x, dst->y + dst->h, surface->w, surface->h};
		SDL_BlitSurface(surface, NULL, doom->surface, dst);
		SDL_FreeSurface(surface);
	}
	str = ft_sprintf("Enemies Killed: %d", doom->nb.kills);
	surface = TTF_RenderText_Blended(doom->font.amaz, str, clr);
	free(str);
	*dst = (SDL_Rect){dst->x, dst->y + dst->h, surface->w, surface->h};
	SDL_BlitSurface(surface, NULL, doom->surface, dst);
	SDL_FreeSurface(surface);
	str = get_elapsed_time_str(doom);
	surface = TTF_RenderText_Blended(doom->font.amaz, str, clr);
	free(str);
	*dst = (SDL_Rect){dst->x, dst->y + dst->h, surface->w, surface->h};
	SDL_BlitSurface(surface, NULL, doom->surface, dst);
	SDL_FreeSurface(surface);
}

/*
 *	Blit "'P' to Save Screen Shot" to surface.
 */
static void	blit_info(t_doom *doom)
{
	SDL_Color	clr;
	SDL_Rect	dstr;
	TTF_Font	*amaz;
	SDL_Surface	*surf;

	clr = hex_to_sdl_color(0xFFFFFFFF);
	surf = TTF_RenderText_Blended(doom->font.amaz,
			"Press Enter to Continue ", clr);
	dstr = (SDL_Rect){doom->surface->w - surf->w,
		doom->surface->h - surf->h, surf->w, surf->h};
	SDL_BlitSurface(surf, NULL, doom->surface, &dstr);
	SDL_FreeSurface(surf);
	GET_PATH("resources/TTF/digital.ttf");
	amaz = TTF_OpenFont(doom->root, 15);
	surf = TTF_RenderText_Blended(amaz, "'S' to Save Screen Shot", clr);
	dstr = (SDL_Rect){(dstr.x + dstr.w / 2) - surf->w / 2,
		doom->surface->h - surf->h - 5, surf->w, surf->h};
	SDL_BlitSurface(surf, NULL, doom->surface, &dstr);
	SDL_FreeSurface(surf);
	TTF_CloseFont(amaz);
}

/*
 *	Draws game over screen and handels events for exiting and screen shots.
 */
void	game_over(t_doom *doom)
{
	SDL_Rect	dst;
	SDL_Event	event;
	int			screen_shot;

	screen_shot = FALSE;
	blit_title(doom, &dst, doom->player.health);
	blit_stats(doom, &dst, NULL);
	blit_info(doom);
	update_screen(doom);
	while (1)
	{
		SDL_PollEvent(&event);
		if (event.key.keysym.sym == SDLK_RETURN)
			break ;
		if (event.key.keysym.sym == SDLK_s && !screen_shot)
			print_screen_shot(doom, &screen_shot);
	}
}
