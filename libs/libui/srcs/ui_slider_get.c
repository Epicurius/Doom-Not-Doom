/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_slider_get.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalmi <jsalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 19:24:31 by jsalmi            #+#    #+#             */
/*   Updated: 2021/12/10 19:24:32 by jsalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

t_ui_element	*ui_slider_get(t_ui_element *elem, int ui_type)
{
	if (elem->element_type == UI_TYPE_SLIDER
		&& ui_type == UI_TYPE_BUTTON)
		return (ui_slider_get_button_element(elem));
	return (NULL);
}

t_ui_element	*ui_slider_get_button_element(t_ui_element *elem)
{
	if (elem->element_type == UI_TYPE_SLIDER)
		return (&ui_slider_get_slider(elem)->button);
	return (NULL);
}

t_ui_slider	*ui_slider_get_slider(t_ui_element *elem)
{
	if (elem->element_type == UI_TYPE_SLIDER)
		return (elem->element);
	return (NULL);
}
