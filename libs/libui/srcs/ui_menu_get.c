/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Jony Salmi <jony.salmi@gmail.com>
 */

#include "libui.h"

t_ui_menu	*ui_menu_get_menu(t_ui_element *elem)
{
	if (elem->element_type == UI_TYPE_MENU)
		return (elem->element);
	return (NULL);
}
