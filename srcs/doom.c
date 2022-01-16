/*
 * https://github.com/Epicurius/Doom-Not-Doom
 * 
 * Created: 2020/10/08 11:32:08 nneronin
 * Updated: 2022/01/16 12:50:02 Niklas Neronin
 */

#include "doom.h"

/*
 *	Launch the DnD launcher if flag -launcher was passed.
 */
static void	launcher(void)
{
	char *const	arr[] = {"../wolf3d", NULL};

	execv(arr[0], arr);
}

/*
 *	Main game loop that handles all of the games elements.
 *	For implementing a fps cap.
 *	HostFilterTime (10000 millis / 80 fps = 12.5)
 *	if (SDL_GetTicks() - doom->time.curr < 12) 
 *		return ;
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
	map(doom);
	update_fps(doom);
	update_screen(doom);
	game_quit(doom);
}

/*
 *	Gets everything ready.
 *	SDL_Delay(ft_clamp(0, 50, doom.map.zoom * 2));
 */
static void	game(char *map, t_settings settings)
{
	t_doom	doom;

	ft_bzero(&doom, sizeof(t_doom));
	get_root(doom.root, &doom.rlen);
	doom.settings = settings;
	init_sdl(&doom);
	game_loading(&doom);
	parse_map(&doom, map);
	if (!validate_map(&doom))
		return ;
	init_doom(&doom);
	while (!doom.quit && doom.player.health > 0)
		game_loop(&doom);
	if (doom.quit == 2 || doom.player.health <= 0)
		game_over(&doom);
	free_doom(&doom);
}

int	main(int ac, char **av)
{
	t_settings	settings;

	if (ac == 1)
		print_help_msg();
	lg_setLevel(LEVEL_WARN, LEVEL_INFO);
	if (!lg_openFile("log", "a+"))
		return (0);
	args(ac, av, &settings);
	game(av[1], settings);
	lg_closeFile();
	if (settings.debug)
		system("leaks doom");
	if (settings.launcher)
		launcher();
	return (1);
}
