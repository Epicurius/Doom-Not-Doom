/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Jony Salmi <jony.salmi@gmail.com>
 */

#include "libui.h"

void	ui_element_set_pos_from_recipe(t_ui_element *elem, t_ui_recipe *recipe)
{
	t_vec4	pos;
	int		i;

	pos = elem->pos;
	i = -1;
	while (++i < VEC4_SIZE)
		if (recipe->pos_set[i])
			pos.v[i] = recipe->pos.v[i];
	ui_element_pos_set(elem, pos);
}

void	ui_element_set_color_from_recipe(
	t_ui_element *elem, t_ui_recipe *recipe)
{
	int		i;

	i = -1;
	while (++i < UI_STATE_AMOUNT)
		if (recipe->bg_colors_set[i])
			ui_element_color_set(elem, i, recipe->bg_colors[i]);
}

/*
 * IMPORTANT!!!
 * DONT FREE TEMP If you set it into the bg_image;
*/
void	ui_element_set_bgimage_from_recipe(
	t_ui_element *elem, t_ui_recipe *recipe)
{
	int		i;
	char	*temp;

	i = -1;
	while (++i < UI_STATE_AMOUNT)
	{
		if (recipe->bg_images_set[i] && recipe->bg_images[i])
		{
			if (!access(recipe->bg_images[i], F_OK))
				ui_element_image_set_from_path(elem, i, recipe->bg_images[i]);
			else
			{
				temp = ui_layout_get_file_from_resource_dirs(
						elem->win->layout, recipe->bg_images[i]);
				if (!temp)
					continue ;
				ft_strdel(&recipe->bg_images[i]);
				recipe->bg_images[i] = temp;
				ui_element_image_set_from_path(elem, i, recipe->bg_images[i]);
			}
		}
	}
}

/*
 * This function will be called recursively for elements that are
 * contained inside other elements.
*/
void	ui_element_edit(t_ui_element *elem, t_ui_recipe *recipe)
{
	ui_element_set_pos_from_recipe(elem, recipe);
	ui_element_set_color_from_recipe(elem, recipe);
	ui_element_set_bgimage_from_recipe(elem, recipe);
	if (recipe->flags)
	{
		if (ft_strinarr("render_on_parent", recipe->flags))
			elem->render_me_on_parent = 1;
	}
	if (recipe->z_set)
	{
		elem->z = recipe->z;
		elem->figure_out_z = 0;
	}
	if (recipe->show_set)
		elem->show = recipe->show;
	if (g_acceptable[elem->element_type].edit)
		g_acceptable[elem->element_type].edit(elem, recipe);
	else
		ft_printf("[%s] Element of type :%d:%s doenst have a edit function.\n",
			__FUNCTION__, elem->element_type,
			ui_element_type_to_string(elem->element_type));
}
