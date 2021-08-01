/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 11:32:08 by nneronin          #+#    #+#             */
/*   Updated: 2021/08/01 16:23:20 by nneronin         ###   ########.fr       */
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
		Mix_Volume(CHANNEL_WEAPON, 50);
	}
}

static inline void	game_loop(t_doom *doom)
{
	int	i;

	i = 0;
	ft_printf("%d ", i++);
	game_mode(doom);
	ft_printf("%d ", i++);
	map_events(doom);
	ft_printf("%d ", i++);
	precompute_walls(doom);
	ft_printf("%d ", i++);
	precompute_skybox(doom);
	ft_printf("%d ", i++);
	draw_screen(doom);
	ft_printf("%d ", i++);
	sound_board(doom);
	ft_printf("%d ", i++);
	precompute_weapon(doom);
	ft_printf("%d ", i++);
	precompute_entities(doom);
	ft_printf("%d ", i++);
	precompute_projectiles(doom);
	ft_printf("%d ", i++);
	movement(doom);
	ft_printf("%d ", i++);//10
	poll_event(doom);
	ft_printf("%d ", i++);
	tpool_wait(&doom->tpool);
	ft_printf("%d ", i++);
	draw_projectiles(doom);
	ft_printf("%d ", i++);
	draw_entities(doom);
	ft_printf("%d ", i++);
	draw_crosshair(doom);
	ft_printf("%d ", i++);
	draw_hud(doom);
	ft_printf("%d ", i++);
	draw_weapon(doom);
	ft_printf("%d ", i++);
	fps_func(doom);
	ft_printf("%d ", i++);
	map(doom);
	ft_printf("%d ", i++);
	update_screen(doom);
	ft_printf("%d ", i++);
	game_pause(doom);
	ft_printf("%d ", i++);
	game_quit(doom);
	ft_printf("%d\n", i++);
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
