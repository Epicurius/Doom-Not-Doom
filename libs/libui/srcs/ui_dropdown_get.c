/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_dropdown_get.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalmi <jsalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 19:22:13 by jsalmi            #+#    #+#             */
/*   Updated: 2021/12/10 19:22:19 by jsalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

t_ui_element	*ui_dropdown_get(t_ui_element *elem, int ui_type)
{
	if (elem->element_type == UI_TYPE_DROPDOWN)
	{
		if (ui_type == UI_TYPE_MENU)
			return (ui_dropdown_get_menu_element(elem));
		if (ui_type == UI_TYPE_SCROLLBAR)
			return (ui_dropdown_get_scrollbar_element(elem));
	}
	ft_printf("[%s] Something went wrong.\n", __FUNCTION__);
	return (NULL);
}

t_ui_menu	*ui_dropdown_get_menu(t_ui_element *elem)
{
	t_ui_dropdown	*drop;
	t_ui_menu		*menu;

	drop = ui_dropdown_get_dropdown(elem);
	if (!drop)
		return (NULL);
	return (ui_menu_get_menu(&drop->menu));
}

t_ui_element	*ui_dropdown_get_menu_element(t_ui_element *elem)
{
	if (elem->element_type == UI_TYPE_DROPDOWN)
		return (&ui_dropdown_get_dropdown(elem)->menu);
	ft_printf("[%s] Something went wrong.\n", __FUNCTION__);
	return (NULL);
}

t_ui_element	*ui_dropdown_get_scrollbar_element(t_ui_element *elem)
{
	if (elem->element_type == UI_TYPE_DROPDOWN)
		return (&ui_dropdown_get_dropdown(elem)->scrollbar);
	ft_printf("[%s] Something went wrong.\n", __FUNCTION__);
	return (NULL);
}

t_ui_scrollbar	*ui_dropdown_get_scrollbar(t_ui_element *elem)
{
	t_ui_element	*scroll;

	if (elem->element_type != UI_TYPE_DROPDOWN)
		return (NULL);
	scroll = ui_dropdown_get_scrollbar_element(elem);
	if (!scroll)
		return (NULL);
	return (scroll->element);
}
