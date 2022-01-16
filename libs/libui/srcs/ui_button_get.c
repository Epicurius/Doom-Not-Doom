/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_button_get.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalmi <jsalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 19:21:54 by jsalmi            #+#    #+#             */
/*   Updated: 2021/12/10 19:21:57 by jsalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		ft_printf("[%s] Elem is not of type button. <%d : %s>\n",
			__FUNCTION__, elem->element_type,
			ui_element_type_to_string(elem->element_type));
		return (NULL);
	}
	return (elem->element);
}

t_ui_element	*ui_button_get_label_element(t_ui_element *elem)
{
	t_ui_button	*button;

	if (!elem)
	{
		ft_printf("[%s] No element.\n", __FUNCTION__);
		return (NULL);
	}
	if (elem->element_type != UI_TYPE_BUTTON)
	{
		ft_printf("[%s] Element not of type UI_TYPE_BUTTON. It\'s %d %s.",
			__FUNCTION__, elem->element_type,
			ui_element_type_to_string(elem->element_type));
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
	ft_printf("[%s] No button with text %s in list.\n", __FUNCTION__, str);
	return (NULL);
}
