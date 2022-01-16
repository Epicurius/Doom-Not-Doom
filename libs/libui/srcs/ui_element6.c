/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_element6.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalmi <jsalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 19:22:43 by jsalmi            #+#    #+#             */
/*   Updated: 2021/12/10 19:22:44 by jsalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
