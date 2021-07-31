/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 11:32:08 by nneronin          #+#    #+#             */
/*   Updated: 2021/07/31 17:52:23 by nneronin         ###   ########.fr       */
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
	{
		Mix_PlayChannel(CHANNEL_MUSIC, doom->sound[WAV_MAIN_THEME], -1);
		Mix_Volume(CHANNEL_MUSIC, 50);
		//Mix_Volume(CHANNEL_WEAPON, 10);
	}
}

struct timespec begin, end;
double elapsed;

static inline void	game_loop(t_doom *doom)
{
	int i = 0;
	//ft_printf("%d\n", i++);
	game_mode(doom);
	//ft_printf("%d\n", i++);
	map_events(doom);
	//ft_printf("%d\n", i++);
	precompute_walls(doom);
	//ft_printf("%d\n", i++);
	precompute_skybox(doom);
	//ft_printf("%d\n", i++);
	draw_screen(doom);//4
	//ft_printf("%d\n", i++);
	sound_board(doom);
	//ft_printf("%d\n", i++);
	precompute_weapon(doom);
	//ft_printf("%d\n", i++);
	precompute_entities(doom);
	//ft_printf("%d\n", i++);
	precompute_projectiles(doom);
	//ft_printf("%d\n", i++);
	movement(doom);//9 9
	//ft_printf("%d\n", i++);
	poll_event(doom);//10 10 10
	//ft_printf("%d\n", i++);
	if (!tpool_wait(&doom->tpool))//11 11
		ft_putstr("asdasdasd\n");
	//ft_printf("%d\n", i++);
	draw_projectiles(doom);
	//ft_printf("%d\n", i++);
	draw_entities(doom);
	//ft_printf("%d\n", i++);
	draw_crosshair(doom);
	//ft_printf("%d\n", i++);
	draw_hud(doom);
	//ft_printf("%d\n", i++);
	draw_weapon(doom);
	//ft_printf("%d\n", i++);
	fps_func(doom);
	//ft_printf("%d\n", i++);
	map(doom);
	//ft_printf("%d\n", i++);
	update_screen(doom, doom->surface);
	//ft_printf("%d\n", i++);
	game_pause(doom);
	//ft_printf("%d\n", i++);
	game_quit(doom);
	//ft_printf("%d\n", i++);
}

static void	game(char *map, t_settings settings)
{
	t_doom		doom;

	ft_bzero(&doom, sizeof(t_doom));
	doom.settings = settings;
	init_sdl(&doom);
	game_loading(&doom);
	read_file(&doom, map);
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
