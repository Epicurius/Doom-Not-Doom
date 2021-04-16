/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 11:32:08 by nneronin          #+#    #+#             */
/*   Updated: 2020/11/26 14:58:23 by nneronin         ###   ########.fr       */
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
	elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
	printf("%s: %f\n", str, elapsed);
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

	//init_player1(doom);
	init_camera(doom);
	init_skybox(doom);
	doom->nb.processors = min(sysconf(_SC_NPROCESSORS_CONF), MAX_PROCESSORS);
	init_tpool(&doom->tpool, doom->nb.processors);
	init_minimap(doom);
	cs();
	load_textures(doom);
	ce("load textures");
	init_scale(doom);
	init_entity_stats(doom);
}

int main1(void)
{
	t_doom		*doom;
    	SDL_Event	event;

	if (!(doom = ft_memalloc(sizeof(t_doom))))
		return (0);
	if (!read_file(doom, "./skybox.txt"))
		return (0);
	ft_putstr("Done with read_map.\n");
	init_doom(doom);
	ft_putstr("Done with init_doom.\n");
	SDL_SetRelativeMouseMode(SDL_TRUE);
    	while (!doom->quit)
    	{
		cs();
		reset_render_arrays(doom);
		ce("1");
		cs();
		update_camera(doom, 0, 0);
		ce("2");
		cs();
		precompute_walls(doom);
		ce("3");
		cs();
		precompute_skybox(doom);
		ce("4");
		cs();
		DrawScreen(doom);//
		ce("5");
		cs();
		doom->player.shooting = 0;
		precompute_entities(doom);
		ce("6");
		cs();
		precompute_projectiles(doom);
		ce("7");
		cs();
		DrawProjectiles(doom);
		ce("8");
		cs();
		DrawEntity(doom);//
		ce("10");
		cs();
		if (doom->key.tab)
			map(doom);
		//shade_zbuffer(doom);
		ce("11");
		cs();
        	while (SDL_PollEvent(&event))//
		{
			if (event.type == SDL_KEYUP || event.type == SDL_KEYDOWN)
			{
				if (keys(doom, &event))
					break ;
			}
			else if (event.type == SDL_QUIT)
				exit (1);
		}
		ce("12");
		cs();
		movement(doom);
		ce("13");
		cs();
		player_collision(doom);
		ce("14");
		cs();
		draw_crosshair(doom);
		//asd(doom->surface, &doom->mtx[2]);
		ce("15");
		fps_func(doom);
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
