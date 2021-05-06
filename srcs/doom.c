/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 11:32:08 by nneronin          #+#    #+#             */
/*   Updated: 2021/05/06 10:30:22 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	init_doom(t_doom *doom, t_settings *settings)
{
	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();
	doom->w2 = settings->width / 2;
	doom->h2 = settings->height / 2;

	doom->win = SDL_CreateWindow("DOOM", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			settings->width, settings->height, SDL_WINDOW_SHOWN);
	doom->surface = SDL_GetWindowSurface(doom->win);
	SDL_SetRelativeMouseMode(SDL_TRUE);

	doom->nb.processors = ft_min(sysconf(_SC_NPROCESSORS_CONF), MAX_PROCESSORS);
	doom->nb.threads = doom->surface->w / 10;
	printf("nb.processors %d, nb.threads %d\n", doom->nb.processors, doom->nb.threads);
	init_tpool(&doom->tpool, doom->nb.processors);
	init_fps(doom);
	init_camera(doom);
	init_skybox(doom);
	init_minimap(doom);
	init_textures(doom);
	init_scale(doom);
	init_player(doom);
	init_game_entity(doom);
	init_render(doom);
	init_gamemode(doom);
}

void	game_loop(t_doom *doom, SDL_Event *event)
{

	update_camera(doom, 0, 0);
	precompute_walls(doom);
	precompute_skybox(doom);
	DrawScreen(doom);
	/* All this has no time requirements */
	{
		gamemode(doom);
		precompute_weapon(doom);
		precompute_entities(doom);
		precompute_projectiles(doom);
		movement(doom);
		player_collision(doom);
		while (SDL_PollEvent(event))
			keys(doom, event);
	}
	tpool_wait(&doom->tpool);
	DrawProjectiles(doom);
	Drawsprite(doom);
	draw_crosshair(doom);
	blit_weapon(doom);	
	fps_func(doom);
	blit_fps(doom);
	if (doom->key.tab)
		map(doom);
	SDL_UpdateWindowSurface(doom->win);
}

int	game(t_settings *settings)
{
	t_doom		*doom;
    SDL_Event	event;

	if (!(doom = ft_memalloc(sizeof(t_doom))))
		return (0);
	if (!read_file(doom, settings->map))
		return (0);
	init_doom(doom, settings);
    while (!doom->quit)
		debug_loop(doom, &event);
	//	game_loop(doom, &event);
	free_doom(doom);
	return (1);
}


int main(void)
{
	t_settings settings;

	settings.map = ft_strdup("./resources/MAPS/skybox.txt");
	settings.width = 2560;
	settings.height = 1440;
	settings.mode = 1;
	settings.god = 0;
	game(&settings);
	return (1);
}
