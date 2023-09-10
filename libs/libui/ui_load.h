/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Jony Salmi <jony.salmi@gmail.com>
 */

#ifndef UI_LOAD_H
# define UI_LOAD_H
# include "libui.h"

/*
 * Fun fact: you can only have flexible array in the end of a struct.
 * 	which actually makes sense if you think about it.
*/
typedef struct s_ui_acceptable
{
	char			*name;
	int				type;
	void			(*freer)(void *elem, size_t size);
	void			(*maker)(t_ui_window *win, t_ui_element *elem);
	int				(*renderer)(t_ui_element	*elem);
	void			(*eventer)(t_ui_element *elem, SDL_Event e);
	void			(*edit)(t_ui_element *elem, t_ui_recipe *recipe);
	void			(*printer)(t_ui_element	*elem);
	t_ui_element	*(*getter)(t_ui_element *elem, int ui_element_type);
}				t_ui_acceptable;

static const t_ui_acceptable	g_acceptable[] =
{
	{
		.name = "Element",
		.type = UI_TYPE_ELEMENT,
		.freer = NULL,
		.maker = NULL,
		.renderer = &ui_element_render,
		.eventer = &ui_element_event,
		.edit = NULL,
		.printer = NULL,
		.getter = NULL
	},
	{
		.name = "Label",
		.type = UI_TYPE_LABEL,
		.freer = &ui_label_free,
		.maker = &ui_label_new,
		.renderer = &ui_label_render,
		.eventer = &ui_label_event,
		.edit = &ui_label_edit,
		.printer = &ui_label_print,
		.getter = NULL
	},
	{
		.name = "Button",
		.type = UI_TYPE_BUTTON,
		.freer = &ui_button_free,
		.maker = &ui_button_new,
		.renderer = &ui_button_render,
		.eventer = &ui_button_event,
		.edit = &ui_button_edit,
		.printer = &ui_button_print,
		.getter = NULL
	},
	{
		.name = "Menu",
		.type = UI_TYPE_MENU,
		.freer = &ui_menu_free,
		.maker = &ui_menu_new,
		.renderer = &ui_menu_render,
		.eventer = &ui_menu_event,
		.edit = &ui_menu_edit,
		.printer = NULL,
		.getter = NULL
	},
	{
		.name = "Dropdown",
		.type = UI_TYPE_DROPDOWN,
		.freer = &ui_dropdown_free,
		.maker = &ui_dropdown_new,
		.renderer = &ui_dropdown_render,
		.eventer = &ui_dropdown_event,
		.edit = &ui_dropdown_edit,
		.printer = NULL,
		.getter = &ui_dropdown_get
	},
	{
		.name = "Input",
		.type = UI_TYPE_INPUT,
		.freer = &ui_input_free,
		.maker = &ui_input_new,
		.renderer = &ui_input_render,
		.eventer = &ui_input_event,
		.edit = &ui_input_edit,
		.printer = &ui_input_print,
		.getter = NULL
	},
	{
		.name = "Slider",
		.type = UI_TYPE_SLIDER,
		.freer = &ui_slider_free,
		.maker = &ui_slider_new,
		.renderer = &ui_slider_render,
		.eventer = &ui_slider_event,
		.edit = &ui_slider_edit,
		.printer = NULL,
		.getter = &ui_slider_get
	},
	{
		.name = "Checkbox",
		.type = UI_TYPE_CHECKBOX,
		.freer = &ui_checkbox_free,
		.maker = &ui_checkbox_new,
		.renderer = &ui_checkbox_render,
		.eventer = &ui_checkbox_event,
		.edit = NULL,
		.printer = NULL,
		.getter = NULL
	},
	{
		.name = "Radio",
		.type = UI_TYPE_RADIO,
		.freer = &ui_radio_free,
		.maker = &ui_radio_new,
		.renderer = &ui_radio_render,
		.eventer = &ui_radio_event,
		.edit = NULL,
		.printer = NULL,
		.getter = NULL
	},
	{
		.name = "Scrollbar",
		.type = UI_TYPE_SCROLLBAR,
		.freer = &ui_scrollbar_free,
		.maker = &ui_scrollbar_new,
		.renderer = &ui_scrollbar_render,
		.eventer = &ui_scrollbar_event,
		.edit = &ui_scrollbar_edit,
		.printer = NULL,
		.getter = &ui_scrollbar_get
	},
	{
		.name = "Window",
		.type = UI_TYPE_WINDOW,
		.freer = NULL,
		.maker = NULL,
		.renderer = NULL,
		.eventer = NULL,
		.edit = NULL,
		.printer = NULL,
		.getter = NULL
	}
};

#endif
