/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_scrollbar_get.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalmi <jsalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 19:24:19 by jsalmi            #+#    #+#             */
/*   Updated: 2021/12/10 19:24:23 by jsalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		ft_printf("[%s] Elem not of type UI_TYPE_SCROLLBAR. %d %s.\n",
			__FUNCTION__, elem->element_type,
			ui_element_type_to_string(elem->element_type));
		return (NULL);
	}
	return (&((t_ui_scrollbar *)elem->element)->button);
}

t_ui_button	*ui_scrollbar_get_button(t_ui_element *elem)
{
	if (elem->element_type != UI_TYPE_SCROLLBAR)
	{
		ft_printf("[%s] Elem not of type UI_TYPE_SCROLLBAR. %d %s.\n",
			__FUNCTION__, elem->element_type,
			ui_element_type_to_string(elem->element_type));
		return (NULL);
	}
	return (((t_ui_scrollbar *)elem->element)->button.element);
}
