/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_element_render.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalmi <jsalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 19:22:29 by jsalmi            #+#    #+#             */
/*   Updated: 2021/12/10 19:22:31 by jsalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

/*
 * NOTE: we dont always update all the values in 'result';
*/
void	complicated_math(
		t_vec4i *result, t_vec4i pos,
		t_vec4i parent_from_pos, t_vec4i parent_to_pos)
{
	if (pos.x < parent_from_pos.x)
	{
		result->x = parent_from_pos.x - pos.x;
		result->w = pos.w - result->x;
	}
	else if (pos.x + pos.w > parent_to_pos.w)
		result->w = pos.w - abs((pos.x + pos.w) - parent_to_pos.w);
	if (pos.y < parent_from_pos.y)
	{
		result->y = parent_from_pos.y - pos.y;
		result->h = pos.h - result->y;
	}
	else if (pos.y + pos.h > parent_to_pos.h)
		result->h = pos.h - abs((pos.y + pos.h) - parent_to_pos.h);
}

/*
 * TODO: from and to should be pointer, and if they are null,
 * 		we put whole 'texture' on 'win->texture';
 *
 * From 'texture' at pos 'from' blit pixels to 'win->texture' to pos 'to';
 * Returns if the texture was blat or not;
*/
int	ui_puttextureonwindow(
		t_ui_window *win, SDL_Texture *texture, t_vec4i from, t_vec4i to)
{
	if (to.w <= 0 || to.h <= 0 || from.w <= 0 || from.h <= 0)
		return (0);
	SDL_SetRenderTarget(win->renderer, win->texture);
	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
	SDL_RenderCopy(win->renderer, texture,
		&(SDL_Rect){from.x, from.y, from.w, from.h},
		&(SDL_Rect){to.x, to.y, to.w, to.h});
	SDL_SetRenderTarget(win->renderer, NULL);
	return (1);
}

void	ui_element_update_texture(t_ui_element *elem)
{
	SDL_UpdateTexture(elem->texture, NULL,
		elem->textures[elem->state]->pixels,
		elem->textures[elem->state]->pitch);
}

void	ui_element_update_to_from(t_ui_element *elem)
{
	complicated_math(&elem->from_pos, vec4_to_vec4i(elem->pos),
		((t_ui_element *)elem->parent)->from_pos,
		((t_ui_element *)elem->parent)->to_pos);
	elem->to_pos = vec4i(elem->to_pos.x + elem->from_pos.x, elem->to_pos.y
			+ elem->from_pos.y, elem->from_pos.w, elem->from_pos.h);
}

/*
 * Return: 1 if rendering successful, 0 if not.
 *
 * TODO: when radio is either removed or reworked,
 * move: elem->rendered_last_frame = 1;
*/
int	ui_element_render(t_ui_element *elem)
{
	elem->rendered_last_frame = 0;
	if (elem->texture_recreate || elem->win->textures_recreate)
		ui_element_textures_redo(elem);
	if (!*elem->parent_rendered_last_frame
		|| !*elem->parent_show || !elem->show
		|| !elem->textures[elem->state])
		return (0);
	elem->screen_pos = ui_element_screen_pos_get(elem);
	elem->from_pos = vec4i(0, 0, elem->pos.w, elem->pos.h);
	elem->to_pos = elem->screen_pos;
	if (elem->state != elem->last_state)
		ui_element_update_texture(elem);
	if (elem->parent_type == UI_TYPE_ELEMENT && elem->figure_out_z)
		elem->z = ((t_ui_element *)elem->parent)->z + 1;
	if (elem->parent && elem->parent_type == UI_TYPE_ELEMENT
		&& ((t_ui_element *)elem->parent)->render_me_on_parent)
		elem->render_me_on_parent = 1;
	if (elem->render_me_on_parent && elem->parent_type != UI_TYPE_WINDOW)
		ui_element_update_to_from(elem);
	elem->last_state = elem->state;
	elem->rendered_last_frame = 1;
	if (!ui_puttextureonwindow(elem->win, elem->texture,
			elem->from_pos, elem->to_pos))
		return (0);
	return (1);
}
