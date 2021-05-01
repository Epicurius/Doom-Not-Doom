/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 10:58:35 by nneronin          #+#    #+#             */
/*   Updated: 2021/05/01 15:58:18 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	blit_fps(t_doom *doom)
{
	SDL_Rect dstr;
	SDL_Rect srcr;

	if (doom->time.surf == NULL)
		return ;
	dstr.x = 0;
	dstr.y = 0;
	dstr.w = 500;
	dstr.h = 500;
	srcr.x = 0;
	srcr.y = 0;
	srcr.w = doom->time.surf->w - 10;
	srcr.h = doom->time.surf->h - 10;
	//SDL_BlitScaled(doom->time.surf, &srcr, doom->surface, &dstr);
	SDL_BlitSurface(doom->time.surf, NULL, doom->surface, NULL);
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
	doom->time.font = TTF_OpenFont("./resources/font/digital.ttf", 100);
	doom->time.color = hex_to_sdl_color(0x40eb34ff);
}
