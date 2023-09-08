/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Jony Salmi <jony.salmi@gmail.com>
 */

#include "libui.h"

void	ui_checkbox_new(t_ui_window *win, t_ui_element *elem)
{
	t_ui_checkbox	*checkbox;

	ui_element_new(win, elem);
	checkbox = ft_memalloc(sizeof(t_ui_checkbox));
	elem->element = checkbox;
	elem->element_type = UI_TYPE_CHECKBOX;
}

/*
 * NOTE for DEV:
 * try to keep this element only,
 * because its used in the radio buttons.
 * (or atleast should at some point)
*/
void	ui_checkbox_event(t_ui_element *elem, SDL_Event e)
{
	elem->is_hover = ui_element_is_hover(elem);
	if (elem->is_hover && elem->win->mouse_down_last_frame)
	{
		elem->was_click = 1;
		if (elem->is_toggle)
			ui_checkbox_toggle_off(elem);
		else
			ui_checkbox_toggle_on(elem);
	}
	if (elem->is_toggle)
		elem->is_click = 1;
	if (elem->is_click)
		elem->state = UI_STATE_CLICK;
	else if (elem->is_hover)
		elem->state = UI_STATE_HOVER;
	else
		elem->state = UI_STATE_DEFAULT;
	(void)e;
}

int	ui_checkbox_render(t_ui_element *elem)
{
	elem->was_click = 0;
	if (!ui_element_render(elem))
		return (0);
	return (1);
}

void	ui_checkbox_free(void *elem, size_t size)
{
	t_ui_element	*element;
	t_ui_checkbox	*checkbox;

	element = elem;
	if (!elem)
		return ;
	checkbox = element->element;
	if (!checkbox)
		return ;
	free(checkbox);
	(void)size;
}

void	ui_checkbox_edit(t_ui_element *elem, t_ui_recipe *recipe)
{
	(void)elem;
	(void)recipe;
}
