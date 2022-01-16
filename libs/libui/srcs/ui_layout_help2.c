/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_layout_help2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalmi <jsalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 10:01:41 by jsalmi            #+#    #+#             */
/*   Updated: 2021/12/18 10:07:08 by jsalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

void	get_style_file(t_ui_layout *layout, char *str)
{
	char	*temp;

	if (!str)
		return ;
	temp = ft_strndup(str, ft_strlen(str) - 1);
	if (layout->root_dir)
		layout->style_file = ft_strjoin(layout->root_dir, temp);
	else
		layout->style_file = ft_strdup(temp);
	ft_strdel(&temp);
}

void	get_resource_dir(t_ui_layout *layout, char *str)
{
	char	*temp;
	char	*temp2;

	if (!str)
		return ;
	temp = ft_strndup(str, ft_strlen(str) - 1);
	if (layout->root_dir)
	{
		temp2 = ft_strjoin(layout->root_dir, temp);
		layout->resource_dirs = ft_arradd(layout->resource_dirs, temp2);
		ft_strdel(&temp2);
	}
	else
		layout->resource_dirs = ft_arradd(layout->resource_dirs, temp);
	ft_strdel(&temp);
}

int	get_special(t_ui_layout *layout, char *str)
{
	char	**arr;
	int		result;

	result = 0;
	arr = ft_strsplitfirstoccurence(str, ':');
	if (arr && arr[0] && arr[1])
	{
		ft_strtrimwholearr(arr);
		if (ft_strequ(arr[0], "style"))
		{
			get_style_file(layout, arr[1]);
			result = 1;
		}
		else if (ft_strequ(arr[0], "resource_dir"))
		{
			get_resource_dir(layout, arr[1]);
			result = 1;
		}
	}
	ft_arraydel(arr);
	return (result);
}
