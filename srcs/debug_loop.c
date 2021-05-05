/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 12:37:23 by nneronin          #+#    #+#             */
/*   Updated: 2021/05/05 12:39:34 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

struct timespec start, finish;
double elapsed;
#include <time.h>

void	cs(void)
{
	//return ;
	clock_gettime(_CLOCK_MONOTONIC, &start);
}

void	ce(char *str)
{
	//return ;
	clock_gettime(_CLOCK_MONOTONIC, &finish);
	elapsed = (finish.tv_sec - start.tv_sec);
	elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
	ft_printf("%15s:\t%f\n", str, elapsed);
}

void	debug_loop(t_doom *doom, SDL_Event *event)
{
	cs();
	update_camera(doom, 0, 0);
	ce("update_camera");
	cs();
	precompute_walls(doom);
	ce("precompute_walls");
	cs();
	precompute_skybox(doom);
	ce("precompute_skybox");
	cs();
	DrawScreen(doom);
	ce("DRAW_SCREEN");
	/* All this has no time requirements */
	{
		cs();
		gamemode(doom);
		ce("gamemode");
		precompute_weapon(doom);
		cs();
		precompute_entities(doom);
		ce("precomp_entities");
		cs();
		precompute_projectiles(doom);
		ce("precomp_project");
		cs();
		movement(doom);
		ce("movement");
		cs();
		player_collision(doom);
		ce("player_collision");
		cs();
		while (SDL_PollEvent(event))
			keys(doom, event);
		ce("pollevent");
	}
	cs();
	tpool_wait(&doom->tpool);
	ce("DRAW_WAIT");
	cs();
	DrawProjectiles(doom);
	ce("draw_project");
	cs();
	Drawsprite(doom);//
	ce("draw_sprite");
	cs();
	draw_crosshair(doom);
	ce("Croshair");
	cs();
	blit_weapon(doom);
	ce("Blit_weapon");
	fps_func(doom);
	blit_fps(doom);
	if (doom->key.tab)
		map(doom);
	cs();
	SDL_UpdateWindowSurface(doom->win);
	ce("UpdateWindowSurface");
}
