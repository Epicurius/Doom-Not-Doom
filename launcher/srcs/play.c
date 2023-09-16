/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Niklas Neronin <niklas.neronin@gmail.com>
 */

#include "launcher.h"

void	play_menu_init(t_launcher *launcher)
{
	launcher->play_menu
		= ui_layout_get_element(&launcher->layout, "play_menu");
	launcher->story_menu
		= ui_layout_get_element(&launcher->layout, "story_menu");
	launcher->story_button
		= ui_layout_get_element(&launcher->layout, "story_button");
	launcher->active_play_button = launcher->story_button;
	launcher->difficulty_dropdown
		= ui_layout_get_element(&launcher->layout, "difficulty_dropdown");
	ui_dropdown_activate(launcher->difficulty_dropdown,
		ui_list_get_element_by_id(
			ui_dropdown_get_menu_element(launcher->difficulty_dropdown)
			->children, "normal_button"));
}

void	play_events(t_launcher *launcher)
{
	t_ui_element	*clicked_map;
	char			*diff_text;

	if (ui_dropdown_exit(launcher->difficulty_dropdown))
	{
		diff_text = ui_button_get_text(
				ui_dropdown_active(launcher->difficulty_dropdown));
		if (ft_strequ(diff_text, "Normal"))
			launcher->settings.difficulty = 2;
		else if (ft_strequ(diff_text, "Hard"))
			launcher->settings.difficulty = 3;
		else if (ft_strequ(diff_text, "Easy"))
			launcher->settings.difficulty = 1;
		else
			launcher->settings.difficulty = 2;
	}
	clicked_map = NULL;
	if (launcher->story_menu->show)
		clicked_map = ui_list_get_clicked_element(
				launcher->story_map_buttons);
	if (clicked_map)
		start_game(launcher, launcher->settings,
			ui_button_get_text(clicked_map));
}

void	start_game(t_launcher *launcher, t_settings settings, char *map)
{
	char	**args;

	args = ft_memalloc(sizeof(char *) * 10);
	ft_strcpy(&launcher->root[launcher->rlen], "doom-game");
	args[0] = ft_sprintf("%s", launcher->root);
	ft_strcpy(&launcher->root[launcher->rlen], "resources/MAPS/");
	args[1] = ft_sprintf("%s%s", launcher->root, map);
	args[2] = ft_sprintf("-size=%dx%d", settings.width, settings.height);
	args[3] = ft_sprintf("-res=%.2f",
			ceil((float)settings.texture_scale / 10) / 10);
	args[4] = ft_sprintf("-mouse=%.3fx%.3f",
			(float)settings.mouse_x / 1000,
			(float)settings.mouse_y / 1000);
	args[5] = ft_sprintf("-diff=%d", settings.difficulty);
	args[6] = ft_sprintf("-fov=%d", settings.fov);
	args[7] = ft_strdup("-launcher");
	if (settings.developer)
		args[8] = ft_strdup("-debug");
	args[9] = NULL;
	launcher_free(launcher);
	execv(args[0], args);
	ft_arraydel(args);
}
