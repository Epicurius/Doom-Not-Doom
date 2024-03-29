/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Jony Salmi <jony.salmi@gmail.com>
 */

#include "libui.h"

int	make_usable_win_flags(char	**flags)
{
	int		result;
	int		i;

	result = 0;
	i = -1;
	while (flags && flags[++i])
	{
		if (ft_strequ(flags[i], "hide"))
			result |= UI_WINDOW_HIDE;
		else if (ft_strequ(flags[i], "show"))
			result |= UI_WINDOW_SHOW;
		else if (ft_strequ(flags[i], "maximize"))
			result |= UI_WINDOW_MAXIMIZE;
		else if (ft_strequ(flags[i], "minimize"))
			result |= UI_WINDOW_MINIMIZE;
		else if (ft_strequ(flags[i], "fullscreen"))
			result |= UI_WINDOW_FULLSCREEN;
		else if (ft_strequ(flags[i], "fullscreen_windowed"))
			result |= UI_WINDOW_FULLSCREEN_WINDOWED;
		else if (ft_strequ(flags[i], "grab"))
			result |= UI_WINDOW_GRAB;
		else if (ft_strequ(flags[i], "resizeable"))
			result |= UI_WINDOW_RESIZEABLE;
	}
	return (result);
}

void	ui_window_edit(t_ui_window *win, t_ui_recipe *recipe)
{
	t_vec4	pos;
	int		i;

	pos = win->pos;
	i = -1;
	while (++i < VEC4_SIZE)
	{
		if (recipe->pos_set[i])
			pos.v[i] = recipe->pos.v[i];
	}
	ui_window_pos_set(win, pos);
	if (recipe->texture_size_set[0])
		pos.w = recipe->texture_size.v[0];
	if (recipe->texture_size_set[1])
		pos.h = recipe->texture_size.v[1];
	ui_window_texture_pos_set(win, vec2i(pos.w, pos.h));
	if (recipe->title)
		ui_window_title_set(win, recipe->title);
	if (recipe->bg_colors_set[UI_STATE_DEFAULT])
		win->bg_color = recipe->bg_colors[UI_STATE_DEFAULT];
	if (ft_strinarr("xhides", recipe->flags))
		win->hide_on_x = 1;
	if (ft_strinarr("xdoesn'thides", recipe->flags))
		win->hide_on_x = 0;
	ui_window_flag_set(win, make_usable_win_flags(recipe->flags));
}
