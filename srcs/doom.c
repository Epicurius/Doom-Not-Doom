/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 11:32:08 by nneronin          #+#    #+#             */
/*   Updated: 2021/07/16 12:50:21 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	launcher(void)
{
	char	*arr[2];

	arr[0] = ft_strdup(ROOT_PATH"ui/dialog");
	arr[1] = NULL;
	execv(arr[0], arr);
	free(&arr[0]);
}

static void	sound_board(t_doom *doom)
{
	if (!Mix_Playing(CHANNEL_TTS) && !Mix_Playing(CHANNEL_MUSIC))
		Mix_PlayChannel(CHANNEL_MUSIC, doom->sound[WAV_MAIN_THEME], -1);
}

//buymenu_new(doom->win, doom->surface, doom->inv);
static inline void	game_loop(t_doom *doom, SDL_Event *event)
{
	update_camera(doom, 0, 0);
	map_events(doom);
	precompute_walls(doom);
	precompute_skybox(doom);
	draw_screen(doom);
	//game_mode(doom);
	sound_board(doom);
	precompute_weapon(doom);
	precompute_entities(doom);
	precompute_projectiles(doom);
	movement(doom);
	poll_event(doom, event);
	tpool_wait(&doom->tpool);
	draw_projectiles(doom);
	draw_sprites(doom);
	if (doom->key.tab)
	{
		float curr;
		float prev;

		curr = doom->time.curr;
		prev = doom->time.prev;
		SDL_SetRelativeMouseMode(SDL_FALSE);
		buymenu_new(doom->win, doom->renderer, doom->surface, &doom->inv);
		doom->key.tab = 0;
		ft_printf("{CLR:123}Aniem e best{RESET}\n");
		SDL_SetRelativeMouseMode(SDL_TRUE);
	}
	draw_crosshair(doom);
	draw_hud(doom);
	draw_weapon(doom);
	fps_func(doom);
	//map(doom);
	update_screen(doom, doom->surface);
	game_pause(doom);
	game_quit(doom);
}

static void	game(char *map, t_settings settings)
{
	t_doom		doom;
	SDL_Event	event;

	ft_bzero(&doom, sizeof(t_doom));
	doom.settings = settings;
	init_sdl(&doom);
	game_loading(&doom);
	read_file(&doom, map);
	if (!validate_map(&doom))
		return ;
	init_doom(&doom);
	while (!doom.quit && doom.player.hp > 0)
	{
		game_loop(&doom, &event);
		reload_map(&doom, map);
	}
	if (doom.player.hp <= 0)
		game_over(&doom);
	free_doom(&doom);
}

int	main(int ac, char **av)
{
	t_settings	settings;

	if (ac == 1)
		print_help_msg();
	args(ac, av, &settings);
	game(av[1], settings);
	if (settings.launcher)
		launcher();
	if (settings.debug)
		system("leaks doom");
	return (1);
}
