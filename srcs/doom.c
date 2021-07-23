/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 11:32:08 by nneronin          #+#    #+#             */
/*   Updated: 2021/07/23 08:46:04 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	sound_board(t_doom *doom)
{
	if (!Mix_Playing(CHANNEL_TTS) && !Mix_Playing(CHANNEL_MUSIC))
		Mix_PlayChannel(CHANNEL_MUSIC, doom->sound[WAV_MAIN_THEME], -1);
}

static inline void	game_loop(t_doom *doom, SDL_Event *event)
{
	game_mode_endless(doom);
	update_camera(doom, 0, 0);
	map_events(doom);
	precompute_walls(doom);
	precompute_skybox(doom);
	draw_screen(doom);
	sound_board(doom);
	precompute_weapon(doom);
	precompute_entities(doom);
	precompute_projectiles(doom);
	movement(doom);
	poll_event(doom, event);
	tpool_wait(&doom->tpool);
	draw_projectiles(doom);
	draw_entities(doom);
	draw_crosshair(doom);
	draw_hud(doom);
	draw_weapon(doom);
	fps_func(doom);
	map(doom);
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
		execv(g_launcher[0], g_launcher);
	if (settings.debug)
		system("leaks doom");
	return (1);
}
