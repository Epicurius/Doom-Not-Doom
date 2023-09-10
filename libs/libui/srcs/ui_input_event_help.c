/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Jony Salmi <jony.salmi@gmail.com>
 */

#include "libui.h"

void	ui_input_remove_selected(t_ui_element *elem)
{
	t_ui_input	*input;
	t_ui_label	*label;
	int			small;
	int			big;

	input = elem->element;
	label = ui_input_get_label(elem);
	small = ft_min(input->cursor_on_char_num, input->cursor_from_char_num);
	big = ft_max(input->cursor_on_char_num, input->cursor_from_char_num);
	if (big - small > 0)
	{
		remove_str_from_n_to_m(&label->text, small, big);
		input->cursor_on_char_num = small;
		input->cursor_from_char_num = input->cursor_on_char_num;
	}
}

void	ui_input_add(t_ui_element *elem, char *str)
{
	t_ui_input	*input;
	t_ui_label	*label;
	char		*temp;

	input = elem->element;
	label = ui_input_get_label(elem);
	ui_input_remove_selected(elem);
	if (input->input_type == 1)
		temp = str_remove_all_letters(str);
	else if (input->input_type == 2)
		temp = str_remove_all_numbers(str);
	else
		temp = ft_strdup(str);
	insert_str_after_nth_char(&label->text, temp, input->cursor_on_char_num);
	input->cursor_on_char_num += ft_strlen(temp);
	input->cursor_from_char_num = input->cursor_on_char_num;
	ft_strdel(&temp);
}
