/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 11:32:08 by nneronin          #+#    #+#             */
/*   Updated: 2021/07/25 17:23:29 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	launcher(void)
{
	char	*arr[2];

	arr[0] = ft_strdup(ROOT_PATH"ui/menu");
	arr[1] = NULL;
	execv(arr[0], arr);
}

static void	sound_board(t_doom *doom)
{
	if (!Mix_Playing(CHANNEL_TTS) && !Mix_Playing(CHANNEL_MUSIC))
		Mix_PlayChannel(CHANNEL_MUSIC, doom->sound[WAV_MAIN_THEME], -1);
}

static inline void	game_loop(t_doom *doom, SDL_Event *event)
{
	game_mode(doom);
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
	ft_putstr("1\n");
	doom.settings = settings;
	ft_putstr("2\n");
	init_sdl(&doom);
	ft_putstr("3\n");
	game_loading(&doom);
	ft_putstr("4\n");
	read_file(&doom, map);
	ft_putstr("5\n");
	if (!validate_map(&doom))
		return ;
	ft_putstr("6\n");
	init_doom(&doom);
	ft_putstr("7\n");
	while (!doom.quit && doom.player.health > 0)
	{
		game_loop(&doom, &event);
		reload_map(&doom, map);
	}
	ft_putstr("8\n");
	if (doom.player.health <= 0)
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
