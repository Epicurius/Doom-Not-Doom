/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 10:58:35 by nneronin          #+#    #+#             */
/*   Updated: 2021/05/05 13:24:01 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	blit_fps(t_doom *doom)
{
	SDL_Rect dstr;
	SDL_Rect srcr;

	if (doom->time.surf == NULL)
		return ;
	dstr.x = 500;
	dstr.y = 0;
	dstr.w = 100;
	dstr.h = 75;
	srcr.x = 0;
	srcr.y = 0;
	srcr.w = doom->time.surf->w - 10;
	srcr.h = doom->time.surf->h - 10;
	//SDL_BlitScaled(doom->time.surf, &srcr, doom->surface, &dstr);
	SDL_BlitSurface(doom->time.surf, NULL, doom->surface, NULL);


	SDL_Surface *temp;
	SDL_Surface *surf;
	char *str;
	str = ft_itoa(doom->player.hp);
	temp = TTF_RenderText_Solid(doom->time.font, str, doom->time.color);
	surf = SDL_ConvertSurface(temp, doom->surface->format, 0);
	SDL_BlitSurface(surf, NULL, doom->surface, &dstr);
	free(str);
	SDL_FreeSurface(temp);
	SDL_FreeSurface(surf);
}

void	update_fps_surface(t_time *time)
{
	char	*str;

	str = ft_itoa(time->fps);
	if (time->surf != NULL)
		SDL_FreeSurface(time->surf);
	time->surf = TTF_RenderText_Solid(time->font, str, time->color);
	free(str);
}

void				fps_func(t_doom *doom)
{
	t_time		*time;
	SDL_Rect	rect;

	time = &doom->time;
	time->curr = SDL_GetTicks();
	time->fps++;
	if (time->curr - time->prev >= 1000)
	{
		time->prev = time->curr;
		update_fps_surface(&doom->time);
		time->fps = 0;
	}
}

void	init_fps(t_doom *doom)
{
	doom->time.fps = 0;
	doom->time.curr = SDL_GetTicks();
	doom->time.prev = 0;
	doom->time.surf = NULL;
	doom->time.font = TTF_OpenFont("./resources/TTF/digital.ttf", 100);
	doom->time.color = hex_to_sdl_color(0x40eb34ff);
}
