/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buy_menu_buttons.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalmi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 15:38:37 by jsalmi            #+#    #+#             */
/*   Updated: 2021/07/28 15:43:22 by jsalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buymenu.h"

t_bui_element	*new_stat(
		t_bui_element *parent, char *str, t_xywh pos)
{
	t_bui_element	*elem;

	elem = bui_new_element(parent, str, pos);
	bui_set_element_color(elem, 0x00000000);
	elem->font_style = TTF_STYLE_BOLD;
	bui_center_element_text_y(elem);
	elem->text_x = pos.w / 32;
	bui_set_element_text_font(elem, TTF_PATH"ShareTechMono-Regular.ttf",
		18, 0xff72e26c);
	elem->clear = 1;
	return (elem);
}

t_bui_element	*new_button(t_bui_element *parent, char *name, t_xywh c)
{
	t_bui_element	*elem;

	elem = bui_new_element(parent, name, c);
	bui_set_element_color(elem, 0x00000000);
	bui_set_element_state_border(elem, 2, 0xf072e26c, ELEMENT_HOVER);
	draw_rect(elem->surface[2], new_xywh(4, 4, c.w - 8, c.h - 8),
		0xf072e26c, 0);
	elem->update_state = 0;
	elem->clear = 1;
	elem->font_style = TTF_STYLE_BOLD;
	bui_set_element_text_font(elem, TTF_PATH"ShareTechMono-Regular.ttf",
		18, 0xff72e26c);
	bui_center_element_text_y(elem);
	elem->text_x = elem->position.w / 8;
	return (elem);
}

t_bui_element	*new_buy_button(t_bui_element *parent, t_xywh c)
{
	t_bui_element	*buy_button;

	buy_button = bui_new_element(parent, "Buy", c);
	bui_set_element_color(buy_button, 0x00000000);
	bui_set_element_state_border(buy_button, 2, 0xf072e26c, ELEMENT_HOVER);
	draw_rect(buy_button->surface[2], new_xywh(4, 4, c.w - 8, c.h - 8),
		0xf072e26c, 0);
	bui_set_element_text_font(buy_button,
		TTF_PATH"ShareTechMono-Regular.ttf", 18, 0xff72e26c);
	buy_button->clear = 1;
	bui_center_element_text_y(buy_button);
	buy_button->text_x = buy_button->position.w / 8;
	return (buy_button);
}

t_bui_element	*new_upgrade_button(t_bui_element *parent, char *str, int i)
{
	int				x;
	int				w;
	int				h;
	t_xywh			c;
	t_bui_element	*elem;

	x = 0;
	w = parent->position.w;
	h = 50;
	c = new_xywh(x, i * h + ((i + 1) * 10) + 10, w, h);
	elem = bui_new_element(parent, str, c);
	bui_set_element_color(elem, 0x00000000);
	bui_set_element_state_border(elem, 2, 0xf072e26c, ELEMENT_HOVER);
	draw_rect(elem->surface[2], new_xywh(4, 4, c.w - 8, c.h - 8),
		0xf072e26c, 0);
	bui_set_element_text_font(elem,
		TTF_PATH"ShareTechMono-Regular.ttf", 18, 0xff72e26c);
	elem->clear = 1;
	bui_center_element_text_y(elem);
	elem->text_x = elem->position.w / 16;
	return (elem);
}
