/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Authors: Jony Salmi <jony.salmi@gmail.com>
 *          Niklas Neronin <niklas.neronin@gmail.com>
 */

#include "libui.h"

/*
 * 1. First try to find with absolute path...
 * 2. ... if not found, try to find from UI_FONT_PATH/"font_name" ...
 * 3. ... if still not found, try to find default font.
 * 		IF this is not found, it's my fault.
 *
 * Seg faults if font_path == NULL;
*/
char	*get_font_path(char *font_path)
{
	char	root[PATH_MAX];
	int		len;

	len = get_root(root, PATH_MAX);
	if (access(font_path, F_OK))
		ft_strcpy(&root[len], font_path);
	else
		return (ft_strdup(font_path));
	if (access(root, F_OK))
	{
		ft_strcpy(&root[len], DEFAULT_TTF"DroidSans.ttf");
		if (!access(root, F_OK))
			return (ft_strdup(root));
		else
			return (NULL);
	}
	return (ft_strdup(root));
}

void	recreate_font_of_label(t_ui_label *label)
{
	char	*temp;

	temp = get_font_path(label->font_path);
	ft_strdel(&label->font_path);
	label->font_path = temp;
//	if (label->font)
//		TTF_CloseFont(label->font);
//	label->font = TTF_OpenFont(label->font_path, label->font_size);
	label->font = ui_get_font(label->font_path, label->font_size);
}

SDL_Surface	*ui_surface_create_from_text_recipe(t_ui_label *label)
{
	SDL_Surface	*surface;
	t_rgba		rgba;
	SDL_Color	color;
	char		*temp;

	if (!label->font || label->font_recreate)
	{
		recreate_font_of_label(label);
		label->font_recreate = 0;
	}
	if (!label->font || !label->text)
		return (NULL);
	TTF_SizeUTF8(label->font, label->text,
		&label->text_wh.x, &label->text_wh.y);
	color = rgba_to_sdl_color(hex_to_rgba(label->font_color));
	if (label->max_w == -1)
		surface = TTF_RenderUTF8_Blended(label->font, label->text, color);
	else
		surface = TTF_RenderUTF8_Blended_Wrapped(label->font,
				label->text, color, label->max_w);
	return (surface);
}

SDL_Texture	*ui_texture_create_from_text_recipe(
		SDL_Renderer *renderer, t_ui_label *recipe)
{
	SDL_Texture	*texture;
	SDL_Surface	*surface;

	surface = ui_surface_create_from_text_recipe(recipe);
	if (!surface)
		return (NULL);
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	return (texture);
}

SDL_Texture	*ui_texture_create_from_path(SDL_Renderer *renderer, char *path)
{
	SDL_Surface	*surface;
	SDL_Texture	*texture;

	surface = ui_surface_image_new(path);
	if (!surface)
	{
		ft_printf("[%s] Surface couldn\'t be created from path. <%s>\n",
			__FUNCTION__, path);
		return (NULL);
	}
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (!texture)
		ft_printf("[%s] Texture couldn\'t be created from surface. <%s>\n",
			__FUNCTION__, path);
	SDL_FreeSurface(surface);
	return (texture);
}
