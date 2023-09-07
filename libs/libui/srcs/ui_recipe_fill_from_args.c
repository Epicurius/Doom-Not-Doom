/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Jony Salmi <jony.salmi@gmail.com>
 */

#include "libui.h"

void	try_getting_value(t_ui_recipe *recipe, char **key_value)
{
	int		jj;
	char	**values;

	if (ft_strequ(key_value[0], "value") || ft_strequ(key_value[0], "values"))
	{
		jj = -1;
		values = ft_strsplit(key_value[1], ',');
		while (++jj < 3)
		{
			recipe->value[jj] = ft_atoi(values[jj]);
			recipe->value_set[jj] = 1;
		}
		ft_arraydel(values);
	}
}

void	try_getting_flags(t_ui_recipe *recipe, char **key_value)
{
	int		i;
	char	**flags;
	char	**final_flags;

	if (ft_strequ(key_value[0], "flag") || ft_strequ(key_value[0], "flags"))
	{
		flags = ft_strsplit(key_value[1], ' ');
		final_flags = ft_arrjoin(recipe->flags, flags);
		ft_arraydel(flags);
		ft_arraydel(recipe->flags);
		recipe->flags = final_flags;
	}
	else if (ft_strequ(key_value[0], "texture"))
	{
		i = -1;
		flags = ft_strsplit(key_value[1], ' ');
		while (flags[++i])
		{
			recipe->texture_size.v[i] = ft_atoi(flags[i]);
			recipe->texture_size_set[i] = 1;
		}
		ft_arraydel(flags);
	}
}

void	try_getting_input_stuff(t_ui_recipe *recipe, char **key_value)
{
	if (ft_strequ(key_value[0], "type"))
	{
		if (ft_strequ(key_value[1], "numbers"))
		{
			recipe->input_type = 1;
			recipe->input_type_set = 1;
		}
		else if (ft_strequ(key_value[1], "letters"))
		{
			recipe->input_type = 2;
			recipe->input_type_set = 1;
		}
		else if (ft_strequ(key_value[1], "everything"))
		{
			recipe->input_type = 0;
			recipe->input_type_set = 1;
		}
	}
	else if (ft_strequ(key_value[0], "placeholder"))
	{
		if (recipe->placeholder_text)
			ft_strdel(&recipe->placeholder_text);
		recipe->placeholder_text = ft_strdup(key_value[1]);
	}
}

void	try_getting_scrollbar_stuff(t_ui_recipe *recipe, char **key_value)
{
	if (ft_strequ(key_value[0], "target"))
	{
		recipe->target = ft_strdup(key_value[1]);
	}
}

void	fill_recipe_from_args(t_ui_recipe *recipe, char **args)
{
	int		i;
	char	**key_value;

	if (!args)
		return ;
	i = -1;
	while (args[++i])
	{
		key_value = ft_strsplitfirstoccurence(args[i], ':');
		ft_strtrimwholearr(key_value);
		try_getting_xywh_separate(recipe, key_value);
		try_getting_xywh(recipe, key_value);
		try_getting_text_pos(recipe, key_value);
		try_getting_bgcolor(recipe, key_value);
		try_getting_bgimage(recipe, key_value);
		try_getting_z_show(recipe, key_value);
		try_getting_text_stuff(recipe, key_value);
		try_getting_value(recipe, key_value);
		try_getting_flags(recipe, key_value);
		try_getting_input_stuff(recipe, key_value);
		try_getting_scrollbar_stuff(recipe, key_value);
		ft_arraydel(key_value);
	}
}
