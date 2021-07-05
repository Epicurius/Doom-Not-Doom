/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 10:58:35 by nneronin          #+#    #+#             */
/*   Updated: 2021/07/05 15:35:52 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	blit_fps(t_doom *doom)
{
	if (doom->time.surf == NULL)
		return ;
	SDL_BlitSurface(doom->time.surf, NULL, doom->surface, NULL);
}

static void	update_fps_surface(char *str, TTF_Font *font, t_time *time)
{
	if (time->surf != NULL)
		SDL_FreeSurface(time->surf);
	time->surf = TTF_RenderText_Blended(font, str, time->color);
}

void	fps_func(t_doom *doom)
{
	t_time		*time;
	double		prev;
	char		*str;

	time = &doom->time;
	prev = time->curr;
	time->curr = SDL_GetTicks();
	time->delta = (time->curr - prev) / 1000.0f;
	time->fps++;
	if (time->curr - time->prev >= 1000)
	{
		time->prev = time->curr;
		str = ft_sprintf("FPS: [%d]", time->fps);
		SDL_SetWindowTitle(doom->win, str);
		free(str);
		time->fps = 0;
	}
}

void	init_fps(t_doom *doom)
{
	doom->time.fps = 0;
	doom->time.curr = SDL_GetTicks();
	doom->time.prev = 0;
	doom->time.surf = NULL;
	doom->time.color = hex_to_sdl_color(0x8800FF00);
}
