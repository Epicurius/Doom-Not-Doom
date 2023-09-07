/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Jony Salmi <jony.salmi@gmail.com>
 */

#include "libui.h"

void	ui_scroll_value_set(t_ui_element *elem, int value)
{
	t_ui_scrollbar	*scroll;

	scroll = elem->element;
	scroll->value = value;
	scroll->button.pos.y = ft_clamp(
			ui_set_slider_value(
				value, scroll->min, scroll->max,
				elem->pos.h - scroll->button.pos.h),
			0, elem->pos.h - scroll->button.pos.h);
	scroll->update = 1;
}

/*
 * updates the target size of the scrollbar;
*/
void	ui_scrollbar_update_target_size(t_ui_element *elem)
{
	t_list			*curr;
	t_ui_scrollbar	*scroll;
	t_ui_element	*child;

	scroll = elem->element;
	curr = ((t_ui_element *)scroll->target)->children;
	if (curr)
	{
		scroll->top_most = vec2i(0, ((t_ui_element *)curr->content)->pos.y);
		scroll->bot_most = vec2i(0, ((t_ui_element *)curr->content)->pos.y);
		while (curr)
		{
			child = curr->content;
			if (child->pos.y < scroll->top_most.y)
				scroll->top_most.y = child->pos.y;
			if (child->pos.y + child->pos.h > scroll->bot_most.y)
				scroll->bot_most.y = child->pos.y + child->pos.h;
			curr = curr->next;
		}
		scroll->target_size = abs(scroll->bot_most.y - scroll->top_most.y);
	}
	else
		scroll->target_size = 0;
}

/*
 * recalculates the value of the list of childrens size;
*/
void	ui_scrollbar_recount(t_ui_element *elem)
{
	t_ui_scrollbar	*scroll;
	int				new_h;

	scroll = elem->element;
	ui_scrollbar_update_target_size(elem);
	if (((t_ui_element *)scroll->target)->pos.h - scroll->target_size < 0)
		scroll->max = fabsf(((t_ui_element *)scroll->target)->pos.h
				- scroll->target_size);
	else
		scroll->max = 0;
	new_h = (((t_ui_element *)scroll->target)->pos.h / scroll->target_size)
		*elem->pos.h;
	new_h = ft_clamp(elem->pos.h, elem->pos.h * 0.05, new_h);
	ui_element_pos_set(&scroll->button,
		vec4(scroll->button.pos.x, scroll->button.pos.y,
			scroll->button.pos.w, new_h));
}
