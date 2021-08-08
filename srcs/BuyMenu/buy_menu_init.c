/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buy_menu_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalmi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 15:38:42 by jsalmi            #+#    #+#             */
/*   Updated: 2021/07/28 15:38:43 by jsalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buymenu.h"

void	menu_init(t_bui_window *win, t_buymenu *buymenu)
{
	t_xywh	c;

	c = new_xywh(0, 0, win->position.w, win->position.h);
	buymenu->menu = bui_new_menu(win, NULL, c);
	bui_set_element_image_from_path(buymenu->menu, ELEMENT_DEFAULT,
		ICON_PATH"test2.bmp", NULL);
	bui_set_element_image_from_path(buymenu->menu, ELEMENT_DEFAULT,
		ICON_PATH"terminal_without_alpha.bmp", NULL);
}

void	exit_button_init(t_buymenu *buymenu)
{
	t_xywh	c;

	c = new_xywh(1237, 944, 1300 - 1237, 1007 - 944);
	buymenu->exit_button = bui_new_element(buymenu->menu, NULL, c);
	bui_set_element_image_from_path(buymenu->exit_button, ELEMENT_ALL,
		ICON_PATH"exit_button.png", NULL);
	bui_set_element_image_from_path(buymenu->exit_button, ELEMENT_HOVER,
		ICON_PATH"exit_button_hover.png", NULL);
}

void	currency_init(t_buymenu *buymenu)
{
	t_xywh	c;

	c = new_xywh(481, 230, 764 - 481, 295 - 230);
	buymenu->currency = bui_new_element(buymenu->menu, "Dosh", c);
	bui_set_element_flags(buymenu->currency,
		BUI_ELEMENT_DONT_UPDATE_STATE | BUI_ELEMENT_CLEAR);
	bui_set_element_color(buymenu->currency, 0x00);
	buymenu->currency->text_x = c.w / 16;
	bui_center_element_text_y(buymenu->currency);
	bui_set_element_text_font(buymenu->currency,
		TTF_PATH"ShareTechMono-Regular.ttf", 18, 0x72e26c);
	bui_element_set_text_style(buymenu->currency, TTF_STYLE_BOLD);
}

t_buymenu	*buymenu_init(void)
{
	t_buymenu	*buymenu;

	buymenu = ft_memalloc(sizeof(t_buymenu));
	buymenu->active_gun = NULL;
	buymenu->all_guns = NULL;
	return (buymenu);
}

void	buymenu_quit(t_buymenu *buymenu)
{
	ft_lstdel(&buymenu->all_guns, &dummy_free_er);
	ft_memdel((void *)&buymenu);
}
