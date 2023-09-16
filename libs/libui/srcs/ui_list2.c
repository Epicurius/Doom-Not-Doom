/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Jony Salmi <jony.salmi@gmail.com>
 */

#include "libui.h"

void	ui_list_event(t_list *list, SDL_Event e)
{
	t_list			*curr;
	t_ui_element	*elem;

	curr = list;
	while (curr)
	{
		elem = curr->content;
		if (elem->element_type >= 0 && elem->element_type < UI_TYPE_AMOUNT)
		{
			if (g_acceptable[elem->element_type].eventer)
				g_acceptable[elem->element_type].eventer(elem, e);
		}
		else
			LG_WARN("Element of type <%d : %s> is not supported",
				elem->element_type,
				ui_element_type_to_string(elem->element_type));
		curr = curr->next;
	}
}

/*
 * A no matter what renderer.
*/
void	ui_list_render(t_list *list)
{
	t_list			*curr;
	t_ui_element	*elem;

	curr = list;
	while (curr)
	{
		elem = curr->content;
		if (elem->element_type >= 0
			&& elem->element_type < UI_TYPE_AMOUNT
			&& g_acceptable[elem->element_type].renderer)
			g_acceptable[elem->element_type].renderer(elem);
		else
			LG_WARN("Element of type <%d : %s> is not supported",
				elem->element_type,
				ui_element_type_to_string(elem->element_type));
		curr = curr->next;
	}
}

/*
 * A matter what renderer.
*/
void	ui_layout_list_render(t_list *list)
{
	t_list			*curr;
	t_ui_element	*elem;

	curr = list;
	while (curr)
	{
		elem = curr->content;
		if (elem->element_type >= 0
			&& elem->element_type < UI_TYPE_AMOUNT
			&& !elem->is_a_part_of_another
			&& g_acceptable[elem->element_type].renderer)
			g_acceptable[elem->element_type].renderer(elem);
		else if (!elem->is_a_part_of_another)
			LG_WARN("Element of type <%d : %s> is not supported",
				elem->element_type,
				ui_element_type_to_string(elem->element_type));
		curr = curr->next;
	}
}

/*
 * Calls ui_element_free on everything in 'list'.
 * And then frees the whole list, no questions asked.
*/
void	ui_list_element_free(t_list	**list)
{
	t_list	*curr;
	t_list	*next;
	int		i;

	if (!list)
		return ;
	curr = *list;
	i = 0;
	while (curr)
	{
		next = curr->next;
		ui_element_free(curr->content, UI_TYPE_ELEMENT);
		if (!*list)
			break ;
		if (next)
			curr = next;
		else
			break ;
		i++;
	}
	ft_lstdel(list, &dummy_free_er);
}
