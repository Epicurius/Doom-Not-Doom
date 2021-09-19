/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 11:32:08 by nneronin          #+#    #+#             */
/*   Updated: 2021/09/19 13:15:11 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
 *	Launch the DnD launcher if flag -launcher was passed.
 */
static void	launcher(void)
{
	char	*arr[2];

	arr[0] = ft_strdup(ROOT_PATH"/wolf3d");
	arr[1] = NULL;
	execv(arr[0], arr);
}

//void	ff_test_temp(t_doom *doom)
//{
//	if (doom->keys[SDL_SCANCODE_U])
//	{
//		for (int i = 0; i < 100; i++)
//			draw_line(doom->surface, 0xffff0000,
//				(t_point){0, rand() % 1079}, (t_point){1920, rand() % 1079});
//		int x, y;
//		SDL_GetMouseState(&x, &y);
//		ft_timer_start();
//		flood_fill(doom->surface, 0xff00ff00, x, y);
//		ft_printf("time: %f\n", ft_timer_end());
//		doom->keys[SDL_SCANCODE_U] = 0;
//	}	
//}

/*
 *	Main game loop that handles all of the games elements.
 */
static inline void	game_loop(t_doom *doom)
{
	game_mode(doom);
	map_events(doom);
	precompute_walls(doom);
	precompute_skybox(doom);
	draw_map(doom);
	precompute_weapon(doom);
	precompute_entities(doom);
	precompute_projectiles(doom);
	movement(doom);
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

/*
 *	Gets everything ready.
 *	SDL_Delay(doom.map.zoom * 2);
 */
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
		game_loop(&doom);
	if (doom.player.health <= 0)
		game_over(&doom);
	free_doom(&doom);
}

int	main(int ac, char **av)
{
	t_settings	settings;
	
	ft_printf("%d\n", sizeof(t_wall));
	ft_printf("%d\n", sizeof(t_bullet_hole));
	ft_printf("%d\n", sizeof(t_wsprite));
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
