/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Jony Salmi <jony.salmi@gmail.com>
 */

#include "libui.h"

void	recipe_text_stuff_set_fill2(t_ui_recipe *target, t_ui_recipe *child)
{
	int	jj;

	if (child->font != NULL)
	{
		if (target->font)
			ft_strdel(&target->font);
		target->font = ft_strdup(child->font);
	}
	if (child->text_align_set)
	{
		target->text_align = child->text_align;
		target->text_align_set = 1;
	}
	jj = -1;
	while (++jj < 4)
	{
		if (child->text_pos_set[jj])
		{
			target->text_pos.v[jj] = child->text_pos.v[jj];
			target->text_pos_set[jj] = 1;
		}
	}
}

void	recipe_text_stuff_set_fill(t_ui_recipe *target, t_ui_recipe *child)
{
	if (child->title != NULL)
	{
		if (target->title)
			ft_strdel(&target->title);
		target->title = ft_strdup(child->title);
	}
	if (child->remove_title)
		target->remove_title = 1;
	if (child->text_color_set)
	{
		target->text_color = child->text_color;
		target->text_color_set = 1;
	}
	if (child->text_size_set)
	{
		target->text_size = child->text_size;
		target->text_size_set = 1;
	}
	recipe_text_stuff_set_fill2(target, child);
}

void	recipe_value_set_fill(t_ui_recipe *target, t_ui_recipe *child)
{
	int	jj;

	jj = -1;
	while (++jj < 3)
	{
		if (child->value_set[jj])
		{
			target->value[jj] = child->value[jj];
			target->value_set[jj] = 1;
		}
	}
	if (child->input_type_set)
	{
		target->input_type = child->input_type;
		target->input_type_set = 1;
	}
	if (child->placeholder_text != NULL)
	{
		if (target->placeholder_text)
			ft_strdel(&target->placeholder_text);
		target->placeholder_text = ft_strdup(child->placeholder_text);
	}
	if (child->target)
		target->target = ft_strdup(child->target);
}

void	recipe_flag_set_fill(t_ui_recipe *target, t_ui_recipe *child)
{
	char	**flags;
	int		i;

	if (child->flags != NULL)
	{
		flags = ft_arrjoin(target->flags, child->flags);
		ft_arraydel(target->flags);
		target->flags = flags;
	}
	i = -1;
	while (++i < 2)
	{
		if (child->texture_size_set[i])
		{
			target->texture_size_set[i] = 1;
			target->texture_size.v[i] = child->texture_size.v[i];
		}
	}
}

void	fill_recipe_from_recipe(t_ui_recipe *target, t_ui_recipe *child)
{
	if (!target || !child)
		return ;
	recipe_pos_set_fill(target, child);
	recipe_bgcolor_set_fill(target, child);
	recipe_bgimage_set_fill(target, child);
	recipe_z_show_set_fill(target, child);
	recipe_text_stuff_set_fill(target, child);
	recipe_value_set_fill(target, child);
	recipe_flag_set_fill(target, child);
}
