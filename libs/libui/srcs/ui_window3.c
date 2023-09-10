/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Jony Salmi <jony.salmi@gmail.com>
 */

#include "libui.h"

void	ui_window_title_set(t_ui_window *win, const char *title)
{
	if (win->title)
		ft_strdel(&win->title);
	win->title = ft_strdup(title);
	SDL_SetWindowTitle(win->win, title);
}

void	ui_window_id_set(t_ui_window *win, const char *id)
{
	if (!id)
		return ;
	if (win->id)
		ft_strdel(&win->id);
	win->id = ft_strdup(id);
}

void	ui_window_set_icon(t_ui_window *win, char *path)
{
	SDL_Surface	*surface;

	if (!win || !path || !win->win)
	{
		if (!win)
			ft_printf("[%s] No win.\n", __FUNCTION__);
		else if (!path)
			ft_printf("[%s] No image path.\n", __FUNCTION__);
		else if (!win->win)
			ft_printf("[%s] No win->win.\n", __FUNCTION__);
		return ;
	}
	surface = ui_surface_image_new(path);
	if (!surface)
	{
		ft_printf("[%s] Failed creating surface from path.\n", __FUNCTION__);
		return ;
	}
	SDL_SetWindowIcon(win->win, surface);
	SDL_FreeSurface(surface);
}

void	ui_window_print(t_ui_window *win)
{
	ft_printf("[%s]\n", __FUNCTION__);
	ft_printf("\tid : %s\n", win->id);
	ft_printf("\tpos : ");
	print_vec(win->pos.v, 4);
	ft_printf("\tscreen_pos : ");
	print_veci(win->screen_pos.v, 4);
	ft_printf("\ttexture_scale : ");
	print_vec(win->texture_scale.v, 2);
}
