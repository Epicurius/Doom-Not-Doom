/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Jony Salmi <jony.salmi@gmail.com>
 */

#include "libui.h"

/*
 * Returns from button element its child elements
 * 	(that are specific to this type of element only);
*/
t_ui_element	*ui_button_get(t_ui_element *elem, int ui_type)
{
	if (elem->element_type != UI_TYPE_BUTTON)
		return (NULL);
	if (ui_type == UI_TYPE_LABEL)
		return (ui_button_get_label_element(elem));
	return (NULL);
}

t_ui_button	*ui_button_get_button(t_ui_element *elem)
{
	if (elem->element_type != UI_TYPE_BUTTON)
	{
		LG_WARN("Element is not of type UI_TYPE_BUTTON. <%d : %s>",
			elem->element_type, ui_element_type_to_string(elem->element_type));
		return (NULL);
	}
	return (elem->element);
}

t_ui_element	*ui_button_get_label_element(t_ui_element *elem)
{
	t_ui_button	*button;

	if (!elem)
	{
		LG_WARN("No element.");
		return (NULL);
	}
	if (elem->element_type != UI_TYPE_BUTTON)
	{
		LG_WARN("Element is not of type UI_TYPE_BUTTON. <%d : %s>",
			elem->element_type, ui_element_type_to_string(elem->element_type));
		return (NULL);
	}
	button = elem->element;
	if (!button)
		return (NULL);
	return (&button->label);
}

t_ui_label	*ui_button_get_label(t_ui_element *elem)
{
	t_ui_element	*label;

	label = ui_button_get_label_element(elem);
	if (!label)
		return (NULL);
	return (label->element);
}

/*
 * From list get the button with str as text;
*/
t_ui_element	*ui_list_get_button_with_text(t_list *list, const char *str)
{
	while (list)
	{
		if (ft_strequ(ui_button_get_text(list->content), str))
			return (list->content);
		list = list->next;
	}
	LG_WARN("No button with text %s in list.", str);
	return (NULL);
}
