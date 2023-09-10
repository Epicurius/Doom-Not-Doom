/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Jony Salmi <jony.salmi@gmail.com>
 */

#include "libui.h"

void	ui_button_new(t_ui_window *win, t_ui_element *elem)
{
	t_ui_button	*button;

	ui_element_new(win, elem);
	elem->element = ft_memalloc(sizeof(t_ui_button));
	elem->element_type = UI_TYPE_BUTTON;
	button = elem->element;
	button->elem = elem;
	ui_element_color_set(elem, UI_STATE_DEFAULT, 0xff95d7ae);
	ui_element_color_set(elem, UI_STATE_HOVER, 0xff7bae7f);
	ui_element_color_set(elem, UI_STATE_CLICK, 0xff73956f);
	ui_label_new(win, &button->label);
	button->label.is_a_part_of_another = 1;
	ui_element_set_parent(&button->label, elem, UI_TYPE_ELEMENT);
	ui_label_text_align(&button->label, UI_TEXT_ALIGN_CENTER);
}

void	ui_button_edit(t_ui_element *elem, t_ui_recipe *recipe)
{
	t_ui_button	*button;

	button = elem->element;
	ui_label_edit(&button->label, recipe);
}

void	ui_button_event(t_ui_element *elem, SDL_Event e)
{
	if (!elem->show || !elem->event)
		return ;
	elem->is_hover = ui_element_is_hover(elem);
	if (elem->is_hover && elem->win->mouse_down)
		elem->is_click = 1;
	if (elem->is_click && !elem->win->mouse_down)
		elem->is_click = 0;
	if (elem->is_click)
		elem->state = UI_STATE_CLICK;
	else if (elem->is_hover)
		elem->state = UI_STATE_HOVER;
	else
		elem->state = UI_STATE_DEFAULT;
	elem->was_click = elem->is_click;
	if (elem->is_toggle == 1)
		elem->state = UI_STATE_CLICK;
}

/*
 * NOTE: !!!!! Dont do anything that needs the element type to be UI_TYPE_BUTTOn
 * since our dropdown is using this button_redner for reason.!!!!!!!!!!!!!!!!!!!
*/
int	ui_button_render(t_ui_element *elem)
{
	t_ui_button	*button;
	t_ui_label	*label;

	if (!ui_element_render(elem))
		return (0);
	button = elem->element;
	label = button->label.element;
	ui_label_render(&button->label);
	ui_label_text_align(&button->label, label->text_align);
	return (1);
}

void	ui_button_free(void *elem, size_t size)
{
	t_ui_element	*element;
	t_ui_button		*button;

	element = elem;
	if (!elem)
		return ;
	button = element->element;
	if (!button)
		return ;
	free(button);
	(void)size;
}
