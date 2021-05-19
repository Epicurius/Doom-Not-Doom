/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 11:32:08 by nneronin          #+#    #+#             */
/*   Updated: 2021/05/19 16:33:29 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	launcher(void)
{
	char *arr[2];
	
	arr[0] = ft_strdup(ROOT_PATH"ui/dialog");
	arr[1] = NULL;
	execv(arr[0], arr);
	free(&arr[0]);
}

void	init_doom(t_doom *doom, t_settings init)
{
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
	TTF_Init();
	Mix_Init(MIX_INIT_FLAC);
	doom->settings = init;
	doom->settings.w = init.w;// * 0.666f;
	doom->settings.h = init.h;// * 0.666f;
	doom->w2 = doom->settings.w / 2;
	doom->h2 = doom->settings.h / 2;

	doom->win = SDL_CreateWindow("DOOM", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			init.w, init.h, SDL_WINDOW_SHOWN);//SDL_WINDOW_MOUSE_FOCUS
	if (!doom->win)
		error_msg("Could not create window: %s\n", SDL_GetError());

	doom->surface = SDL_CreateRGBSurfaceWithFormat(0, doom->settings.w, doom->settings.h,
			32, SDL_PIXELFORMAT_ARGB8888);
	if (!doom->surface)
		error_msg("Could not create surface: %s\n", SDL_GetError());

	doom->renderer = SDL_CreateRenderer(doom->win, -1, SDL_RENDERER_TARGETTEXTURE);//SDL_RENDERER_TARGETTEXTURE
	if (!doom->renderer)
		error_msg("Could not create renderer: %s\n", SDL_GetError());
	
	doom->texture = SDL_CreateTexture(doom->renderer, SDL_PIXELFORMAT_ARGB8888,
			SDL_TEXTUREACCESS_STREAMING, doom->settings.w, doom->settings.h);
	if (!doom->texture)
		error_msg("Could not create texture: %s\n", SDL_GetError());

	SDL_SetWindowDisplayMode(doom->win, NULL);
	SDL_SetRelativeMouseMode(SDL_TRUE);
	ft_set_icon(doom->win, GAME_PATH"resources/SpaceStudio.bmp");

	doom->nb.processors = ft_min(sysconf(_SC_NPROCESSORS_CONF), MAX_PROCESSORS);
	doom->nb.threads = doom->surface->w / 10;
	if (!init_tpool(&doom->tpool, doom->nb.processors))
		error_msg(NULL);
	init_fps(doom);
	init_weapons(doom);
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
		poll_event(doom, event);
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
	SDL_UpdateTexture(doom->texture, NULL, doom->surface->pixels, doom->surface->pitch);
	SDL_RenderCopy(doom->renderer, doom->texture, NULL, NULL);
	SDL_RenderPresent(doom->renderer);
}

//debug_loop(doom, &event);
void	game(char *map, t_settings init)
{
	t_doom		*doom;
    SDL_Event	event;

	doom = ft_memalloc(sizeof(t_doom));
	if (!doom)
		error_msg(init.flag, "Doom malloc.\n");
	read_file(doom, map);
	validate_map(doom);
	init_doom(doom, init);
    while (!doom->quit)
		game_loop(doom, &event);
	game_over(doom);
	free_doom(doom);
}

int main(int ac, char **av)
{
	t_settings init;

	//2560 1390
	init.w = 1920;
	init.h = 1080;
	init.diff = 0;
	init.flag = 0;
	if (ac <= 1)
		error_msg("No map.\n");
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
	return (1);
}
