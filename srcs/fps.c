/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                              :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 10:58:35 by nneronin          #+#    #+#             */
/*   Updated: 2021/05/20 11:56:47 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	blit_fps(t_doom *doom)
{
	if (doom->time.surf == NULL)
		return ;
	SDL_BlitSurface(doom->time.surf, NULL, doom->surface, NULL);
}

void	update_fps_surface(t_time *time)
{
	char	*str;

	str = ft_itoa(time->fps);
	if (time->surf != NULL)
		SDL_FreeSurface(time->surf);
	time->surf = TTF_RenderText_Blended(time->font, str, time->color);
	free(str);
}

void				fps_func(t_doom *doom)
{
	t_time		*time;

	time = &doom->time;
	time->delta = (SDL_GetTicks() - time->curr) / 1000.0f;
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
	doom->time.font = TTF_OpenFont(GAME_PATH"resources/TTF/digital.ttf", 100);
	doom->time.color = hex_to_sdl_color(0x8800FF00);
}
