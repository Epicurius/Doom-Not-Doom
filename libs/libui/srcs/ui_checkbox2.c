/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_checkbox2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalmi <jsalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 19:22:07 by jsalmi            #+#    #+#             */
/*   Updated: 2021/12/10 19:22:09 by jsalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

/*
 * We don't need to check if the element_type is checkbox,
 * 	because we don't do anything to the checkbox element.
 * Might make this ui_element_toggle_on rather;
*/
void	ui_checkbox_toggle_on(t_ui_element *elem)
{
	elem->is_click = 1;
	elem->is_toggle = 1;
	elem->was_click = 1;
	elem->state = UI_STATE_CLICK;
}

void	ui_checkbox_toggle_off(t_ui_element *elem)
{
	elem->is_click = 0;
	elem->is_toggle = 0;
	if (elem->state == UI_STATE_CLICK)
		elem->state = UI_STATE_DEFAULT;
}

void	ui_checkbox_toggle_accordingly(t_ui_element *elem, bool want_to_toggle)
{
	if (want_to_toggle)
		ui_checkbox_toggle_on(elem);
	else
		ui_checkbox_toggle_off(elem);
}
