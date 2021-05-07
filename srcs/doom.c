/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 11:32:08 by nneronin          #+#    #+#             */
/*   Updated: 2021/05/07 15:16:30 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	init_doom(t_doom *doom, t_settings init)
{
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
	TTF_Init();
	Mix_Init(MIX_INIT_FLAC);
	doom->settings = init;
	doom->w2 = doom->settings.w / 2;
	doom->h2 = doom->settings.h / 2;

	doom->win = SDL_CreateWindow("DOOM", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			doom->settings.w, doom->settings.h, SDL_WINDOW_SHOWN);
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
	init_sound(doom);
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
	ft_putstr("a\n");
	DrawProjectiles(doom);
	ft_putstr("b\n");
	Drawsprite(doom);
	draw_crosshair(doom);
	blit_weapon(doom);	
	fps_func(doom);
	blit_fps(doom);
	if (doom->key.tab)
		map(doom);
	SDL_UpdateWindowSurface(doom->win);
}

int	game(char *map, t_settings init)
{
	t_doom		*doom;
    SDL_Event	event;

	if (!(doom = ft_memalloc(sizeof(t_doom))))
		return (0);
	if (!read_file(doom, map))
		return (0);
	init_doom(doom, init);
    while (!doom->quit)
		game_loop(doom, &event);
		//debug_loop(doom, &event);
	free_doom(doom);
	return (1);
}

void	launcher(void)
{
	char *arr[2];
	
	ft_putstr("here\n");
	arr[0] = ft_strdup(ROOT_PATH"ui/dialog");
	arr[1] = NULL;
	execv(arr[0], arr);
	free(&arr[0]);
}

int main(int ac, char **av)
{
	t_settings init;

	init.w = 1920;
	init.h = 1080;
	init.diff = 0;
	init.flag = 0;
	if (ac <= 1)
		return (ft_printf("{RED}[ERROR]{RESET} No map.\n"));
	if (ac >= 4)
	{
		init.w = ft_atoi(av[2]);
		init.h = ft_atoi(av[3]);
	}
	if (ac >= 5)
		init.diff = ft_atoi(av[4]);
	if (ac >= 6)
		init.flag = ft_atoi(av[5]);
	game(av[1], init);
	if (init.flag == 1)
		launcher();
	//while (1)
	//	;
	return (1);
}
