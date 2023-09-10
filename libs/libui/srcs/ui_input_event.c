/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Jony Salmi <jony.salmi@gmail.com>
 */

#include "libui.h"

void	ui_input_decide_clickiness(
	t_ui_element *elem, t_ui_input *input, SDL_Event e)
{
	static unsigned int	text_started = 0;

	if (elem->is_hover && elem->win->mouse_down)
	{
		if (!elem->is_click)
		{
			SDL_StartTextInput();
			text_started++;
		}
		elem->is_click = 1;
	}
	else if (elem->is_click && ((!elem->is_hover && elem->win->mouse_down)
			|| (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN)))
	{
		text_started--;
		if (text_started == 0)
			SDL_StopTextInput();
		elem->is_click = 0;
		input->input_exit = 1;
	}
}

void	ui_input_remove(t_ui_input *input, t_ui_label *label, SDL_Event e)
{
	int	small;
	int	big;

	small = ft_min(input->cursor_on_char_num, input->cursor_from_char_num);
	big = ft_max(input->cursor_on_char_num, input->cursor_from_char_num);
	if (big - small == 0)
	{
		if (e.key.keysym.sym == SDLK_BACKSPACE)
		{
			remove_str_from_n_to_m(&label->text, small - 1, small);
			input->cursor_on_char_num
				= ft_max(input->cursor_on_char_num - 1, 0);
			input->cursor_from_char_num = input->cursor_on_char_num;
		}
		else
			remove_str_from_n_to_m(&label->text, small, small + 1);
	}
	else
		remove_str_from_n_to_m(&label->text, small, big);
}

/*
 * IMPORTANT: Remember that when you have pressed lshift,
 *		it will not reset the from_char_num...
 *		 ...so whatever you do to this dont change that.!
 *
 * Dont unselect if you have pressed control or
 *	if you have typed a capital letter by holding shift;
 *
 *  int	text_input_shift_pressed;
 * 		is for capital chars. we dont want the selection to automatically
 * 		select the just typed capital letter and then you have to unselect
 * 		it manually before continuing your typing....
*/
void	ui_input_check_if_unselect(t_ui_element *elem, SDL_Event e)
{
	t_ui_input	*input;
	int			text_input_key_pressed;
	int			text_input_shift_pressed;

	input = elem->element;
	text_input_key_pressed = e.type == SDL_TEXTINPUT || e.type == SDL_KEYDOWN;
	text_input_shift_pressed = e.type == SDL_TEXTINPUT
		&& (KMOD_LSHIFT & SDL_GetModState());
	if (text_input_key_pressed && !(KMOD_LCTRL & SDL_GetModState())
		&& (text_input_shift_pressed || !(KMOD_LSHIFT & SDL_GetModState())))
		input->cursor_from_char_num = input->cursor_on_char_num;
}

void	ui_input(t_ui_element *elem, SDL_Event e)
{
	t_ui_input	*input;
	t_ui_label	*lbl;
	int			len;

	input = elem->element;
	lbl = ui_input_get_label(elem);
	if (e.type == SDL_TEXTINPUT)
		ui_input_add(elem, e.text.text);
	else if (e.type == SDL_KEYDOWN)
		ui_input_key_events(elem, e);
	if (e.type == SDL_MOUSEBUTTONDOWN)
		ui_input_mouse_events(elem, input, lbl, e);
	else if (elem->is_hover && elem->win->mouse_down == SDL_BUTTON_LEFT
		&& e.type == SDL_MOUSEMOTION)
	{
		if (elem->win->mouse_down_last_frame)
			input->cursor_from_char_num = input->cursor_on_char_num;
		input->cursor_on_char_num = get_nth_char_of_text_at_x(lbl->text,
				elem->win->mouse_pos.x - input->label.screen_pos.x, lbl->font);
	}
	lbl->texture_recreate = 1;
	len = ft_strlen(lbl->text);
	input->cursor_on_char_num = ft_clamp(input->cursor_on_char_num, 0, len);
	input->cursor_from_char_num = ft_clamp(input->cursor_from_char_num, 0, len);
	ui_input_check_if_unselect(elem, e);
}

void	ui_input_event(t_ui_element *elem, SDL_Event e)
{
	t_ui_input			*input;

	input = elem->element;
	if (!elem->rendered_last_frame || !elem->event)
		return ;
	elem->is_hover = ui_element_is_hover(elem);
	ui_input_decide_clickiness(elem, input, e);
	if (elem->is_click)
		ui_input(elem, e);
}
