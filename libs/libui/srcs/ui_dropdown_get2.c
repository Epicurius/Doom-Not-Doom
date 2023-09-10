/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Jony Salmi <jony.salmi@gmail.com>
 */

#include "libui.h"

/*
 * Returns dropdown from element, if the type is dropdown;
*/
t_ui_dropdown	*ui_dropdown_get_dropdown(t_ui_element *elem)
{
	if (!elem || elem->element_type != UI_TYPE_DROPDOWN)
		return (NULL);
	return (elem->element);
}

t_ui_element	*ui_dropdown_get_button_with_text(
	t_ui_element *elem, char *text)
{
	t_ui_element	*menu;

	if (!elem || elem->element_type != UI_TYPE_DROPDOWN || !text)
		return (NULL);
	menu = ui_dropdown_get_menu_element(elem);
	if (!menu)
		return (NULL);
	return (ui_list_get_button_with_text(menu->children, text));
}
