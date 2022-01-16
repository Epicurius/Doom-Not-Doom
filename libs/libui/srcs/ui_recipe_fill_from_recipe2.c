/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_recipe_fill_from_recipe2.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalmi <jsalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 19:24:16 by jsalmi            #+#    #+#             */
/*   Updated: 2021/12/10 19:24:17 by jsalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

void	recipe_pos_set_fill(t_ui_recipe *target, t_ui_recipe *child)
{
	int	jj;

	jj = -1;
	while (++jj < VEC4_SIZE)
	{
		if (child->pos_set[jj])
		{
			target->pos.v[jj] = child->pos.v[jj];
			target->pos_set[jj] = 1;
		}
	}
}

void	recipe_bgcolor_set_fill(t_ui_recipe *target, t_ui_recipe *child)
{
	int	jj;

	jj = -1;
	while (++jj < UI_STATE_AMOUNT)
	{
		if (child->bg_colors_set[jj])
		{
			target->bg_colors[jj] = child->bg_colors[jj];
			target->bg_colors_set[jj] = 1;
		}
	}
}

void	recipe_bgimage_set_fill(t_ui_recipe *target, t_ui_recipe *child)
{
	int	jj;

	jj = -1;
	while (++jj < UI_STATE_AMOUNT)
	{
		if (child->bg_images_set[jj])
		{
			if (target->bg_images_set[jj])
				ft_strdel(&target->bg_images[jj]);
			target->bg_images[jj] = ft_strdup(child->bg_images[jj]);
			target->bg_images_set[jj] = 1;
		}
	}
}

void	recipe_z_show_set_fill(t_ui_recipe *target, t_ui_recipe *child)
{
	if (child->z_set)
	{
		target->z = child->z;
		target->z_set = 1;
	}
	if (child->show_set)
	{
		target->show = child->show;
		target->show_set = 1;
	}
}
