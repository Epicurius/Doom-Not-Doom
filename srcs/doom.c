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

static void unload_data(t_doom *doom)
{
    for (unsigned a=0; a<SECTORNUM; ++a)
		free(doom->sectors[a].vertex);
    for (unsigned a=0; a<SECTORNUM; ++a)
		free(doom->sectors[a].neighbors);
    free(doom->sectors);
    doom->sectors  = NULL;
    SECTORNUM = 0;
}

void	init_doom(t_doom *doom)
{
	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
	TTF_Init();
	bzero(doom, sizeof(t_doom));
	PLAYER.falling = 1;

	FPS.curr = SDL_GetTicks();
	FPS.font = TTF_OpenFont("./bmp/Minecraft.ttf", 20);
	doom->win = SDL_CreateWindow("DOOM", 0,
				0, W, H, SDL_WINDOW_SHOWN);
	//doom->rend = SDL_CreateRenderer(doom->win, -1, 0); //combine win and renderer
	//doom->tx = SDL_CreateTexture(doom->rend, SDL_PIXELFORMAT_ARGB8888,
	//					SDL_TEXTUREACCESS_STREAMING, W, H);
	doom->surface = SDL_GetWindowSurface(doom->win);
	doom->surface->userdata = doom->pz;
	//doom->surface = SDL_CreateRGBSurface(0, W, H, 32, 0, 0, 0, 0);
	doom->texture[0] = IMG_Load("./bmp/alloy.bmp");
	doom->texture[1] = IMG_Load("./bmp/grass.bmp");
	doom->texture[2] = IMG_Load("./bmp/ceiling.bmp");
	doom->texture[3] = IMG_Load("./bmp/stone.bmp");
	doom->imp = IMG_Load("./bmp/doom_imp.bmp");
	doom->key.t = 0;
}

int main(int ac, char **av)
{
	t_doom		*doom;
    	SDL_Event	event;
	
	if (!(doom = (t_doom *)malloc(sizeof(t_doom))))
		return (0);
	init_doom(doom);
	init_tpool(&doom->tpool, THREADS_NB);
	if (!read_file(doom, "./new.txt"))
		return (0);
	SDL_SetRelativeMouseMode(SDL_TRUE);
    	while (!doom->quit)
    	{
		DrawScreen(doom);
		if (doom->key.tab)
			DrawMap(doom);
		vertical_collision(doom);
		horizontal_collision(doom);
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
		mouse_and_keys(doom);
		fps_func(doom);
		//SDL_RenderClear(doom->rend);
		//SDL_UpdateTexture(doom->tx, NULL, doom->surface->pixels, W * sizeof(Uint32));
		//SDL_RenderClear(doom->rend);
		//SDL_RenderCopy(doom->rend, doom->tx, NULL, NULL);
		//SDL_RenderPresent(doom->rend);
		SDL_UpdateWindowSurface(doom->win);
	}	
	free_tpool(&doom->tpool);
    	//unload_data(doom);
    	SDL_Quit();
	TTF_Quit();
	IMG_Quit();
	return (0);
}
