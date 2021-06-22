/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 11:32:08 by nneronin          #+#    #+#             */
/*   Updated: 2021/06/22 12:02:57 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

//t_doom	*get_master(void)
//{
//	static t_doom	*master;
//
//	if (!master)
//		master = (t_doom *)ft_pmalloc(sizeof(t_doom), "Doom");
//	return (master);
//}
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

static void	game_loop(t_doom *doom, SDL_Event *event)
{
	update_camera(doom, 0, 0);
	precompute_walls(doom);
	precompute_skybox(doom);
	draw_screen(doom);
	game_mode(doom);
	sound_board(doom);
	precompute_weapon(doom);
	precompute_entities(doom);
	precompute_projectiles(doom);
	movement(doom);
	poll_event(doom, event);
	tpool_wait(&doom->tpool);
	draw_projectiles(doom);
	draw_sprites(doom);
	draw_crosshair(doom);
	draw_hud(doom);
	draw_weapon(doom);
	fps_func(doom);
	if (doom->key.tab)
		map(doom);
	update_screen(doom, doom->surface);
	if (doom->key.p)
		game_pause(doom);
	else if (doom->quit == 1)
		game_quit(doom);
}

static void	game(char *map, t_settings init)
{
	t_doom		*doom;
	SDL_Event	event;

	doom = ft_pmalloc(sizeof(t_doom), "Doom");
	init_sdl(doom, init);
	game_loading(doom);
	read_file(doom, map);
	if (!validate_map(doom))
		return ;
	init_doom(doom, init);
	while (!doom->quit && doom->player.hp > 0)
	{
		game_loop(doom, &event);
		if (doom->key.equal)
			reload_map(doom, map);
	}
	if (doom->player.hp <= 0)
		game_over(doom);
	free_doom(doom);
}

int	main(int ac, char **av)
{
	t_settings	init;

	init.display_w = 1920;
	init.display_h = 1080;
	init.render_resolution = 0.8;
	init.difficulty = 0;
	init.flag = 0;
	if (ac <= 1)
		error_msg("No map.\n");
	if (ac >= 4)
	{
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
