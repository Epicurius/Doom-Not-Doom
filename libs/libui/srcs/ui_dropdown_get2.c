/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_dropdown_get2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalmi <jsalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 19:22:20 by jsalmi            #+#    #+#             */
/*   Updated: 2021/12/10 19:22:21 by jsalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
