/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 11:32:08 by nneronin          #+#    #+#             */
/*   Updated: 2020/10/24 16:15:03 by nneronin         ###   ########.fr       */
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
	doom->win = SDL_CreateWindow("DOOM", SDL_WINDOWPOS_CENTERED,
				SDL_WINDOWPOS_CENTERED, W, H, SDL_WINDOW_SHOWN);
	doom->surface = SDL_GetWindowSurface(doom->win);
	doom->txtx = IMG_Load("./bmp/stone.bmp");
	doom->txtx1 = IMG_Load("./bmp/grass.bmp");
	doom->txtx2 = IMG_Load("./bmp/alloy.bmp");
	doom->key.t = 1;
}

int main()
{
	t_doom		*doom;
    SDL_Event	event;
	
	if (!(doom = (t_doom *)malloc(sizeof(t_doom))))
		return (0);
	init_doom(doom);
	read_file(doom, "./idea.txt");
	SDL_SetRelativeMouseMode(SDL_TRUE);
    while (!doom->quit)
    {
		//ft_timer_start();
        DrawScreen(doom);
		//printf("Time: %f\n", ft_timer_end());
		DrawMap(doom);
		fps_func(doom);
		SDL_UpdateWindowSurface(doom->win);
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
        //SDL_Delay(10);
    }
    unload_data(doom);
    SDL_Quit();
	TTF_Quit();
	IMG_Quit();
    return (0);
}
