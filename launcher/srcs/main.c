/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Niklas Neronin <niklas.neronin@gmail.com>
 */

#include "launcher.h"

void	user_events(t_launcher *launcher)
{
	ui_list_radio_event(launcher->menu_buttons, &launcher->active_menu_button);
	launcher->play_menu->show
		= launcher->active_menu_button == launcher->play_button;
	launcher->settings_menu->show
		= launcher->active_menu_button == launcher->settings_button;
	if (launcher->play_menu->show)
	{
		if (launcher->story_button->state == UI_STATE_CLICK)
			launcher->active_play_button = launcher->story_button;
		launcher->story_menu->show
			= launcher->active_play_button == launcher->story_button;
		play_events(launcher);
	}
	if (launcher->settings_menu->show)
		settings_events(launcher);
}

void	main_menu_init(t_launcher *launcher)
{
	launcher->main_menu
		= ui_layout_get_element(&launcher->layout, "main_menu");
	launcher->play_button
		= ui_layout_get_element(&launcher->layout, "play_button");
	launcher->settings_button
		= ui_layout_get_element(&launcher->layout, "settings_button");
	add_to_list(&launcher->menu_buttons,
		launcher->play_button, sizeof(t_ui_element));
	add_to_list(&launcher->menu_buttons,
		launcher->settings_button, sizeof(t_ui_element));
	launcher->quit_button
		= ui_layout_get_element(&launcher->layout, "quit_button");
}

void	launcher_init(t_launcher *launcher)
{
	ft_memset(launcher, 0, sizeof(t_launcher));
	launcher->rlen = get_root(launcher->root, PATH_MAX);
	ui_layout_load(&launcher->layout, launcher->root, "resources/UI/launcher.ui");
	if (!launcher->layout.style_file_content
		|| !launcher->layout.layout_file_content)
	{
		ft_printf("[%s] Layout couldnt be loaded.\n", __FUNCTION__);
		exit (0);
	}
	launcher->win_main = ui_layout_get_window(&launcher->layout, "win_main");
	ft_strcpy(&launcher->root[launcher->rlen], "resources/ICON/DNDl.bmp");
	ui_window_set_icon(launcher->win_main, launcher->root);
	main_menu_init(launcher);
	play_menu_init(launcher);
	settings_menu_init(launcher);
	map_init(launcher);
	settings_init(launcher);
	settings_elem_default(launcher);
}

void	launcher_free(t_launcher *launcher)
{
	ui_layout_free(&launcher->layout);
	ft_lstdel(&launcher->menu_buttons, &dummy_free_er);
	ft_lstdel(&launcher->story_map_names, &str_free);
	ui_sdl_free();
}

int	main(void)
{
	t_launcher	launcher;
	SDL_Event	e;

	lg_setLevel(LEVEL_WARN, LEVEL_INFO);
	if (!lg_openFile("launcher/launcher.log", "a+"))
		return (0);
	ui_sdl_init();
	launcher_init(&launcher);
	while (!launcher.win_main->wants_to_close
		&& launcher.quit_button->state != UI_STATE_CLICK)
	{
		while (SDL_PollEvent(&e))
		{
			ui_layout_event(&launcher.layout, e);
			user_events(&launcher);
			if (e.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
				launcher.win_main->wants_to_close = 1;
		}
		ui_texture_fill(launcher.win_main->renderer,
			launcher.win_main->texture, 0xff00ff00);
		ui_layout_render(&launcher.layout);
	}
	launcher_free(&launcher);
	lg_closeFile();
	return (0);
}
