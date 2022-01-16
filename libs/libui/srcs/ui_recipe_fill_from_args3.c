/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_recipe_fill_from_args3.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalmi <jsalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 19:24:12 by jsalmi            #+#    #+#             */
/*   Updated: 2021/12/10 19:24:13 by jsalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

void	try_getting_xywh_separate(t_ui_recipe *recipe, char **key_value)
{
	if (ft_strequ(key_value[0], "x"))
	{
		recipe->pos.v[0] = ft_atof(key_value[1]);
		recipe->pos_set[0] = 1;
	}
	else if (ft_strequ(key_value[0], "y"))
	{
		recipe->pos.v[1] = ft_atof(key_value[1]);
		recipe->pos_set[1] = 1;
	}
	else if (ft_strequ(key_value[0], "w"))
	{
		recipe->pos.v[2] = ft_atof(key_value[1]);
		recipe->pos_set[2] = 1;
	}
	else if (ft_strequ(key_value[0], "h"))
	{
		recipe->pos.v[3] = ft_atof(key_value[1]);
		recipe->pos_set[3] = 1;
	}
}

void	try_getting_xywh(t_ui_recipe *recipe, char **key_value)
{
	char	**pos;
	int		pp;

	if (ft_strequ(key_value[0], "xywh"))
	{
		pp = -1;
		pos = ft_strsplit(key_value[1], ',');
		while (++pp < VEC4_SIZE)
		{
			recipe->pos.v[pp] = ft_atof(pos[pp]);
			recipe->pos_set[pp] = 1;
		}
		ft_arraydel(pos);
	}
}

void	try_getting_text_pos(t_ui_recipe *recipe, char **key_value)
{
	char	**pos;
	int		pp;

	if (ft_strequ(key_value[0], "text_pos"))
	{
		pp = -1;
		pos = ft_strsplit(key_value[1], ',');
		while (++pp < VEC4_SIZE)
		{
			recipe->text_pos.v[pp] = ft_atof(pos[pp]);
			recipe->text_pos_set[pp] = 1;
		}
		ft_arraydel(pos);
	}
}

void	try_getting_bgcolor_separate(t_ui_recipe *recipe, char **key_value)
{
	if (ft_strequ(key_value[0], "bg_color_default"))
	{
		recipe->bg_colors[UI_STATE_DEFAULT]
			= (unsigned int)strtoul(key_value[1], NULL, 16);
		recipe->bg_colors_set[UI_STATE_DEFAULT] = 1;
	}
	else if (ft_strequ(key_value[0], "bg_color_hover"))
	{
		recipe->bg_colors[UI_STATE_HOVER]
			= (unsigned int)strtoul(key_value[1], NULL, 16);
		recipe->bg_colors_set[UI_STATE_HOVER] = 1;
	}
	else if (ft_strequ(key_value[0], "bg_color_click"))
	{
		recipe->bg_colors[UI_STATE_CLICK]
			= (unsigned int)strtoul(key_value[1], NULL, 16);
		recipe->bg_colors_set[UI_STATE_CLICK] = 1;
	}
}

void	try_getting_bgcolor(t_ui_recipe *recipe, char **key_value)
{
	int		jj;

	if (ft_strequ(key_value[0], "bg_color"))
	{
		jj = -1;
		while (++jj < UI_STATE_AMOUNT)
		{
			recipe->bg_colors[jj]
				= (unsigned int)strtoul(key_value[1], NULL, 16);
			recipe->bg_colors_set[jj] = 1;
		}
	}
	try_getting_bgcolor_separate(recipe, key_value);
}
