/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Niklas Neronin <niklas.neronin@gmail.com>
 */

#ifndef LAUNCHER_H
# define LAUNCHER_H

# include "libft.h"
# include "libpf.h"
# include "libui.h"
# include <dirent.h>
# include <limits.h>

# define GRAYISH_BLUEISH 0xff505168
# define GREENISH 0xffb3c0a4

typedef struct s_settings
{
	int				fov;
	int				mouse_x;
	int				mouse_y;
	int				texture_scale;
	int				developer;
	int				width;
	int				height;
	int				difficulty;
}					t_settings;
/*
 * t_list			*menu_buttons; // t_ui_element *
 * t_list			*endless_map_buttons;
 * 						t_ui_element * (endless->menu->children) DONT FREE
 * t_list			*story_map_buttons; 
 * 						t_ui_element * (story->menu->children) DONT FREE
 * t_list			*story_map_names; // char *
 */
typedef struct s_launcher
{
	char			root[PATH_MAX];
	int				rlen;

	t_ui_layout		layout;

	t_ui_window		*win_main;

	t_ui_element	*main_menu;

	t_ui_element	*play_button;
	t_ui_element	*settings_button;
	t_ui_element	*quit_button;

	t_list			*menu_buttons;
	t_ui_element	*active_menu_button;

	t_ui_element	*play_menu;
	t_ui_element	*story_button;
	t_ui_element	*active_play_button;
	t_ui_element	*story_menu;
	t_ui_element	*difficulty_dropdown;

	t_ui_element	*settings_menu;
	t_ui_element	*fov_slider;
	t_ui_element	*mouse_x_slider;
	t_ui_element	*mouse_y_slider;
	t_ui_element	*texture_scale_slider;
	t_ui_element	*developer_checkbox;
	t_ui_element	*resolution_drop;
	t_settings		settings;

	t_list			*story_map_buttons;
	t_list			*story_map_names;
}					t_launcher;

// Play
void				play_menu_init(t_launcher *launcher);
void				play_events(t_launcher *launcher);
void				start_game(t_launcher *launcher, t_settings settings, char *map);

// Settings
void				settings_menu_init(t_launcher *launcher);
void				settings_events(t_launcher *launcher);
void				settings_init(t_settings *settings);
void				settings_elem_default(t_launcher *launcher);

// Map
void				map_init(t_launcher *launcher);
void				init_map_buttons_from_list(t_list *map_names,
						t_ui_recipe *rcp, t_ui_element *parent);

// Help
t_ui_element		*ui_list_get_clicked_element(t_list *list);
void				get_files_from_dir_with_file_ending(t_list **dest_list,
						char *directory, char *ending);
void				str_free(void *str, size_t size);
void				launcher_free(t_launcher *launcher);

#endif
