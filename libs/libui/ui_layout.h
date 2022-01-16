/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_layout.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalmi <jsalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 19:23:36 by jsalmi            #+#    #+#             */
/*   Updated: 2021/12/18 10:06:50 by jsalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UI_LAYOUT_H
# define UI_LAYOUT_H
# include "libui.h"

typedef struct s_ui_layout	t_ui_layout;
typedef struct s_ui_element	t_ui_element;
typedef struct s_ui_window	t_ui_window;
typedef struct s_ui_recipe	t_ui_recipe;

/*
 * char		*root_dir;	all files/resources will be prefixed with this;
 * t_list	*windows;	t_ui_window;
 * t_list	*elements;	t_ui_element;
 * t_list	*families;	t_ui_family;
 * t_list	*recipes;	t_ui_recipe;
*/
struct s_ui_layout
{
	char			*root_dir;
	char			*layout_file;
	char			*layout_file_content;
	char			**layout_element_strings;
	char			*style_file;
	char			*style_file_content;
	char			**style_recipe_strings;
	t_list			*windows;
	t_list			*elements;
	t_list			*families;
	t_list			*recipes;
	char			**resource_dirs;
};

/*
 * t_list	*children;	t_ui_family;
*/
typedef struct s_ui_family
{
	char			*id;
	int				type;
	char			**children_strings;
	t_list			*children;
}					t_ui_family;

/*
 * int		value[3];		0 : value, 1 : min, 2 : max;
 * Uint32	input_type;		only numbers, only letters, only everything (default)
*/
typedef struct s_ui_recipe
{
	char			*id;
	t_vec4			pos;
	Uint32			bg_colors[UI_STATE_AMOUNT];
	char			*bg_images[UI_STATE_AMOUNT];
	int				z;
	bool			show;
	bool			pos_set[VEC4_SIZE];
	bool			bg_colors_set[UI_STATE_AMOUNT];
	bool			bg_images_set[UI_STATE_AMOUNT];
	bool			z_set;
	bool			show_set;
	char			*title;
	Uint32			text_color;
	int				text_size;
	int				text_align;
	int				text_style;
	char			*font;
	t_vec4			text_pos;
	bool			remove_title;
	bool			text_size_set;
	bool			text_color_set;
	bool			text_style_set;
	bool			text_align_set;
	bool			text_pos_set[VEC4_SIZE];
	int				value[3];
	int				value_set[3];
	char			**flags;
	bool			input_type_set;
	Uint32			input_type;
	char			*placeholder_text;
	char			*target;
}					t_ui_recipe;

///////////////
// Layout
///////////////
void				ui_layout_event(t_ui_layout *layout, SDL_Event e);
void				ui_layout_render(t_ui_layout *layout);
void				ui_layout_list_render(t_list *list);
void				ui_layout_load(t_ui_layout *layout, char *root_dir,
						char *file);
void				layout_apply_style(t_ui_layout *layout);
void				layout_make_recipes(t_ui_layout *layout);
void				layout_split_styles(t_ui_layout *layout);
void				layout_read_style(t_ui_layout *layout);
void				layout_compile_elements(t_ui_layout *layout);
void				layout_make_family_trees(t_ui_layout *layout);
void				layout_split_elements(t_ui_layout *layout);
void				layout_read_file(t_ui_layout *layout, char *file);
void				print_recipe(t_ui_recipe *recipe);
t_ui_window			*ui_layout_get_window(t_ui_layout *layout, char *id);
t_ui_element		*ui_layout_get_element(t_ui_layout *layout, char *id);
t_ui_recipe			*ui_layout_get_recipe(t_ui_layout *layout, char *id);
char				*ui_layout_get_file_from_resource_dirs(t_ui_layout *layout,
						char *file);
void				ui_layout_free(t_ui_layout *layout);

///////////////
// Recipe
///////////////
void				ui_recipe_free(void *recipe, size_t size);
void				ui_recipe_print(t_ui_recipe *recipe);

void				try_getting_xywh_separate(t_ui_recipe *recipe,
						char **key_value);
void				try_getting_xywh(t_ui_recipe *recipe,
						char **key_value);
void				try_getting_text_pos(t_ui_recipe *recipe,
						char **key_value);
void				try_getting_bgcolor_separate(t_ui_recipe *recipe,
						char **key_value);
void				try_getting_bgcolor(t_ui_recipe *recipe,
						char **key_value);
void				try_getting_bgimage_separate(t_ui_recipe *recipe,
						char **key_value);
void				try_getting_bgimage(t_ui_recipe *recipe,
						char **key_value);
void				try_getting_z_show(t_ui_recipe *recipe,
						char **key_value);
void				try_getting_text_stuff2(t_ui_recipe *recipe,
						char **key_value);
void				try_getting_text_stuff(t_ui_recipe *recipe,
						char **key_value);
void				try_getting_value(t_ui_recipe *recipe, char **key_value);
void				try_getting_flags(t_ui_recipe *recipe, char **key_value);
void				try_getting_input_stuff(t_ui_recipe *recipe,
						char **key_value);
void				try_getting_scrollbar_stuff(t_ui_recipe *recipe,
						char **key_value);
void				fill_recipe_from_args(t_ui_recipe *recipe, char **args);

void				recipe_pos_set_fill(t_ui_recipe *target,
						t_ui_recipe *child);
void				recipe_bgcolor_set_fill(t_ui_recipe *target,
						t_ui_recipe *child);
void				recipe_bgimage_set_fill(t_ui_recipe *target,
						t_ui_recipe *child);
void				recipe_z_show_set_fill(t_ui_recipe *target,
						t_ui_recipe *child);
void				recipe_text_stuff_set_fill2(t_ui_recipe *target,
						t_ui_recipe *child);
void				recipe_text_stuff_set_fill(t_ui_recipe *target,
						t_ui_recipe *child);
void				recipe_value_set_fill(t_ui_recipe *target,
						t_ui_recipe *child);
void				recipe_flag_set_fill(t_ui_recipe *target,
						t_ui_recipe *child);
void				fill_recipe_from_recipe(t_ui_recipe *target,
						t_ui_recipe *child);

///////////////
// Family
///////////////
t_ui_family			*make_family_from_string(char *str);
void				make_elements_from_family(t_list **list, void *parent,
						int parent_type, t_ui_family *family);
void				ui_family_free(void *family, size_t size);

void				make_family_from_children(t_list **list, void *parent,
						int parent_type, t_ui_family *family);

///////////////
// Help
///////////////
char				**split_string_into_array(char *str);
int					actual_word_count(char *str);
char				*get_file_content(t_ui_layout *layout, char *file);
int					get_special(t_ui_layout *layout, char *str);

#endif
