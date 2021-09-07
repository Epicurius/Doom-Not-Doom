/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buy_menu.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 10:40:21 by jsalmi            #+#    #+#             */
/*   Updated: 2021/09/07 12:01:15 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buymenu.h"
#include "libgfx.h"

void	init(t_buymenu *buymenu, t_bui_window *win)
{
	menu_init(win, buymenu);
	exit_button_init(buymenu);
	currency_init(buymenu);
	weapon_stats_init(buymenu);
	player_stats_init(buymenu);
	weapon_menu_init(buymenu);
	weapon_upgrades_init(buymenu);
	player_menu_init(buymenu);
}

void	events(t_bui_libui *libui, t_buymenu *buymenu, t_inv *inv)
{
	if (bui_button(buymenu->exit_button))
		libui->run = 0;
	weapon_buying_events(buymenu, inv);
	weapon_stat_events(buymenu, inv);
	weapon_upgrading_events(buymenu, inv);
	player_stat_events(buymenu, inv);
	player_upgrading_events(buymenu, inv);
}

void	buymenu_new(SDL_Window *window, SDL_Renderer *renderer,
	SDL_Surface *surface, t_inv *inv)
{
	t_buymenu		*buymenu;
	SDL_Texture		*texture;
	t_bui_libui		*libui;
	t_bui_window	*win;
	int w, h;
	
	SDL_GetWindowSize(window, &w, &h);
	libui = bui_new_libui();
	win = bui_new_window_from_window(libui, window, surface);
	win->update = 0;
	buymenu = buymenu_init();
	//SDL_BlitSurface(win->active_surface, NULL, surface, NULL);
	//ft_printf("%d %d : %d %d\n", win->active_surface->w, win->active_surface->h, surface->w, surface->h);
	texture = SDL_CreateTextureFromSurface(renderer, win->active_surface);
	init(buymenu, win);
	give_weapon(buymenu, inv, WEAPON_SHOTGUN);
	while (libui->run)
	{
		bui_event_handler(libui);
		events(libui, buymenu, inv);
		bui_render(libui);
		SDL_UpdateTexture(texture, NULL, win->active_surface->pixels,
			win->active_surface->pitch);
		SDL_RenderCopy(renderer, texture, NULL, &(SDL_Rect){0, 0, w, h});
		SDL_RenderPresent(renderer);
	}
	SDL_DestroyTexture(texture);
	buymenu_quit(buymenu);
	bui_libui_quit(libui);
}
