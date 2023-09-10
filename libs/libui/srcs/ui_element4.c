/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Jony Salmi <jony.salmi@gmail.com>
 */

#include "libui.h"

t_vec4i	ui_element_screen_pos_get(t_ui_element *elem)
{
	t_vec4i	screen_pos;

	screen_pos.w = elem->pos.w;
	screen_pos.h = elem->pos.h;
	screen_pos.x = elem->parent_screen_pos->x + elem->pos.x;
	screen_pos.y = elem->parent_screen_pos->y + elem->pos.y;
	return (screen_pos);
}

void	dummy_free_er(void *dont, size_t care)
{
	(void)dont;
	(void)care;
}

t_list	**ui_element_get_parent_children(t_ui_element *elem)
{
	t_list	**list;

	if (!elem->parent)
		return (NULL);
	list = NULL;
	if (elem->parent_type == UI_TYPE_WINDOW)
	{
		if (((t_ui_window *)elem->parent)->children)
			list = &((t_ui_window *)elem->parent)->children;
	}
	else if (elem->parent_type == UI_TYPE_ELEMENT)
	{
		if (((t_ui_element *)elem->parent)->children)
			list = &((t_ui_element *)elem->parent)->children;
	}
	return (list);
}

/*
 * Goes through parent->children and find "elem" if found,
 * it removes it from the list.
*/
void	ui_element_remove_child_from_parent(t_ui_element *elem)
{
	t_list	*curr;
	t_list	**list;

	list = ui_element_get_parent_children(elem);
	if (!list)
		return ;
	curr = *list;
	while (curr)
	{
		if (curr->content == elem)
		{
			ft_lstdelone_nonfree(list, curr);
			return ;
		}
		curr = curr->next;
	}
}

/*
 * int	type;		this is the parent type, so we know what to typecast to.
*/
void	ui_element_set_parent(t_ui_element *elem, void *parent, int type)
{
	t_ui_element	*parent_elem;
	t_ui_window		*parent_win;

	if (elem->parent)
		ui_element_remove_child_from_parent(elem);
	if (type == UI_TYPE_WINDOW)
	{
		parent_win = parent;
		elem->parent = parent;
		elem->parent_type = type;
		elem->parent_screen_pos = &parent_win->screen_pos;
		elem->parent_show = &parent_win->show;
		elem->parent_rendered_last_frame = &parent_win->show;
		add_to_list(&parent_win->children, elem, UI_TYPE_ELEMENT);
	}
	else if (type == UI_TYPE_ELEMENT)
	{
		parent_elem = parent;
		elem->parent = parent;
		elem->parent_type = type;
		elem->parent_screen_pos = &parent_elem->screen_pos;
		elem->parent_show = &parent_elem->show;
		elem->parent_rendered_last_frame = &parent_elem->rendered_last_frame;
		add_to_list(&parent_elem->children, elem, UI_TYPE_ELEMENT);
	}
}
