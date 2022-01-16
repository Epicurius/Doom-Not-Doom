/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_layout_get.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalmi <jsalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 19:23:30 by jsalmi            #+#    #+#             */
/*   Updated: 2021/12/10 19:23:31 by jsalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

/*
 * Have this function to make it easier for the user getting a window;
 * (the user doesnt have to know the in the layout the window is...);
*/
t_ui_window	*ui_layout_get_window(t_ui_layout *layout, char *id)
{
	if (!layout)
		return (NULL);
	return (ui_list_get_window_by_id(layout->windows, id));
}

t_ui_element	*ui_layout_get_element(t_ui_layout *layout, char *id)
{
	if (!layout)
		return (NULL);
	return (ui_list_get_element_by_id(layout->elements, id));
}

t_ui_recipe	*ui_layout_get_recipe(t_ui_layout *layout, char *id)
{
	if (!layout)
		return (NULL);
	return (ui_list_get_recipe_by_id(layout->recipes, id));
}

char	*ui_layout_get_file_from_resource_dirs(t_ui_layout *layout, char *file)
{
	char	*temp;
	int		iii;

	if (!layout || !file || !layout->resource_dirs)
		return (NULL);
	iii = -1;
	while (layout->resource_dirs[++iii])
	{
		temp = ft_strjoin(layout->resource_dirs[iii], file);
		if (!access(temp, F_OK))
			return (temp);
		ft_strdel(&temp);
	}
	return (NULL);
}
