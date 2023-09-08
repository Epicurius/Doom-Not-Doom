/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Jony Salmi <jony.salmi@gmail.com>
 */

#include "libui.h"

void	ui_scrollbar_new(t_ui_window *win, t_ui_element *elem)
{
	t_ui_scrollbar	*scroll;

	ui_element_new(win, elem);
	elem->element = ft_memalloc(sizeof(t_ui_scrollbar));
	elem->element_type = UI_TYPE_SCROLLBAR;
	scroll = elem->element;
	ui_button_new(win, &scroll->button);
	scroll->button.is_a_part_of_another = 1;
	ui_element_set_parent(&scroll->button, elem, UI_TYPE_ELEMENT);
	ui_element_pos_set(&scroll->button, vec4(0, 0, elem->pos.h, elem->pos.h));
	scroll->button.colors[UI_STATE_DEFAULT] = UI_COLOR_ORANGEISH;
	scroll->button.colors[UI_STATE_HOVER] = UI_COLOR_ORANGEISH_DARKER;
	scroll->button.colors[UI_STATE_CLICK] = UI_COLOR_ORANGEISH_DARKEST;
	ui_label_size_set(&ui_scrollbar_get_button(elem)->label, 20);
	ui_label_set_text(&ui_scrollbar_get_button(elem)->label, "=");
	scroll->min = 0;
	scroll->max = 100;
}

/*
 * TODO: maybe dont event handle if the target is not shown.
*/
void	ui_scrollbar_event(t_ui_element *elem, SDL_Event e)
{
	t_ui_scrollbar	*scroll;
	t_ui_button		*button;

	if (!elem->show || !elem->event)
		return ;
	scroll = elem->element;
	button = scroll->button.element;
	if (ui_element_is_click(elem))
	{
		scroll->value = ui_get_slider_value(scroll->min, scroll->max,
				(elem->win->mouse_pos.y - elem->screen_pos.y)
				- scroll->button.pos.h / 2,
				elem->pos.h - scroll->button.pos.h);
		scroll->update = 1;
	}
	else if (ui_element_is_hover(scroll->target)
		&& ((t_ui_element *)scroll->target)->win->scroll != 0)
	{
		scroll->value -= ((t_ui_element *)scroll->target)->win->scroll * 30;
		scroll->value = ft_clamp(scroll->value, scroll->min, scroll->max);
		scroll->update = 1;
	}
	(void)e;
}

/*
 * TODO: maybe dont event render if the target is not shown.
*/
int	ui_scrollbar_render(t_ui_element *elem)
{
	t_ui_scrollbar	*scroll;
	t_ui_button		*button;

	if (!ui_element_render(elem))
		return (0);
	scroll = elem->element;
	button = scroll->button.element;
	if (scroll->target)
		elem->z = ((t_ui_element *)scroll->target)->z;
	ui_scrollbar_recount(elem);
	if (scroll->update)
	{
		scroll->button.pos.y = ft_clamp(
				ui_set_slider_value(
					scroll->value, scroll->min,
					scroll->max, elem->pos.h - scroll->button.pos.h),
				0, elem->pos.h - scroll->button.pos.h);
		scroll->update = 0;
		ui_element_move_list(((t_ui_element *)scroll->target)->children,
			vec2i(0, scroll->last_value - scroll->value));
	}
	scroll->last_value = scroll->value;
	ui_button_render(&scroll->button);
	return (1);
}

void	ui_scrollbar_edit(t_ui_element *elem, t_ui_recipe *recipe)
{
	t_ui_scrollbar	*scroll;

	scroll = elem->element;
	if (recipe->target)
		scroll->target = ui_list_get_element_by_id(
				elem->win->layout->elements, recipe->target);
	if (recipe->value_set[1])
		scroll->min = recipe->value[1];
	if (recipe->value_set[2])
		scroll->max = recipe->value[2];
	if (recipe->value_set[0])
		ui_scroll_value_set(elem, recipe->value[0]);
}

void	ui_scrollbar_free(void *elem, size_t size)
{
	t_ui_element	*element;
	t_ui_scrollbar	*scroll;

	element = elem;
	if (!element)
		return ;
	scroll = element->element;
	if (!scroll)
		return ;
	scroll->target = NULL;
	free(scroll);
	(void)size;
}
