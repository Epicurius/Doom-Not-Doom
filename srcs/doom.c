/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 11:32:08 by nneronin          #+#    #+#             */
/*   Updated: 2021/04/19 16:34:38 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "doom.h"


struct timespec start, finish;
double elapsed;
#include <time.h>
//Precompute takes 0,005% of fps

void	cs(void)
{
	return ;
	clock_gettime(_CLOCK_MONOTONIC, &start);
}

void	ce(char *str)
{
	return ;
	clock_gettime(_CLOCK_MONOTONIC, &finish);
	elapsed = (finish.tv_sec - start.tv_sec);
	//elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
	elapsed += (finish.tv_nsec - start.tv_nsec) / 10000.0;
	printf("%.10s:\t%f\n", str, elapsed);
}

void	init_doom(t_doom *doom)
{
	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();
	if (!(doom->ytop = ft_memalloc(sizeof(int) * W)))
		return ;
	if (!(doom->ybot = ft_memalloc(sizeof(int) * W)))
		return ;
	if (!(doom->zbuffer = ft_memalloc(sizeof(double) * (W * H))))
		return ;
	doom->w2 = W/2;
	doom->h2 = H/2;

	FPS.count = 0;
	FPS.surf = NULL;
	FPS.font = TTF_OpenFont("./resources/font/digital.ttf", FPS_FONT_SIZE);
	FPS.color = hex_to_sdl_color(0x40eb34ff);
	doom->clock_font = TTF_OpenFont("./resources/font/digital.ttf", 100);
	doom->win = SDL_CreateWindow("DOOM", 0, 0, W, H, SDL_WINDOW_SHOWN);
	doom->surface = SDL_GetWindowSurface(doom->win);
	doom->surface->userdata = doom->zbuffer;
	SDL_SetRelativeMouseMode(SDL_TRUE);

	doom->nb.processors = min(sysconf(_SC_NPROCESSORS_CONF), MAX_PROCESSORS);
	init_tpool(&doom->tpool, doom->nb.processors);
	init_camera(doom);
	init_skybox(doom);
	init_minimap(doom);
	init_textures(doom);
	init_scale(doom);
	init_entity(doom);
}

int main1(void)
{
	t_doom		*doom;
    SDL_Event	event;

	if (!(doom = ft_memalloc(sizeof(t_doom))))
		return (0);
	cs();
	if (!read_file(doom, "./skybox.txt"))
		return (0);
	ce("Read_file");
	cs();
	init_doom(doom);
	ce("init_doom");
    while (!doom->quit)
    {
		cs();
        while (SDL_PollEvent(&event))
				keys(doom, &event);
		ce("SDL_Events");
		cs();
		reset_render_utils(doom);
		ce("reset_render_arrays");
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
		DrawScreen(doom);//
		ce("DrawScreen");
		cs();
		precompute_entities(doom);
		ce("precomp_entities");
		cs();
		precompute_projectiles(doom);
		ce("precomp_project");
		cs();
		DrawProjectiles(doom);
		ce("draw_project");
		cs();
		DrawEntity(doom);//
		ce("Draw_entity");
		//shade_zbuffer(doom);
		ce("Tab_function");
		cs();
		movement(doom);
		ce("movement");
		cs();
		player_collision(doom);
		ce("player_collision");
		cs();
		draw_crosshair(doom);
		ce("Croshair");
		fps_func(doom);
		if (doom->key.tab)
			map(doom);
		SDL_UpdateWindowSurface(doom->win);
	}
	free_doom(doom);
	return (0);
}

int main(void)
{
	main1();
	//while (1)
	//	;
	return (1);
}
