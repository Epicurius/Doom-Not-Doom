/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Jony Salmi <jony.salmi@gmail.com>
 */

#include "libui.h"

void	ui_window_resize_event(t_ui_window *win)
{
	t_vec2i	new_pos;

	SDL_GetWindowSize(win->win, &new_pos.x, &new_pos.y);
	win->pos.w = new_pos.x;
	win->pos.h = new_pos.y;
	win->texture_scale = vec2(win->screen_pos.w / win->pos.w,
			win->screen_pos.h / win->pos.h);
	win->textures_recreate = 1;
}

void	ui_window_window_events(t_ui_window *win, SDL_Event e)
{
	win->wants_to_close = 0;
	if (e.window.event == SDL_WINDOWEVENT_RESIZED)
		ui_window_resize_event(win);
	else if (e.window.event == SDL_WINDOWEVENT_CLOSE)
	{
		if (win->hide_on_x)
			ui_window_flag_set(win, UI_WINDOW_HIDE);
		win->wants_to_close = 1;
	}
	else if (e.window.event == SDL_WINDOWEVENT_SHOWN)
		win->show = 1;
	else if (e.window.event == SDL_WINDOWEVENT_HIDDEN)
		win->show = 0;
}

void	ui_window_mouse_events(t_ui_window *win)
{
	SDL_GetMouseState(&win->window_mouse_pos.x, &win->window_mouse_pos.y);
	win->mouse_pos.x = win->window_mouse_pos.x * win->texture_scale.x;
	win->mouse_pos.y = win->window_mouse_pos.y * win->texture_scale.y;
}

void	ui_window_keydown_events(t_ui_window *win, SDL_Event e)
{
	int	modkey;

	modkey = SDL_GetModState();
	if (modkey & KMOD_LALT)
	{
		if (e.key.keysym.scancode == SDL_SCANCODE_RETURN)
		{
			ui_window_flag_set(win, UI_WINDOW_FULLSCREEN);
			ui_window_resize_event(win);
		}
	}
	else if (modkey & KMOD_LCTRL)
	{
		if (e.key.keysym.scancode == SDL_SCANCODE_R)
			win->textures_recreate = 1;
	}
}

void	ui_window_event(t_ui_window *win, SDL_Event e)
{
	if (e.button.type == SDL_MOUSEBUTTONUP)
		win->mouse_down = 0;
	if (win->window_id != e.window.windowID)
		return ;
	if (e.type == SDL_WINDOWEVENT)
		ui_window_window_events(win, e);
	else if (e.type == SDL_MOUSEMOTION)
		ui_window_mouse_events(win);
	else if (e.type == SDL_MOUSEWHEEL)
		win->scroll = e.wheel.y;
	else if (e.type == SDL_KEYDOWN)
		ui_window_keydown_events(win, e);
	if (e.button.type == SDL_MOUSEBUTTONDOWN)
	{
		win->mouse_down = e.button.button;
		win->mouse_down_last_frame = win->mouse_down;
	}
}
