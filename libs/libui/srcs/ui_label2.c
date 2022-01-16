/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_label2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalmi <jsalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 19:23:24 by jsalmi            #+#    #+#             */
/*   Updated: 2021/12/10 19:23:25 by jsalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

void	ui_label_edit_helper(
	t_ui_element *elem, t_ui_label *label, t_ui_recipe *recipe)
{
	if (recipe->title && !recipe->remove_title)
		ui_label_set_text(elem, recipe->title);
	if (recipe->remove_title)
	{
		ft_strdel(&label->text);
		label->text = ft_strnew(0);
	}
	if (recipe->text_color_set)
		ui_label_color_set(elem, recipe->text_color);
	if (recipe->text_size_set)
		ui_label_size_set(elem, recipe->text_size);
	if (recipe->text_align_set)
		ui_label_text_align(elem, recipe->text_align);
	if (recipe->font)
		ui_label_font_set(elem, recipe->font);
}

/*
 * TODO:
 *	1. at some point only remove text aligns that dont make sense;
 *	2. When you have title without text (you want no text)
 *		if you just strdel it, everything breaks if you try to use label->text
 *		and its NULL, so we just set an empty string in it instead.
*/
void	ui_label_edit(t_ui_element *elem, t_ui_recipe *recipe)
{
	t_ui_label	*label;
	t_vec4		pos;
	int			i;

	if (!elem || elem->element_type != UI_TYPE_LABEL)
		return ;
	label = elem->element;
	ui_label_edit_helper(elem, label, recipe);
	pos = elem->pos;
	i = -1;
	while (++i < VEC4_SIZE)
	{
		if (recipe->text_pos_set[i])
		{
			pos.v[i] = recipe->text_pos.v[i];
			label->text_align = 0;
		}
	}
	if (recipe->text_pos_set[2])
		label->max_w = recipe->text_pos.v[2];
	ui_element_pos_set(elem, pos);
}

void	ui_label_get_valid_font_path(t_ui_element *elem, t_ui_label *label)
{
	char	*temp;

	if (access(label->font_path, F_OK))
	{
		temp = ui_layout_get_file_from_resource_dirs(elem->win->layout,
				label->font_path);
		if (temp)
		{
			ft_strdel(&label->font_path);
			label->font_path = temp;
		}
	}
}

void	ui_label_texture_redo(t_ui_element *elem)
{
	t_ui_label	*label;
	char		*temp;

	label = elem->element;
	if (elem->textures[UI_STATE_DEFAULT])
		SDL_FreeSurface(elem->textures[UI_STATE_DEFAULT]);
	if (elem->texture)
		SDL_DestroyTexture(elem->texture);
	ui_label_get_valid_font_path(elem, label);
	elem->textures[UI_STATE_DEFAULT]
		= ui_surface_create_from_text_recipe(elem->element);
	if (!elem->textures[UI_STATE_DEFAULT])
		elem->textures[UI_STATE_DEFAULT] = ui_surface_new(1, 1);
	elem->texture = SDL_CreateTextureFromSurface(elem->win->renderer,
			elem->textures[UI_STATE_DEFAULT]);
	label->texture_recreate = 0;
	elem->pos.w = elem->textures[UI_STATE_DEFAULT]->w;
	elem->pos.h = elem->textures[UI_STATE_DEFAULT]->h;
}

void	ui_label_text_align(t_ui_element *elem, int align)
{
	t_ui_label	*label;

	label = elem->element;
	label->text_align = align;
	if (align && !(align & UI_TEXT_ALIGN_NONE))
	{
		if (align & UI_TEXT_ALIGN_CENTER)
		{
			elem->pos.x = (elem->parent_screen_pos->w / 2)
				- (label->text_wh.x / 2);
			elem->pos.y = (elem->parent_screen_pos->h / 2)
				- (label->text_wh.y / 2);
		}
		if (align & UI_TEXT_ALIGN_TOP)
			elem->pos.y = 0;
		if (align & UI_TEXT_ALIGN_BOT)
			elem->pos.y = elem->parent_screen_pos->h - label->text_wh.y;
		if (align & UI_TEXT_ALIGN_LEFT)
			elem->pos.x = 0;
		if (align & UI_TEXT_ALIGN_RIGHT)
			elem->pos.x = elem->parent_screen_pos->w - label->text_wh.x;
	}
}
