/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Jony Salmi <jony.salmi@gmail.com>
 */

#include "libui.h"

void	ui_menu_new(t_ui_window *win, t_ui_element *elem)
{
	t_ui_menu	*menu;

	ui_element_new(win, elem);
	elem->element = ft_memalloc(sizeof(t_ui_menu));
	elem->element_type = UI_TYPE_MENU;
	menu = elem->element;
	menu->elem = elem;
}

void	ui_menu_event(t_ui_element *elem, SDL_Event e)
{
	t_ui_menu		*menu;

	menu = elem->element;
	if (!menu->event_children)
		return ;
	ui_list_event(elem->children, e);
}

int	ui_menu_render(t_ui_element *elem)
{
	t_ui_menu		*menu;

	if (!ui_element_render(elem))
		return (0);
	menu = elem->element;
	if (!menu->render_children)
		return (1);
	ui_list_sort(elem->children);
	ui_list_render(elem->children);
	return (2);
}

void	ui_menu_edit(t_ui_element *elem, t_ui_recipe *recipe)
{
	t_ui_menu	*menu;

	if (elem->element_type != UI_TYPE_MENU)
	{
		ft_printf("[%s] Elem not of type UI_TYPE_MENU. %d %s.\n",
			__FUNCTION__, ui_element_type_to_string(elem->element_type));
		return ;
	}
	menu = elem->element;
	if (ft_strinarr("render_children", recipe->flags))
		menu->render_children = 1;
	if (ft_strinarr("event_children", recipe->flags))
		menu->event_children = 1;
}

void	ui_menu_free(void *elem, size_t size)
{
	t_ui_element	*element;
	t_ui_menu		*menu;

	element = elem;
	if (!element)
		return ;
	menu = element->element;
	if (!menu)
		return ;
	free(menu);
	(void)size;
}
