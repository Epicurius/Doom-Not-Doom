/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Niklas Neronin <niklas.neronin@gmail.com>
 */

#include "doom.h"

static void	get_surface_center(t_doom *doom)
{
	doom->c.x = (doom->settings.size.x * doom->settings.rres) / 2;
	doom->c.y = (doom->settings.size.y * doom->settings.rres) / 2;
	doom->c.z = doom->c.y * doom->surface->w + doom->c.x;
}

#if _WIN32
#  include <Windows.h>
#endif

static void	init_threading(t_doom *doom)
{
#if __APPLE__ || __linux__
	doom->nb.processors = sysconf(_SC_NPROCESSORS_ONLN);
#elif _WIN32
	SYSTEM_INFO	sysinfo;

	GetSystemInfo(&sysinfo);
	doom->nb.processors = sysinfo.dwNumberOfProcessors;
#endif
	doom->nb.processors = ft_min(doom->nb.processors, MAX_PROCESSORS);
	doom->nb.threads = 64;
	if (!init_tpool(&doom->tpool, doom->nb.processors))
		LG_ERROR(NULL);
}

void	set_true_mouse(t_doom *doom)
{
	int	x;
	int	y;

	while (SDL_PollEvent(&(SDL_Event){}))
		;
	SDL_GetMouseState(&x, &y);
	if (!x && !y)
		SDL_WarpMouseInWindow(doom->win, 0, 0);
	SDL_SetRelativeMouseMode(SDL_TRUE);
}

void	init_doom(t_doom *doom)
{
	init_threading(doom);
	get_surface_center(doom);
	init_fps(doom);
	init_skybox(doom);
	init_weapons(doom);
	init_minimap(doom);
	init_textures(doom);
	init_scale(doom);
	init_player(doom);
	init_entities(doom);
	init_game_mode(doom);
	init_render(doom);
	init_inventory(doom);
	init_slope_normal(doom);
	set_true_mouse(doom);
	init_camera(doom);
	init_sound(doom);
}
