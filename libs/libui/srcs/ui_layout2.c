/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Jony Salmi <jony.salmi@gmail.com>
 */

#include "libui.h"

/*
 * This goes through family and searches for window as the head parent,
 * since all elements need a window, to be created;
 *
 * If the head family type is not a UI_TYPE_WINDOW, they will be skipped;
*/
void	layout_compile_elements(t_ui_layout *layout)
{
	t_list		*curr;
	t_ui_family	*family;
	t_ui_window	*win;

	curr = layout->families;
	while (curr)
	{
		family = curr->content;
		if (family->type == UI_TYPE_WINDOW)
		{
			win = ui_layout_get_window(layout, family->id);
			if (!win)
			{
				win = ft_memalloc(sizeof(t_ui_window));
				ui_window_new(win, NULL, vec4(0, 25, 100, 100));
				ui_window_id_set(win, family->id);
				add_to_list(&layout->windows, win, UI_TYPE_WINDOW);
			}
			win->layout = layout;
			make_family_from_children(
				&layout->elements, win, UI_TYPE_WINDOW, family);
		}
		curr = curr->next;
	}
}

t_ui_recipe	*get_global_recipe(
		t_list *windows, t_list *elements, t_list *recipes, char *elem_id)
{
	t_ui_element	*elem;
	t_ui_window		*win;
	t_ui_recipe		*child_recipe;

	elem = ui_list_get_element_by_id(elements, elem_id);
	child_recipe = NULL;
	if (elem)
	{
		child_recipe = ui_list_get_recipe_by_id(recipes,
				g_acceptable[elem->element_type].name);
	}
	else if (!elem)
	{
		win = ui_list_get_window_by_id(windows, elem_id);
		if (win)
		{
			child_recipe = ui_list_get_recipe_by_id(recipes,
					g_acceptable[UI_TYPE_WINDOW].name);
		}
	}
	else
		LG_WARN("No recipe id %s found.", elem_id);
	return (child_recipe);
}

t_ui_recipe	*create_recipe(
		char **name_and_prefabs, char **args,
		t_list *recipes, t_ui_recipe *global_recipe)
{
	t_ui_recipe	*recipe;
	t_ui_recipe	*child_recipe;
	int			i;

	recipe = ft_memalloc(sizeof(t_ui_recipe));
	recipe->id = ft_strdup(name_and_prefabs[0]);
	if (global_recipe)
		fill_recipe_from_recipe(recipe, global_recipe);
	i = 0;
	while (name_and_prefabs[++i])
	{
		child_recipe = ui_list_get_recipe_by_id(recipes, name_and_prefabs[i]);
		if (!child_recipe)
			LG_WARN("No recipe with id %s found.",
				name_and_prefabs[i]);
		else
			fill_recipe_from_recipe(recipe, child_recipe);
	}
	fill_recipe_from_args(recipe, args);
	return (recipe);
}

t_ui_recipe	*make_recipe_from_string(
		t_list *windows, t_list *elements, t_list *recipes, char *str)
{
	t_ui_recipe		*recipe;
	t_ui_recipe		*global_recipe;
	char			**temp;
	char			**name_and_prefabs;
	char			**args;

	if (!str)
		return (NULL);
	temp = ft_strsplitfirstoccurence(str, '{');
	name_and_prefabs = ft_strsplit(temp[0], ':');
	ft_strtrimwholearr(name_and_prefabs);
	args = ft_strsplit(temp[1], ';');
	ft_strtrimwholearr(args);
	ft_arraydel(temp);
	global_recipe
		= get_global_recipe(windows, elements, recipes, name_and_prefabs[0]);
	recipe = create_recipe(name_and_prefabs, args, recipes, global_recipe);
	ft_arraydel(name_and_prefabs);
	ft_arraydel(args);
	return (recipe);
}

/*
 * These are done from the first to the last,
 * which means if you have a child recipe
 * it has to be made before the final recipe.
 * Show error to user if they have prefab that cant
 * be found.
*/
void	layout_make_recipes(t_ui_layout *layout)
{
	int			i;
	char		**arr;
	t_ui_recipe	*recipe;

	arr = layout->style_recipe_strings;
	if (!arr)
		return ;
	i = -1;
	while (arr[++i])
	{
		recipe = make_recipe_from_string(
				layout->windows, layout->elements, layout->recipes, arr[i]);
		if (recipe)
			add_to_list(&layout->recipes, recipe, sizeof(t_ui_recipe));
	}
}
