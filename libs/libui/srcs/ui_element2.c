/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Jony Salmi <jony.salmi@gmail.com>
 */

#include "libui.h"

void	ui_element_set_id(t_ui_element *elem, char *id)
{
	if (elem->id)
		ft_strdel(&elem->id);
	elem->id = ft_strdup(id);
}

int	ui_element_type_from_string(char *str)
{
	int	k;

	k = -1;
	while (++k < UI_TYPE_AMOUNT)
		if (ft_strequ(str, g_acceptable[k].name))
			return (k);
	return (UI_TYPE_NONE);
}

const char	*ui_element_type_to_string(int type)
{
	if (type < 0 || type >= UI_TYPE_AMOUNT)
	{
		ft_printf("[%s] Error : Element type "
			"[%d] doesn\'t exist.\n", __FUNCTION__, type);
		return ("none");
	}
	return (g_acceptable[type].name);
}

/*
 * Moves all elements in list with t_vec2i amount;
*/
void	ui_element_move_list(t_list *list, t_vec2i amount)
{
	t_ui_element	*elem;

	while (list)
	{
		elem = list->content;
		ui_element_pos_set2(elem,
			vec2(elem->pos.x + amount.x, elem->pos.y + amount.y));
		list = list->next;
	}
}

/*
 * NOTE: this doesnt free the element, only removes it from the list;
*/
void	ui_element_remove_from_list(t_ui_element *elem, t_list **list)
{
	t_list	*curr;

	curr = *list;
	while (curr)
	{
		if (curr->content == elem)
			ft_lstdelone_nonfree(list, curr);
		curr = curr->next;
	}
}
