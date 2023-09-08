/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Jony Salmi <jony.salmi@gmail.com>
 */

#ifndef LIBUI_H
# define LIBUI_H

# define SDL_MAIN_HANDLED
# include "SDL2/SDL.h"
# include "SDL2/SDL_ttf.h"
# include "../libft/libft.h"
# include "../libpf/libpf.h"
# include "stdio.h"
# include "ui_enum.h"
# include "ui_vec.h"
# include "ui_layout.h"
# include "ui_elements.h"
# include "ui_load.h"
# include "math.h"
# include <fcntl.h>
# include <limits.h>

# define DEFAULT_TTF	"resources/TTF/"

typedef struct s_rgba
{
	union {
		struct {
			int	r;
			int	g;
			int	b;
			int	a;
		};
		int	rgba[4];
	};
}	t_rgba;

typedef struct s_ui_font
{
	char		*path;
	int			size;
	TTF_Font	*font;
}	t_ui_font;

// FONT
t_list					**ui_global_font(void);
TTF_Font				*ui_get_font(char *path, int size);
void					ui_global_font_free(void);

// Texture
SDL_Texture				*ui_texture_create_from_text_recipe(
							SDL_Renderer *renderer, t_ui_label *recipe);
void					ui_texture_print(SDL_Texture *texture);
SDL_Texture				*ui_create_texture(SDL_Renderer *renderer, t_vec2i pos);
void					ui_texture_draw_border(SDL_Renderer *renderer,
							SDL_Texture *texture, size_t thicc, Uint32 color);
void					ui_texture_fill(SDL_Renderer *renderer,
							SDL_Texture *texture, Uint32 color);
void					ui_texture_fill_rect(SDL_Renderer *renderer,
							SDL_Texture *texture, Uint32 color, t_vec4i rect);
SDL_Texture				*ui_texture_create_from_path(SDL_Renderer *renderer,
							char *path);

// Surface
SDL_Surface				*ui_surface_new(int w, int h);
void					ui_surface_fill(SDL_Surface *surface, Uint32 color);
void					ui_surface_fill_rect(SDL_Surface *surface, Uint32 color,
							t_vec4i rect);
SDL_Surface				*ui_surface_create_from_text_recipe(t_ui_label *recipe);
void					ui_surface_print(SDL_Surface *surface);
SDL_Surface				*ui_surface_text_new(char *text, char *font_path,
							int size, Uint32 font_color);
SDL_Surface				*ui_surface_image_new(char *image_path);
void					ui_surface_pixel_set(SDL_Surface *surface, int x, int y,
							Uint32 color);
Uint32					ui_surface_pixel_get(SDL_Surface *surface,
							int x, int y);
void					ui_surface_draw_border(SDL_Surface *surface,
							size_t thiccness, Uint32 color);
void					ui_surface_line_draw(SDL_Surface *surface,
							t_vec2i p1, t_vec2i p2, Uint32 color);
void					ui_surface_rect_draw(SDL_Surface *surface, t_vec2i p1,
							t_vec2i p2, Uint32 color);

void					ui_surface_rect_draw_filled(SDL_Surface *surface,
							t_vec2i p1, t_vec2i p2, Uint32 color);
void					ui_surface_circle_draw(SDL_Surface *surface,
							t_vec2i orig, int r, Uint32 color);
void					ui_surface_circle_draw_filled(SDL_Surface *surface,
							t_vec2i orig, int r, Uint32 color);
void					ui_surface_line_draw_thicc(SDL_Surface *surface,
							t_vec2i *points, int w, Uint32 color);

// Help
int						point_in_rect(t_vec2i point, t_vec4i rect);
int						rect_in_rect(t_vec4i rect1, t_vec4i rect2);
void					pointer_swap(void *p1, void *p2);
SDL_Rect				create_sdl_rect(int x, int y, int w, int h);
SDL_Color				rgba_to_sdl_color(t_rgba rgba);
t_rgba					hex_to_rgba(Uint32 color_hex);
Uint32					rgba_to_hex(t_rgba rgba);
Uint32					ui_color_change_brightness(Uint32 orig_col,
							float procentage);
char					*get_text_to_char_at_x(char *str, int x,
							TTF_Font *font);
int						get_x_of_char_in_text(char *str, int nth_char,
							TTF_Font *font);
int						get_nth_char_of_text_at_x(char *str, int x,
							TTF_Font *font);
t_ui_element			*ui_list_get_element_by_id(t_list *list, char *id);
t_ui_window				*ui_list_get_window_by_id(t_list *list, char *id);
void					ui_list_sort(t_list *list);
void					ui_list_event(t_list *list, SDL_Event e);
void					ui_list_render(t_list *list);
int						dist(t_vec2i p1, t_vec2i p2);
float					fdist(t_vec2 p1, t_vec2 p2);
char					**ft_strsplitwhitespace(char *str);
char					*ft_supertrim(char *str);
char					**ft_strsplitfirstoccurence(char *str, char c);
char					**ft_strsplitfirstoccurenceor(char *str, char b,
							char c);
void					ft_strtrimwholearr(char **arr);
void					dummy_free_er(void *dont, size_t care);
char					**ft_arrdup(char **src);
int						ft_strinarr(char *str, char **arr);
char					**ft_arradd(char **arr, char *add);
void					ui_list_element_free(t_list	**list);

// Load
void					ui_print_accepted(void);
t_ui_recipe				*ui_list_get_recipe_by_id(t_list *list, char *id);
int						text_align_getter(char *str);
const char				*text_align_to_str(int text_align);

// Other
void					ui_sdl_init(void);
void					ui_sdl_free(void);

#endif
