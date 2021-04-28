/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 11:32:08 by nneronin          #+#    #+#             */
/*   Updated: 2021/04/28 14:21:06 by nneronin         ###   ########.fr       */
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
	ft_printf("%.10s:\t%f\n", str, elapsed);
}

void	init_doom(t_doom *doom)
{
	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();
	//IMG_Init(IMG_INIT_JPG|IMG_INIT_PNG);
	doom->w2 = W/2;
	doom->h2 = H/2;

	doom->win = SDL_CreateWindow("DOOM", 0, 0, W, H, SDL_WINDOW_SHOWN);
	doom->surface = SDL_GetWindowSurface(doom->win);
	SDL_SetRelativeMouseMode(SDL_TRUE);

	doom->nb.processors = min(sysconf(_SC_NPROCESSORS_CONF), MAX_PROCESSORS);
	doom->nb.threads = W / 10;
	printf("nb.processors %d, nb.threads %d\n", doom->nb.processors, doom->nb.threads);
	init_tpool(&doom->tpool, doom->nb.processors);
	init_fps(doom);
	init_camera(doom);
	init_skybox(doom);
	init_minimap(doom);
	cs();
	init_textures(doom);
	ce("BXPM");
	init_scale(doom);
	init_entity(doom);
	init_render(doom);
	//((t_sprite*)doom->sprite->content)->type = 1;
}

int main(int ac, char **av)
{
	t_doom		*doom;
    SDL_Event	event;

	if (ac == 1)
		printf("%s\n", av[0]);
	if (!(doom = ft_memalloc(sizeof(t_doom))))
		return (0);
	cs();
	if (!read_file(doom, "skybox.txt"))
		return (0);
	ce("Read_file");
	init_doom(doom);
    //doom->quit = 1;
    while (!doom->quit)
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
		ce("DrawScreen");

		/* All this has no time requirements */
		{

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
			while (SDL_PollEvent(&event))
				keys(doom, &event);
			ce("WHILE DRAW");
		}
		cs();
		tpool_wait(&doom->tpool);
		ce("Draw tpool_wait");
		cs();
		DrawProjectiles(doom);
		ce("draw_project");
		cs();
		DrawEntity(doom);//
		ce("Draw_sprite");
		cs();
		//shade_zbuffer(doom);
		draw_crosshair(doom);
		ce("Croshair");
		fps_func(doom);
		if (doom->key.tab)
			map(doom);
		//shade_zbuffer(doom);
		cs();
		SDL_UpdateWindowSurface(doom->win);
		ce("UpdateWindowSurface");
	}
	free_doom(doom);
	return (1);
}
/*
int main(void)
{
	main1();
	//while (1)
	//	;
	return (1);
}*/
