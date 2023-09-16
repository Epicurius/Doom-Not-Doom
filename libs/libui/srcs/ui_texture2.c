/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Jony Salmi <jony.salmi@gmail.com>
 */

#include "libui.h"

/*
 * 1. First try to find with absolute path...
 * 2. ... if not found, try to find from DEFAULT_TTF/"font_name" ...
 * 3. ... if still not found, try to find default font.
 * 		IF this is not found, it's my fault.
 *
 * Seg faults if font_path == NULL;
*/
char	*get_font_path(char *font_path)
{
	char	*temp_font_path;

	temp_font_path = ft_strdup(font_path);
	if (access(temp_font_path, F_OK))
	{
		ft_strdel(&temp_font_path);
		temp_font_path = ft_strjoin(DEFAULT_TTF, font_path);
	}
	else
		return (temp_font_path);
	if (access(temp_font_path, F_OK))
	{
		ft_strdel(&temp_font_path);
		temp_font_path = ft_strdup(DEFAULT_TTF"DroidSans.ttf");
		if (!access(temp_font_path, F_OK))
			return (temp_font_path);
		else
		{
			ft_strdel(&temp_font_path);
			return (NULL);
		}
	}
	return (temp_font_path);
}

void	recreate_font_of_label(t_ui_label *label)
{
	char	*temp;

	temp = get_font_path(label->font_path);
	ft_strdel(&label->font_path);
	label->font_path = temp;
	label->font = ui_get_font(label->font_path, label->font_size);
}

SDL_Surface	*ui_surface_create_from_text_recipe(t_ui_label *label)
{
	SDL_Surface	*surface;
	SDL_Color	color;

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
		LG_WARN("Surface couldn\'t be created from path. <%s>",
			path);
		return (NULL);
	}
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (!texture)
		LG_WARN("Texture couldn\'t be created from surface. <%s>",
			path);
	SDL_FreeSurface(surface);
	return (texture);
}
