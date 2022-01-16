/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_button2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalmi <jsalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 19:22:02 by jsalmi            #+#    #+#             */
/*   Updated: 2021/12/10 19:22:04 by jsalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

void	ui_button_toggle_on(t_ui_element *elem)
{
	if (elem)
	{
		elem->is_toggle = 1;
		elem->state = UI_STATE_CLICK;
	}
}

bool	ui_button(t_ui_element *elem)
{
	if (elem->is_click)
	{
		elem->is_click = 0;
		elem->is_hover = 0;
		elem->state = UI_STATE_CLICK;
		return (1);
	}
	return (0);
}

void	ui_button_print(t_ui_element *elem)
{
	t_ui_button	*button;

	if (elem->element_type != UI_TYPE_BUTTON)
	{
		ft_printf("[%s] Not elem of type button. <%d : %s>",
			__FUNCTION__, elem->element_type,
			ui_element_type_to_string(elem->element_type));
		return ;
	}
	button = ui_button_get_button(elem);
	if (!button)
		return ;
	ui_label_print(&button->label);
}

void	ui_button_set_text(t_ui_element *elem, char *str)
{
	t_ui_element		*label;

	label = ui_button_get_label_element(elem);
	ui_label_set_text(label, str);
}

char	*ui_button_get_text(t_ui_element *elem)
{
	t_ui_element		*label;

	label = ui_button_get_label_element(elem);
	return (ui_label_get_text(label));
}
