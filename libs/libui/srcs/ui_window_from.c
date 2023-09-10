/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Jony Salmi <jony.salmi@gmail.com>
 */

#include "libui.h"

/*
 * Create a t_ui_window from SDL_Window
 *
 * Not sure yet if its libuis job to free the sdl window and renderer...
*/
void	ui_window_new_from(t_ui_window *win, SDL_Window *window)
{
	t_vec4i	pos;

	memset(win, 0, sizeof(t_ui_window));
	win->win = window;
	win->title = ft_strdup(SDL_GetWindowTitle(win->win));
	SDL_GetWindowPosition(win->win, &pos.x, &pos.y);
	SDL_GetWindowSize(win->win, &pos.w, &pos.h);
	win->pos = vec4(pos.x, pos.y, pos.w, pos.h);
	win->renderer = SDL_GetRenderer(win->win);
	if (!win->renderer)
		win->renderer = SDL_CreateRenderer(win->win, -1,
				SDL_RENDERER_ACCELERATED);
	win->texture = ui_create_texture(win->renderer, vec2i(pos.w, pos.h));
	win->window_id = SDL_GetWindowID(win->win);
	win->screen_pos = vec4i(0, 0, pos.w, pos.h);
	win->show = 1;
	win->children = NULL;
	win->texture_scale = vec2(win->screen_pos.w / win->pos.w,
			win->screen_pos.h / win->pos.h);
	SDL_GetMouseState(&win->window_mouse_pos.x, &win->window_mouse_pos.y);
	win->mouse_pos.x = win->window_mouse_pos.x * win->texture_scale.x;
	win->mouse_pos.y = win->window_mouse_pos.y * win->texture_scale.y;
	win->bg_color = 0xff000000;
	win->free_me = 1;
	win->textures_recreate = 1;
}