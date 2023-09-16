/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Jony Salmi <jony.salmi@gmail.com>
 */

#include "libui.h"

t_ui_element	*ui_scrollbar_get(t_ui_element *elem, int element_type)
{
	if (elem->element_type != UI_TYPE_SCROLLBAR)
		return (NULL);
	if (element_type == UI_TYPE_BUTTON)
		return (ui_scrollbar_get_button_element(elem));
	return (NULL);
}

t_ui_element	*ui_scrollbar_get_button_element(t_ui_element *elem)
{
	if (elem->element_type != UI_TYPE_SCROLLBAR)
	{
		LG_WARN("Element is not of type UI_TYPE_SCROLLBAR. <%d : %s>",
			elem->element_type, ui_element_type_to_string(elem->element_type));
		return (NULL);
	}
	return (&((t_ui_scrollbar *)elem->element)->button);
}

t_ui_button	*ui_scrollbar_get_button(t_ui_element *elem)
{
	if (elem->element_type != UI_TYPE_SCROLLBAR)
	{
		LG_WARN("Element is not of type UI_TYPE_SCROLLBAR. <%d : %s>",
			elem->element_type, ui_element_type_to_string(elem->element_type));
		return (NULL);
	}
	return (((t_ui_scrollbar *)elem->element)->button.element);
}
