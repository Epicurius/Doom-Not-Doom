/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Jony Salmi <jony.salmi@gmail.com>
 */

#include "libui.h"

void	ui_input_print(t_ui_element *elem)
{
	t_ui_input	*input;

	if (elem->element_type != UI_TYPE_INPUT)
		return ;
	input = elem->element;
	ui_label_print(&input->label);
	ui_label_print(&input->placeholder);
}

char	*ui_input_get_text(t_ui_element *elem)
{
	t_ui_input	*input;
	t_ui_label	*label;

	if (!elem)
		return (NULL);
	input = elem->element;
	if (!input)
		return (NULL);
	label = input->label.element;
	if (!label)
		return (NULL);
	return (label->text);
}

void	ui_input_set_text(t_ui_element *elem, char *str)
{
	ui_label_set_text(ui_input_get_label_element(elem), str);
}

void	ui_input_set_placeholder_text(t_ui_element *elem, char *str)
{
	ui_label_set_text(&ui_input_get(elem)->placeholder, str);
}

int	ui_input_exit(t_ui_element *elem)
{
	return (((t_ui_input *)elem->element)->input_exit);
}
