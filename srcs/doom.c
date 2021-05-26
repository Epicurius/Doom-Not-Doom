/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 11:32:08 by nneronin          #+#    #+#             */
/*   Updated: 2021/05/26 20:58:56 by nneronin         ###   ########.fr       */
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

void	game_loading(t_doom *doom)
{
	SDL_Event	event;
	t_bxpm		*bxpm;

	bxpm = malloc(sizeof(t_bxpm));
	read_bxpm(bxpm, GAME_PATH"resources/BXPM/game_loading.bxpm");
	blit_bxpm(doom->surface, bxpm, doom->surface->w / 2 - bxpm->w / 2,
									doom->surface->h / 2 - bxpm->h / 2);
	update_screen(doom, doom->surface);
	SDL_PollEvent(&event);
	SDL_RaiseWindow(doom->win);
	free_bxpm(bxpm);
}

void	init_sdl(t_doom *doom, t_settings init)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO))
		error_msg("Could not init SDL: %s\n", SDL_GetError());
	if (TTF_Init())
		error_msg("Could not init TTF: %s\n", SDL_GetError());
	if (Mix_Init(MIX_INIT_FLAC)&MIX_INIT_FLAC != MIX_INIT_FLAC)
		error_msg("Could not init MIX: %s\n", SDL_GetError());
	doom->win = SDL_CreateWindow("DOOM", SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, init.display_w, init.display_h, SDL_WINDOW_ALWAYS_ON_TOP);
	if (!doom->win)
		error_msg("Could not create window: %s\n", SDL_GetError());
	doom->surface = SDL_CreateRGBSurfaceWithFormat(0,
			init.display_w * init.render_resolution,
			init.display_h * init.render_resolution,
			32, SDL_PIXELFORMAT_ARGB8888);
	if (!doom->surface)
		error_msg("Could not create surface: %s\n", SDL_GetError());
	doom->renderer = SDL_CreateRenderer(doom->win, -1,
			SDL_RENDERER_TARGETTEXTURE);
	if (!doom->renderer)
		error_msg("Could not create renderer: %s\n", SDL_GetError());	
	doom->texture = SDL_CreateTexture(doom->renderer, SDL_PIXELFORMAT_ARGB8888,
			SDL_TEXTUREACCESS_STREAMING, doom->surface->w, doom->surface->h);
	if (!doom->texture)
		error_msg("Could not create texture: %s\n", SDL_GetError());
	SDL_SetRelativeMouseMode(SDL_TRUE);
	game_loading(doom);
	if (!set_icon(doom->win, GAME_PATH"resources/ICON/SpaceStudio.bmp"))
		error_msg("Could not set icon: %s\n", SDL_GetError());
	doom->font.amaz50 = TTF_OpenFont(GAME_PATH"resources/TTF/AmazDoom.ttf", 50);
	if (!doom->font.amaz50)
		error_msg("Could not open font: %s\n", TTF_GetError());
	doom->font.digi50 = TTF_OpenFont(GAME_PATH"resources/TTF/Digital.ttf", 50);
	if (!doom->font.digi50)
		error_msg("Could not open font: %s\n", TTF_GetError());
	doom->font.digi100 = TTF_OpenFont(GAME_PATH"resources/TTF/Digital.ttf", 100);
	if (!doom->font.digi100)
		error_msg("Could not open font: %s\n", TTF_GetError());
}

void	init_doom(t_doom *doom, t_settings init)
{
	doom->w2 = init.display_w * init.render_resolution / 2;
	doom->h2 = init.display_h * init.render_resolution / 2;
	doom->c = doom->h2 * doom->surface->w + doom->w2;
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
	init_inv(doom);
}

void	game_loop(t_doom *doom, SDL_Event *event)
{
	update_camera(doom, 0, 0);
	precompute_walls(doom);
	precompute_skybox(doom);
	DrawScreen(doom);
	/* All this has no time requirements */
	{
		//gamemode(doom);
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
	draw_hud(doom);
	draw_weapon(doom);	
	fps_func(doom);
	blit_fps(doom);
	if (doom->key.tab)
		map(doom);
	update_screen(doom, doom->surface);
	if (doom->key.p)
		game_pause(doom);
	else if (doom->quit == 1)
		game_quit(doom);
}


void	game(char *map, t_settings init)
{
	t_doom		*doom;
    SDL_Event	event;

	doom = ft_memalloc(sizeof(t_doom));
	if (!doom)
		error_msg("Doom malloc.\n");
	init_sdl(doom, init);
	read_file(doom, map);
	if (!validate_map(doom))
		return ;
	init_doom(doom, init);
    while (!doom->quit && doom->player.hp > 0)
		game_loop(doom, &event);
		//debug_loop(doom, &event);
	if (doom->player.hp <= 0)
		game_over(doom);
	free_doom(doom);
}

int main(int ac, char **av)
{
	t_settings init;




	//2560 1390
	init.display_w = 1920;
	init.display_h = 1080;
	init.render_resolution = 1.0f;
	init.difficulty = 0;
	init.flag = 0;
	if (ac <= 1)
		error_msg("No map.\n");
	if (ac >= 4)
	{
		conv();
		exit(1);
		init.display_w = ft_atoi(av[2]);
		init.display_h = ft_atoi(av[3]);
	}
	if (ac >= 5)
		init.difficulty = ft_atoi(av[4]);
	if (ac >= 6)
		init.flag = ft_atoi(av[5]);
	game(av[1], init);
	if (init.flag == 1)
		launcher();
	return (1);
}
