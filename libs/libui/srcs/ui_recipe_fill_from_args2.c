/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_recipe_fill_from_args2.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalmi <jsalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 19:24:10 by jsalmi            #+#    #+#             */
/*   Updated: 2021/12/10 19:24:11 by jsalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

void	try_getting_bgimage_separate(t_ui_recipe *recipe, char **key_value)
{
	if (ft_strequ(key_value[0], "bg_image_default"))
	{
		if (recipe->bg_images_set[UI_STATE_DEFAULT])
			ft_strdel(&recipe->bg_images[UI_STATE_DEFAULT]);
		recipe->bg_images[UI_STATE_DEFAULT] = ft_strdup(key_value[1]);
		recipe->bg_images_set[UI_STATE_DEFAULT] = 1;
	}
	else if (ft_strequ(key_value[0], "bg_image_hover"))
	{
		if (recipe->bg_images_set[UI_STATE_HOVER])
			ft_strdel(&recipe->bg_images[UI_STATE_HOVER]);
		recipe->bg_images[UI_STATE_HOVER] = ft_strdup(key_value[1]);
		recipe->bg_images_set[UI_STATE_HOVER] = 1;
	}
	else if (ft_strequ(key_value[0], "bg_image_click"))
	{
		if (recipe->bg_images_set[UI_STATE_CLICK])
			ft_strdel(&recipe->bg_images[UI_STATE_CLICK]);
		recipe->bg_images[UI_STATE_CLICK] = ft_strdup(key_value[1]);
		recipe->bg_images_set[UI_STATE_CLICK] = 1;
	}
}

void	try_getting_bgimage(t_ui_recipe *recipe, char **key_value)
{
	int	jj;

	if (ft_strequ(key_value[0], "bg_image"))
	{
		jj = -1;
		while (++jj < UI_STATE_AMOUNT)
		{
			if (recipe->bg_images_set[jj])
				ft_strdel(&recipe->bg_images[jj]);
			recipe->bg_images[jj] = ft_strdup(key_value[1]);
			recipe->bg_images_set[jj] = 1;
		}
	}
	try_getting_bgimage_separate(recipe, key_value);
}

void	try_getting_z_show(t_ui_recipe *recipe, char **key_value)
{
	if (ft_strequ(key_value[0], "z"))
	{
		recipe->z = ft_atoi(key_value[1]);
		recipe->z_set = 1;
	}
	else if (ft_strequ(key_value[0], "show"))
	{
		recipe->show = ft_atoi(key_value[1]);
		recipe->show_set = 1;
	}
}

void	try_getting_text_stuff2(t_ui_recipe *recipe, char **key_value)
{
	if (ft_strequ(key_value[0], "font"))
	{
		if (recipe->font)
			ft_strdel(&recipe->font);
		recipe->font = ft_strdup(key_value[1]);
	}
	else if (ft_strequ(key_value[0], "text_align"))
	{
		recipe->text_align = text_align_getter(key_value[1]);
		recipe->text_align_set = 1;
	}
}

void	try_getting_text_stuff(t_ui_recipe *recipe, char **key_value)
{
	if (ft_strequ(key_value[0], "title"))
	{
		if (recipe->title)
			ft_strdel(&recipe->title);
		if (!key_value[1])
			recipe->remove_title = 1;
		else
			recipe->title = ft_strdup(key_value[1]);
	}
	else if (ft_strequ(key_value[0], "text_color"))
	{
		recipe->text_color = (unsigned int)strtoul(key_value[1], NULL, 16);
		recipe->text_color_set = 1;
	}
	else if (ft_strequ(key_value[0], "text_size"))
	{
		recipe->text_size = ft_atoi(key_value[1]);
		recipe->text_size_set = 1;
	}
	try_getting_text_stuff2(recipe, key_value);
}
