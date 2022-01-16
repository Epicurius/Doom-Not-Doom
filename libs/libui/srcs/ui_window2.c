/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_window2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalmi <jsalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 19:24:58 by jsalmi            #+#    #+#             */
/*   Updated: 2021/12/10 19:33:36 by jsalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

void	ui_window_texture_redo(t_ui_window *win)
{
	if (!win)
	{
		ft_printf("[%s] Error : No window.\n", __FUNCTION__);
		return ;
	}
	if (win->texture)
		SDL_DestroyTexture(win->texture);
	win->texture = SDL_CreateTexture(win->renderer, SDL_PIXELFORMAT_ARGB8888,
			SDL_TEXTUREACCESS_TARGET, win->screen_pos.w, win->screen_pos.h);
	win->texture_scale = vec2(win->screen_pos.w / win->pos.w,
			win->screen_pos.h / win->pos.h);
}

/*
 * Change the position of the actual window : win->pos;
*/
void	ui_window_pos_set(t_ui_window *win, t_vec4 pos)
{
	if (win->pos.x != pos.x || win->pos.y != pos.y)
	{
		win->pos.x = pos.x;
		win->pos.y = pos.y;
		SDL_SetWindowPosition(win->win, win->pos.x, win->pos.y);
	}
	if (win->pos.w != pos.w || win->pos.h != pos.h)
	{
		win->pos.w = pos.w;
		win->pos.h = pos.h;
		SDL_SetWindowSize(win->win, win->pos.w, win->pos.h);
		win->texture_scale = vec2(win->screen_pos.w / win->pos.w,
				win->screen_pos.h / win->pos.h);
	}
}

void	ui_window_texture_pos_set(t_ui_window *win, t_vec2i pos)
{
	if (pos.x != win->screen_pos.w || pos.y != win->screen_pos.h)
	{
		win->screen_pos
			= vec4i(win->screen_pos.x, win->screen_pos.y, pos.x, pos.y);
		ui_window_texture_redo(win);
	}
}

int	choose_fullscreen_mode(t_ui_window *win)
{
	int	curr_flags;

	curr_flags = SDL_GetWindowFlags(win->win);
	if (curr_flags & SDL_WINDOW_FULLSCREEN)
		return (0);
	return (SDL_WINDOW_FULLSCREEN);
}

void	ui_window_flag_set(t_ui_window *win, int flags)
{
	if (flags & UI_WINDOW_HIDE)
		SDL_HideWindow(win->win);
	if (flags & UI_WINDOW_SHOW)
		SDL_ShowWindow(win->win);
	if (flags & UI_WINDOW_RAISE)
		SDL_RaiseWindow(win->win);
	if (flags & UI_WINDOW_MAXIMIZE)
		SDL_MaximizeWindow(win->win);
	if (flags & UI_WINDOW_MINIMIZE)
		SDL_MinimizeWindow(win->win);
	if (flags & UI_WINDOW_FULLSCREEN)
		SDL_SetWindowFullscreen(win->win, choose_fullscreen_mode(win));
	if (flags & UI_WINDOW_FULLSCREEN_WINDOWED)
		SDL_SetWindowFullscreen(win->win, SDL_WINDOW_FULLSCREEN_DESKTOP);
	if (flags & UI_WINDOW_GRAB)
		SDL_SetWindowGrab(win->win, SDL_TRUE);
	if (flags & UI_WINDOW_RESIZEABLE)
		SDL_SetWindowResizable(win->win, SDL_TRUE);
}
