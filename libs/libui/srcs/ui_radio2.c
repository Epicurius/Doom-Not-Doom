/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Jony Salmi <jony.salmi@gmail.com>
 */

#include "libui.h"

/*
 * if 'toggle_this' is in radio button list it will toggle it on,
 * and untoggle all the other buttons;
*/
void	ui_radio_button_toggle_on(t_ui_element *elem, t_ui_element *toggle_this)
{
	t_ui_element	*child;
	t_ui_radio		*radio;
	t_list			*curr;

	radio = elem->element;
	curr = elem->children;
	while (curr)
	{
		child = curr->content;
		if (toggle_this == child)
			radio->active = toggle_this;
		else
			child->state = UI_STATE_DEFAULT;
		curr = curr->next;
	}
	if (radio->active)
		radio->active->state = UI_STATE_CLICK;
}
