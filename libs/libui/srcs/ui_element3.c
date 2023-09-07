/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Authors: Jony Salmi <jony.salmi@gmail.com>
 */

#include "libui.h"

void	ui_element_pos_set(t_ui_element *elem, t_vec4 pos)
{
	if (elem->pos.w != pos.w || elem->pos.h != pos.h)
		elem->texture_recreate = 1;
	elem->pos = pos;
	elem->screen_pos = ui_element_screen_pos_get(elem);
}

void	ui_element_pos_set2(t_ui_element *elem, t_vec2 pos)
{
	elem->pos.x = pos.x;
	elem->pos.y = pos.y;
}

void	ui_element_color_set(t_ui_element *elem, int state, Uint32 color)
{
	int	j;

	if (state < 0 || state >= UI_STATE_AMOUNT)
		return ;
	if (state == UI_STATE_AMOUNT)
	{
		j = -1;
		while (++j < UI_STATE_AMOUNT)
		{
			if (elem->colors[j] != color)
				elem->texture_recreate = 1;
			elem->colors[j] = color;
		}
		return ;
	}
	if (elem->colors[state] != color)
		elem->texture_recreate = 1;
	elem->colors[state] = color;
}

void	ui_element_image_set_from_path(
		t_ui_element *elem, int state, char *image_path)
{
	SDL_Surface	*image;

	if (!image_path)
		return ;
	image = SDL_LoadBMP(image_path);
	if (!image)
		return ;
	ui_element_image_set(elem, state, image);
	SDL_FreeSurface(image);
}

void	ui_element_image_set(t_ui_element *elem, int state, SDL_Surface *image)
{
	int	i;
	int	amount_to_make;
	int	made;

	if (!elem || state < 0 || state > UI_STATE_AMOUNT
		|| !image || !image->w || !image->h)
		return ;
	i = -1;
	amount_to_make = 1;
	made = 0;
	if (state == UI_STATE_AMOUNT)
		amount_to_make = UI_STATE_AMOUNT;
	else
		i = state - 1;
	while (++i < UI_STATE_AMOUNT && made < amount_to_make)
	{
		if (elem->images[i])
			SDL_FreeSurface(elem->images[i]);
		elem->images[i] = ui_surface_new(image->w, image->h);
		SDL_BlitSurface(image, NULL, elem->images[i], NULL);
		made++;
	}
	elem->use_images = 1;
	elem->texture_recreate = 1;
}
