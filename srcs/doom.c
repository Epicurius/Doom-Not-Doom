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

void	init_doom(t_doom *doom)
{
	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
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
	FPS.font = TTF_OpenFont("./bmp/digital.ttf", FPS_FONT_SIZE);
	FPS.color = hex_to_sdl_color(0x40eb34ff);
	doom->clock_font = TTF_OpenFont("./bmp/digital.ttf", 100);
	doom->win = SDL_CreateWindow("DOOM", 0, 0, W, H, SDL_WINDOW_SHOWN);
	doom->surface = SDL_GetWindowSurface(doom->win);
	doom->surface->userdata = doom->zbuffer;

	init_player(doom);
	init_camera(doom);
	init_skybox(doom);
	doom->nb.processors = min(sysconf(_SC_NPROCESSORS_CONF), MAX_PROCESSORS);
#ifndef JONY
	init_tpool(&doom->tpool, doom->nb.processors);
#endif
	//init_minimap(doom);
	load_textures(doom);
	init_scale(doom);
	init_entity_stats(doom);
}
	/*clock_gettime(_CLOCK_MONOTONIC, &start);
	clock_gettime(_CLOCK_MONOTONIC, &finish);
	elapsed = (finish.tv_sec - start.tv_sec);
	elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
	printf("%f\n", elapsed);*/

struct timespec start, finish;
double elapsed;
#include <time.h>
//Precompute takes 0,005% of fps


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
		reset_render_arrays(doom);
		update_camera(doom, 0, 0);
		precompute_walls(doom);
		precompute_skybox(doom);
		DrawScreen(doom);
		doom->player.shooting = 0;
		//precompute_entities(doom);
		//precompute_projectiles(doom);
		//DrawProjectiles(doom);
		//DrawEntity(doom);
		//if (doom->key.tab)
		//	map(doom);
		//shade_zbuffer(doom);

        	while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_KEYUP || event.type == SDL_KEYDOWN)
			{
				if (keys(doom, &event))
					break ;
			}
			else if (event.type == SDL_QUIT)
				exit (1);
		}
		movement(doom);
		vertical_collision(doom, &doom->player);
		horizontal_collision(doom, &doom->player);
		draw_crosshair(doom);
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
