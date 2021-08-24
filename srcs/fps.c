/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 10:58:35 by nneronin          #+#    #+#             */
/*   Updated: 2021/08/24 14:27:46 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

inline int	ticks_elapsed(int curr_tick, int start_tick, int ticks)
{
	return (((curr_tick - start_tick) % TICKS_PER_SEC) > (TICKS_PER_SEC / ticks));
}

//int	get_curr_tick()
//{
//	return ((SDL_GetTicks() * TICKS_PER_SEC) / 1000.0f);
//}

/*
 *	Updates the delta and current time.
 *	And updates the window title FPS.
 */
void	fps_func(t_doom *doom)
{
	t_time		*time;
	int			prev;
	char		*str;

	time = &doom->time;
	prev = time->curr;
	time->curr = SDL_GetTicks();
	time->delta = (time->curr - prev) / 1000.0f;
	//time->tick = time->curr * TICKS_PER_SEC / 1000.0f;
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
