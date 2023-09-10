/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Jony Salmi <jony.salmi@gmail.com>
 */

#include "libui.h"

t_ui_input	*ui_input_get(t_ui_element *elem)
{
	if (elem->element_type != UI_TYPE_INPUT)
	{
		ft_printf("[%s] Elem not of type UI_TYPE_INPUT. %d %s.\n",
			__FUNCTION__, elem->element_type,
			ui_element_type_to_string(elem->element_type));
		return (NULL);
	}
	return (elem->element);
}

t_ui_element	*ui_input_get_label_element(t_ui_element *elem)
{
	if (!elem)
		return (NULL);
	return (&((t_ui_input *)elem->element)->label);
}

t_ui_label	*ui_input_get_label(t_ui_element *elem)
{
	return (ui_input_get_label_element(elem)->element);
}
