/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Jony Salmi <jony.salmi@gmail.com>
 */

#include "libui.h"

void	ui_window_new(t_ui_window *win, char *title, t_vec4 pos)
{
	memset(win, 0, sizeof(t_ui_window));
	if (!title)
		win->title = ft_strdup("Window Title Not Set");
	else
		win->title = ft_strdup(title);
	win->pos = pos;
	win->win = SDL_CreateWindow(win->title,
			win->pos.x, win->pos.y, win->pos.w, win->pos.h, 0);
	win->free_win = 1;
	win->renderer = SDL_CreateRenderer(win->win, -1, SDL_RENDERER_ACCELERATED);
	win->free_renderer = 1;
	win->texture = ui_create_texture(win->renderer, vec2i(pos.w, pos.h));
	win->show = 1;
	win->children = NULL;
	win->window_id = SDL_GetWindowID(win->win);
	win->screen_pos = vec4i(0, 0, pos.w, pos.h);
	win->texture_scale = vec2(win->screen_pos.w / win->pos.w,
			win->screen_pos.h / win->pos.h);
	SDL_GetMouseState(&win->window_mouse_pos.x, &win->window_mouse_pos.y);
	win->mouse_pos.x = win->window_mouse_pos.x * win->texture_scale.x;
	win->mouse_pos.y = win->window_mouse_pos.y * win->texture_scale.y;
	win->bg_color = 0xff000000;
	win->free_me = 1;
	win->textures_recreate = 1;
}

/*
 * Copy the win->texture to the window.
 * Clear the renderer and fill with win color.
 * Reset some stuff that need to be reset every frame.
*/
int	ui_window_render(t_ui_window *win)
{
	t_rgba	rgba;

	rgba = hex_to_rgba(win->bg_color);
	SDL_SetRenderDrawColor(win->renderer, rgba.r, rgba.g, rgba.b, rgba.a);
	SDL_SetRenderTarget(win->renderer, NULL);
	SDL_RenderClear(win->renderer);
	SDL_RenderCopy(win->renderer, win->texture, NULL, NULL);
	SDL_RenderPresent(win->renderer);
	SDL_SetRenderTarget(win->renderer, win->texture);
	SDL_RenderClear(win->renderer);
	SDL_SetRenderTarget(win->renderer, NULL);
	win->textures_recreate = 0;
	win->mouse_pos_prev = win->mouse_pos;
	win->scroll = 0;
	win->mouse_down_last_frame = 0;
	return (1);
}

void	ui_window_free(void *window, size_t size)
{
	t_ui_window	*win;

	win = window;
	if (!win)
		return ;
	ft_strdel(&win->id);
	ft_strdel(&win->title);
	ui_list_element_free(&win->children);
	SDL_DestroyTexture(win->texture);
	if (win->free_renderer)
		SDL_DestroyRenderer(win->renderer);
	if (win->free_win)
		SDL_DestroyWindow(win->win);
	win->layout = NULL;
	if (win->free_me)
		free(win);
	(void)size;
}

/*
 * This function should probably be called right after loading the ui,
 * otherwise you might save the ui_window to a variable that is used
 * somewhere else, or renderer...
 *
 * NOTE:
 * 	1. we will sdl_win associated renderer if it has one, otherwise make one;
*/
void	ui_window_replace_win(t_ui_window *ui_win, SDL_Window *sdl_win)
{
	t_vec4i	pos;

	ui_win->free_win = 0;
	if (ui_win->renderer)
		SDL_DestroyRenderer(ui_win->renderer);
	if (ui_win->win)
		SDL_DestroyWindow(ui_win->win);
	ui_win->win = sdl_win;
	SDL_GetWindowPosition(ui_win->win, &pos.x, &pos.y);
	SDL_GetWindowSize(ui_win->win, &pos.w, &pos.h);
	ui_win->pos = vec4(pos.x, pos.y, pos.w, pos.h);
	ui_win->renderer = SDL_GetRenderer(ui_win->win);
	if (!ui_win->renderer)
		ui_win->renderer
			= SDL_CreateRenderer(sdl_win, -1, SDL_RENDERER_ACCELERATED);
	else
		ui_win->free_renderer = 0;
	ui_win->texture = ui_create_texture(ui_win->renderer,
			vec2i(ui_win->pos.w, ui_win->pos.h));
	ui_win->window_id = SDL_GetWindowID(ui_win->win);
	ui_win->screen_pos.w = pos.w;
	ui_win->screen_pos.h = pos.h;
	ui_win->texture_scale = vec2(ui_win->screen_pos.w / ui_win->pos.w,
			ui_win->screen_pos.h / ui_win->pos.h);
	ui_win->textures_recreate = 1;
}

void	ui_window_render_texture(t_ui_window *win, SDL_Texture *texture)
{
	SDL_SetRenderTarget(win->renderer, win->texture);
	SDL_RenderCopy(win->renderer, texture, NULL, NULL);
	SDL_SetRenderTarget(win->renderer, NULL);
}
