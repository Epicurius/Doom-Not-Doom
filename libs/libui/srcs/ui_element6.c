/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Jony Salmi <jony.salmi@gmail.com>
 */

#include "libui.h"

/*
 * We have this only so that we wouldnt have errors spamming the terminal.
*/
void	ui_element_event(t_ui_element *elem, SDL_Event e)
{
	(void)elem;
	(void)e;
}

int	ui_element_is_hover(t_ui_element *elem)
{
	if (elem->show
		&& elem->rendered_last_frame
		&& *elem->parent_show // Why was this commented out?;
		&& point_in_rect(elem->win->mouse_pos, elem->to_pos))
		return (1);
	return (0);
}

/*
 * Was the element hovered last frame.
*/
int	ui_element_was_hover(t_ui_element *elem)
{
	if (elem->rendered_last_frame
		&& point_in_rect(elem->win->mouse_pos_prev, elem->to_pos))
		return (1);
	return (0);
}

int	ui_element_is_click(t_ui_element *elem)
{
	if (ui_element_is_hover(elem) && elem->win->mouse_down)
		return (1);
	return (0);
}
