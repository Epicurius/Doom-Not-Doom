/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_input_event2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalmi <jsalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 19:23:12 by jsalmi            #+#    #+#             */
/*   Updated: 2021/12/10 19:23:13 by jsalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

void	ui_input_ctrl_events(
	t_ui_element *elem, t_ui_input *input, t_ui_label *label, SDL_Event e)
{
	char	*temp;
	int		small;
	int		big;

	small = ft_min(input->cursor_on_char_num, input->cursor_from_char_num);
	big = ft_max(input->cursor_on_char_num, input->cursor_from_char_num);
	if (e.key.keysym.sym == SDLK_c || e.key.keysym.sym == SDLK_x)
	{
		temp = ft_strsub(label->text, small, big - small);
		SDL_SetClipboardText(temp);
		ft_strdel(&temp);
		if (e.key.keysym.sym == SDLK_x)
			ui_input_remove_selected(elem);
	}
	if (e.key.keysym.sym == SDLK_v)
	{
		temp = SDL_GetClipboardText();
		ui_input_add(elem, temp);
		SDL_free(temp);
	}
	if (e.key.keysym.sym == SDLK_a)
	{
		input->cursor_from_char_num = 0;
		input->cursor_on_char_num = ft_strlen(label->text);
	}
}

void	ui_input_key_events(t_ui_element *elem, SDL_Event e)
{
	t_ui_input	*input;
	t_ui_label	*label;
	char		*temp;
	int			len;

	input = elem->element;
	label = ui_input_get_label(elem);
	len = ft_strlen(label->text);
	if (KMOD_LCTRL & SDL_GetModState())
		ui_input_ctrl_events(elem, input, label, e);
	else if (e.key.keysym.sym == SDLK_END)
		input->cursor_on_char_num = len;
	else if (e.key.keysym.sym == SDLK_HOME)
		input->cursor_on_char_num = 0;
	else if (e.key.keysym.sym == SDLK_LEFT)
		input->cursor_on_char_num--;
	else if (e.key.keysym.sym == SDLK_RIGHT)
		input->cursor_on_char_num++;
	else if (e.key.keysym.sym == SDLK_BACKSPACE
		|| e.key.keysym.sym == SDLK_DELETE)
		ui_input_remove(input, label, e);
	else if (!(KMOD_LSHIFT & SDL_GetModState()))
		ui_input_remove_selected(elem);
}

void	ui_input_mouse_events(
	t_ui_element *elem, t_ui_input *input, t_ui_label *lbl, SDL_Event e)
{
	int	i;

	e.button.clicks %= 4;
	if (e.button.clicks == 1)
	{
		input->cursor_on_char_num = get_nth_char_of_text_at_x(lbl->text,
				elem->win->mouse_pos.x - input->label.screen_pos.x, lbl->font);
		input->cursor_from_char_num = input->cursor_on_char_num;
	}
	else if (e.button.clicks == 2)
	{
		i = input->cursor_on_char_num;
		while (lbl->text[--i] && !ft_isspace(lbl->text[i]))
			;
		input->cursor_from_char_num = ft_clamp(++i, 0, ft_strlen(lbl->text));
		while (lbl->text[++i] && !ft_isspace(lbl->text[i]))
			;
		input->cursor_on_char_num = ft_clamp(i, 0, ft_strlen(lbl->text));
	}
	else if (e.button.clicks == 3)
	{
		input->cursor_from_char_num = 0;
		input->cursor_on_char_num = ft_strlen(lbl->text);
	}
}
