/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 11:32:08 by nneronin          #+#    #+#             */
/*   Updated: 2021/06/17 10:42:38 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	launcher(void)
{
	char	*arr[2];

	arr[0] = ft_strdup(ROOT_PATH"ui/dialog");
	arr[1] = NULL;
	execv(arr[0], arr);
	free(&arr[0]);
}

void	game_loop(t_doom *doom, SDL_Event *event)
{
	update_camera(doom, 0, 0);
	precompute_walls(doom);
	precompute_skybox(doom);
	DrawScreen(doom);
	/*All this has no time requirements*/
	//gamemode(doom);
	precompute_weapon(doom);
	precompute_entities(doom);
	precompute_projectiles(doom);
	movement(doom);
	player_collision(doom);
	poll_event(doom, event);
	/*--------------------------------*/
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

	doom = ft_pmalloc(sizeof(t_doom), "Doom");
	init_sdl(doom, init);
	game_loading(doom);
	read_file(doom, map);
	if (!validate_map(doom))
		return ;
	init_doom(doom, init);
	while (!doom->quit && doom->player.hp > 0)
		game_loop(doom, &event);
	if (doom->player.hp <= 0)
		game_over(doom);
	free_doom(doom);
}

int	main(int ac, char **av)
{
	t_settings	init;
	
	/*double d;
	t_v3 a = {9, 2, 7};
	t_v3 b = {4, 8, 10};
	t_v3 c;

	d = vectors_angle(a, b);
	d = dot_product_v3(a, b);
	d = vectors_angle(a, b);
	printf("%f %f %f | %f\n", c.x, c.y, c.z, d);
	exit(1);*/


	init.display_w = 1920;
	init.display_h = 1080;
	init.render_resolution = 1;
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
