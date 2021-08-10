/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 11:32:08 by nneronin          #+#    #+#             */
/*   Updated: 2021/08/10 16:34:04 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	launcher(void)
{
	char	*arr[2];

	arr[0] = ft_strdup(ROOT_PATH"/wolf3d");
	arr[1] = NULL;
	execv(arr[0], arr);
}

//static void	sound_board(t_doom *doom)
//{
//	//if (!Mix_Playing(CHANNEL_TTS) && !Mix_Playing(CHANNEL_MUSIC))
//	{
//		//Mix_PlayChannel(CHANNEL_MUSIC, doom->sound[WAV_MAIN_THEME], -1);
//		//Mix_Volume(CHANNEL_MUSIC, 10);
//		//Mix_Volume(CHANNEL_WEAPON, 50);
//	}
//}

//struct timespec start, finish;
//double elapsed;

static inline void	game_loop(t_doom *doom)
{
	game_mode(doom);
	map_events(doom);
	precompute_walls(doom);
	precompute_skybox(doom);
	draw_screen(doom);
	precompute_weapon(doom);
	precompute_entities(doom);
	precompute_projectiles(doom);
//clock_gettime(CLOCK_MONOTONIC, &start);
	movement(doom);
//clock_gettime(CLOCK_MONOTONIC, &finish);
//elapsed = (finish.tv_sec - start.tv_sec);
//elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
//ft_printf("%f\n", elapsed);
	poll_event(doom);
	tpool_wait(&doom->tpool);
	draw_projectiles(doom);
	draw_entities(doom);
	draw_crosshair(doom);
	draw_hud(doom);
	draw_weapon(doom);
	fps_func(doom);
	map(doom);
	update_screen(doom);
	game_pause(doom);
	game_quit(doom);
}

//	Crouch in small area and standup for insta death? Maybe fix?
static void	game(char *map, t_settings settings)
{
	t_doom		doom;

	ft_bzero(&doom, sizeof(t_doom));
	doom.settings = settings;
	init_sdl(&doom);
	game_loading(&doom);
	parse_map(&doom, map);
	if (!validate_map(&doom))
		return ;
	init_doom(&doom);
	while (!doom.quit && doom.player.health > 0)
	{
		game_loop(&doom);
		reload_map(&doom, map);
	}
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
