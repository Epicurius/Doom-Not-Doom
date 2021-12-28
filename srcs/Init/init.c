/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 09:15:26 by nneronin          #+#    #+#             */
/*   Updated: 2021/12/28 16:18:1 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	get_surface_center(t_doom *doom)
{
	doom->c.x = (doom->settings.size.x * doom->settings.rres) / 2;
	doom->c.y = (doom->settings.size.y * doom->settings.rres) / 2;
	doom->c.z = doom->c.y * doom->surface->w + doom->c.x;
}

static void	init_threading(t_doom *doom)
{
	doom->nb.processors = ft_min(sysconf(_SC_NPROCESSORS_CONF), MAX_PROCESSORS);
	//ft_printf("%d\n", doom->nb.processors);
	doom->nb.threads = 64;
	if (!init_tpool(&doom->tpool, doom->nb.processors))
		error_msg(NULL);
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

int	multithread_idk3(void *arg)
{
	int	i;
	Mix_Chunk **dest;

	dest = arg;
	i = -1;
	while (++i < WAV_AMOUNT)
	{
		dest[g_sounds[i].id] = Mix_LoadWAV(g_sounds[i].path);
		if (dest[g_sounds[i].id] == NULL)
		{
			ft_printf("Reading[%d]: %s", g_sounds[i].id, g_sounds[i].path);
			return (0);
		}
	}
	return (1);
}

void	init_doom(t_doom *doom)
{
	//ft_timer_start();
	init_threading(doom);
	
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
		error_msg("Mix_OpenAudio: %s\n", Mix_GetError());
	Mix_AllocateChannels(32);
	tpool_add(&doom->tpool, multithread_idk3, &doom->sound);

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
	//ft_printf("%f\n", ft_timer_end());
}
