/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Jony Salmi <jony.salmi@gmail.com>
 */

#include "libui.h"

void	ui_input_new(t_ui_window *win, t_ui_element *elem)
{
	t_ui_input	*input;

	ui_element_new(win, elem);
	input = ft_memalloc(sizeof(t_ui_input));
	input->elem = elem;
	elem->element = input;
	elem->element_type = UI_TYPE_INPUT;
	ui_label_new(win, &input->label);
	ui_label_set_text(&input->label, "Input Text");
	ui_element_set_parent(&input->label, elem, UI_TYPE_ELEMENT);
	ui_label_new(win, &input->placeholder);
	ui_label_set_text(&input->placeholder, "Placeholder");
	ui_element_set_parent(&input->placeholder, elem, UI_TYPE_ELEMENT);
	input->label.is_a_part_of_another = 1;
	input->placeholder.is_a_part_of_another = 1;
	input->label.render_me_on_parent = 1;
	input->placeholder.render_me_on_parent = 1;
}

void	ui_input_edit(t_ui_element *elem, t_ui_recipe *recipe)
{
	t_ui_input	*input;

	input = elem->element;
	ui_label_edit(&input->label, recipe);
	ui_label_edit(&input->placeholder, recipe);
	if (recipe->placeholder_text)
	{
		ui_label_set_text(&input->placeholder, recipe->placeholder_text);
		ui_label_color_set(&input->placeholder,
			ui_color_change_brightness(
				ui_label_get_label(&input->label)->font_color, -0.5));
	}
	input->input_type = recipe->input_type;
}

void	ui_input_render_highlight(t_ui_element *elem)
{
	t_vec2i		pos_on;
	t_vec2i		pos_from;
	t_ui_input	*input;
	t_ui_label	*label;
	t_vec2i		w;

	input = elem->element;
	label = ui_input_get_label(elem);
	pos_on = vec2i(input->cursor_on_char_x + elem->screen_pos.x,
			elem->screen_pos.y + 2);
	pos_from = vec2i(input->cursor_from_char_x + elem->screen_pos.x,
			elem->screen_pos.y + 2);
	SDL_SetRenderTarget(elem->win->renderer, elem->win->texture);
	SDL_SetRenderDrawColor(elem->win->renderer, 255, 0, 0, 255);
	SDL_RenderDrawLine(elem->win->renderer,
		pos_on.x, pos_on.y, pos_on.x, pos_on.y + elem->screen_pos.h - 4);
	SDL_SetRenderDrawColor(elem->win->renderer, 0, 0, 255, 255);
	SDL_RenderDrawLine(elem->win->renderer, pos_from.x, pos_from.y,
		pos_from.x, pos_from.y + elem->screen_pos.h - 4);
	SDL_SetRenderDrawColor(elem->win->renderer, 0, 0, 255, 255);
	w.x = ft_max(pos_from.x, pos_on.x);
	w.y = ft_min(pos_from.x, pos_on.x);
	SDL_RenderFillRect(elem->win->renderer,
		&(SDL_Rect){w.y, pos_from.y, w.x - w.y, elem->screen_pos.h - 4});
	SDL_SetRenderTarget(elem->win->renderer, NULL);
}

int	ui_input_render(t_ui_element *elem)
{
	t_ui_input	*input;
	t_ui_label	*label;

	input = elem->element;
	label = input->label.element;
	if (!ui_element_render(elem))
		return (0);
	input->input_exit = 0;
	if (label->text_wh.x > 0 || elem->is_click)
		input->placeholder.show = 0;
	else
		input->placeholder.show = 1;
	if (elem->is_click)
	{
		input->cursor_on_char_x = get_x_of_char_in_text(label->text,
				input->cursor_on_char_num, label->font) + input->label.pos.x;
		input->cursor_from_char_x = get_x_of_char_in_text(label->text,
				input->cursor_from_char_num, label->font) + input->label.pos.x;
		ui_input_render_highlight(elem);
	}
	ui_label_render(&input->label);
	ui_label_render(&input->placeholder);
	return (1);
}

void	ui_input_free(void *elem, size_t size)
{
	t_ui_element	*element;
	t_ui_input		*input;

	element = elem;
	if (!element)
		return ;
	input = element->element;
	if (!input)
		return ;
	free(input);
	(void)size;
}
