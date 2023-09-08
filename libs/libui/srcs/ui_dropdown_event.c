/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Jony Salmi <jony.salmi@gmail.com>
 */

#include "libui.h"

void	ui_dropdown_check_active_internal(
	t_ui_element *elem, t_ui_dropdown *drop)
{
	if (ui_list_radio_event(drop->menu.children, &drop->active))
	{
		ui_element_render(drop->active);
		ui_label_set_text(&drop->label, ui_dropdown_active_text(elem));
	}
}

void	ui_dropdown_event2(t_ui_element *elem, SDL_Event e)
{
	t_ui_dropdown	*drop;
	t_list			*curr;
	t_ui_element	*child;

	drop = elem->element;
	ui_dropdown_check_active_internal(elem, drop);
	curr = drop->menu.children;
	drop->total_h = 0;
	while (curr)
	{
		child = curr->content;
		ui_element_pos_set2(child, vec2(child->pos.x, drop->total_h
				- ((t_ui_scrollbar *)drop->scrollbar.element)->value));
		drop->total_h += child->pos.h;
		child->render_me_on_parent = 1;
		curr = curr->next;
	}
	drop->scrollbar.show = 0;
	if (drop->max_h != -1 && drop->total_h > drop->max_h)
	{
		drop->scrollbar.show = 1;
		ui_scrollbar_event(&drop->scrollbar, e);
	}
	ui_element_pos_set(&drop->menu, vec4(drop->menu.pos.x, drop->menu.pos.y,
			drop->menu.pos.w, drop->total_h + 1));
}

void	ui_dropdown_event(t_ui_element *elem, SDL_Event e)
{
	t_ui_dropdown	*drop;

	if (!elem->show || !elem->event)
		return ;
	drop = elem->element;
	ui_checkbox_event(elem, e);
	drop->menu.show = elem->state == UI_STATE_CLICK;
	if (!drop->menu.show)
	{
		ui_checkbox_toggle_off(elem);
		drop->scrollbar.show = 0;
		return ;
	}
	drop->drop_open = (elem->win->mouse_down_last_frame
			&& ui_element_is_hover(elem));
	ui_menu_event(&drop->menu, e);
	ui_dropdown_event2(elem, e);
	if (elem->win->mouse_down && !ui_element_is_hover(elem)
		&& !ui_element_is_hover(&drop->scrollbar))
	{
		ui_checkbox_toggle_off(elem);
		drop->menu.show = 0;
		drop->drop_exit = 1;
		drop->scrollbar.show = 0;
	}
}
