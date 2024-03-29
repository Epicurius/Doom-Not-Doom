/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Niklas Neronin <niklas.neronin@gmail.com>
 */

#include "doom.h"

/*
 *	Updates the delta and current time.
 *	And updates the FPS (Window Title).
 */
void	update_fps(t_doom *doom)
{
	t_time		*time;
	int			prev;
	char		str[10];

	time = &doom->time;
	prev = time->curr;
	time->curr = SDL_GetTicks();
	time->delta = (time->curr - prev) / 1000.0f;
	time->fps++;
	if (time->curr - time->prev >= 1000)
	{
		time->prev = time->curr;
		ft_sprintf(str, "FPS: [%d]", time->fps);
		SDL_SetWindowTitle(doom->win, str);
		time->fps = 0;
	}
}

/*
 *	Inits the values for FPS.
 */
void	init_fps(t_doom *doom)
{
	doom->time.fps = 0;
	doom->time.curr = SDL_GetTicks();
	doom->time.prev = 0;
	doom->time.surf = NULL;
	doom->time.color = hex_to_sdl_color(0x8800FF00);
}
