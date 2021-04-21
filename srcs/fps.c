/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 10:58:35 by nneronin          #+#    #+#             */
/*   Updated: 2021/04/21 13:57:10 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void				fps_func(t_doom *doom)
{
	char		*str;
	t_fps		*fps;
	SDL_Rect	rect;

	fps = &doom->fps;
	fps->curr = SDL_GetTicks();
	fps->count++;
	if (fps->curr - fps->prev >= 1000)
	{
		fps->prev = fps->curr;
		fps->fps = fps->count;
		fps->count = 0;
		if (fps->surf != NULL)
			SDL_FreeSurface(fps->surf);
		str = ft_itoa(fps->fps);
		fps->surf = TTF_RenderText_Solid(fps->font, str, fps->color);
		free(str);
	}
	if (fps->surf == NULL)
		return ;
	rect = (SDL_Rect){.x = 0, .y = 0, .w = fps->surf->w, .h = fps->surf->h};
	SDL_BlitSurface(fps->surf, NULL, doom->surface, &rect);
}

void	init_fps(t_doom *doom)
{
	doom->fps.count = 0;
	doom->fps.surf = NULL;
	doom->fps.font = TTF_OpenFont("./resources/font/digital.ttf", FPS_FONT_SIZE);
	doom->fps.color = hex_to_sdl_color(0x40eb34ff);
}
