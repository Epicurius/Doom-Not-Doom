/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_list.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalmi <jsalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 19:23:42 by jsalmi            #+#    #+#             */
/*   Updated: 2021/12/10 19:38:06 by jsalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

/*
 *	sorts all elements with their z value in ascending order;
 *	TODO: figure out how often this should be done;
*/
void	ui_list_sort(t_list *list)
{
	t_list			*curr;
	t_list			*next;
	t_ui_element	*temp;
	int				temp_int;

	curr = list;
	while (curr)
	{
		next = curr->next;
		if (!next || !curr->content || !curr->next->content)
			break ;
		if (((t_ui_element *)curr->content)->z
			> ((t_ui_element *)curr->next->content)->z)
		{
			temp = curr->content;
			curr->content = curr->next->content;
			curr->next->content = temp;
			pointer_swap(&curr->content_size, &curr->next->content_size);
			curr = list;
		}
		else
			curr = curr->next;
	}
}

t_ui_recipe	*ui_list_get_recipe_by_id(t_list *list, char *id)
{
	t_list		*curr;
	t_ui_recipe	*recipe;

	curr = list;
	while (curr)
	{
		recipe = curr->content;
		if (ft_strequ(recipe->id, id))
			return (recipe);
		curr = curr->next;
	}
	return (NULL);
}

t_ui_element	*ui_list_get_element_by_id(t_list *list, char *id)
{
	t_list			*curr;
	t_ui_element	*elem;

	curr = list;
	while (curr)
	{
		elem = curr->content;
		if (ft_strequ(elem->id, id))
			return (elem);
		curr = curr->next;
	}
	return (NULL);
}

t_ui_window	*ui_list_get_window_by_id(t_list *list, char *id)
{
	t_ui_window	*win;

	while (list)
	{
		win = list->content;
		if (ft_strequ(win->id, id))
			return (win);
		list = list->next;
	}
	return (NULL);
}
