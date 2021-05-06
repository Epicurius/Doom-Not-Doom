/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 11:32:08 by nneronin          #+#    #+#             */
/*   Updated: 2021/05/06 14:59:38 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	init_doom(t_doom *doom, int w, int h)
{
	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();
	doom->w2 = w / 2;
	doom->h2 = h / 2;

	doom->win = SDL_CreateWindow("DOOM", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			w, h, SDL_WINDOW_SHOWN);
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

int	doom(char *name, int w, int h)
{
	t_doom		*doom;
    SDL_Event	event;

	if (!(doom = ft_memalloc(sizeof(t_doom))))
		return (0);
	if (!read_file(doom, name))
		return (0);
	init_doom(doom, w, h);
    while (!doom->quit)
		debug_loop(doom, &event);
	//	game_loop(doom, &event);
	free_doom(doom);
	return (1);
}

int game(int ac, char **av)
{
	int w;
	int h;

	w = 1920;
	h = 1080;
	if (ac <= 1)
		return (ft_printf("{RED}[ERROR]{RESET} No map.\n"));
	if (ac >= 3)
	{
		w = ft_atoi(av[2]);
		h = ft_atoi(av[3]);
	}
	if (w > h)
		doom(av[1], w, h);
	else
		ft_printf("{RED}[ERROR]{RESET} Game does not support %d/%d aspect ratio\n", w, h);
	return (1);
}

int main(int ac, char **av)
{
	game(ac, av);
	return (1);
}
