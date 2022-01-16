/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_element5.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalmi <jsalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 19:22:41 by jsalmi            #+#    #+#             */
/*   Updated: 2021/12/10 19:22:42 by jsalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

void	ui_element_set_images_internal(t_ui_element *elem)
{
	int	i;

	i = -1;
	while (++i < UI_STATE_AMOUNT)
	{
		if (!elem->images[i])
			continue ;
		SDL_BlitScaled(elem->images[i], NULL, elem->textures[i], NULL);
	}
}

void	ui_element_textures_free(t_ui_element *elem)
{
	int	i;

	i = -1;
	while (++i < UI_STATE_AMOUNT)
		if (elem->textures[i])
			SDL_FreeSurface(elem->textures[i]);
}

void	ui_element_images_free(t_ui_element *elem)
{
	int	i;

	i = -1;
	while (++i < UI_STATE_AMOUNT)
	{
		if (elem->images[i])
			SDL_FreeSurface(elem->images[i]);
	}
}

void	ui_element_set_colors_internal(t_ui_element *elem)
{
	SDL_FillRect(elem->textures[UI_STATE_DEFAULT], NULL,
		elem->colors[UI_STATE_DEFAULT]);
	SDL_FillRect(elem->textures[UI_STATE_HOVER], NULL,
		elem->colors[UI_STATE_HOVER]);
	SDL_FillRect(elem->textures[UI_STATE_CLICK], NULL,
		elem->colors[UI_STATE_CLICK]);
}

/*
 * Redos the textures, helpful if you have changed the w and/or h of the element.
*/
void	ui_element_textures_redo(t_ui_element *elem)
{
	ui_element_textures_free(elem);
	if (elem->texture)
	{
		SDL_DestroyTexture(elem->texture);
		elem->texture = NULL;
	}
	if (!elem->texture)
		elem->texture = ui_create_texture(elem->win->renderer,
				vec2i(elem->pos.w, elem->pos.h));
	SDL_QueryTexture(elem->texture, NULL, NULL,
		&elem->current_texture_size.x, &elem->current_texture_size.y);
	elem->textures[UI_STATE_DEFAULT] = ui_surface_new(elem->pos.w, elem->pos.h);
	elem->textures[UI_STATE_HOVER] = ui_surface_new(elem->pos.w, elem->pos.h);
	elem->textures[UI_STATE_CLICK] = ui_surface_new(elem->pos.w, elem->pos.h);
	elem->texture_recreate = 0;
	if (elem->use_images)
		ui_element_set_images_internal(elem);
	else
		ui_element_set_colors_internal(elem);
	ui_element_update_texture(elem);
}
