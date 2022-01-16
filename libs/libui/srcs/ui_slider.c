/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_slider.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalmi <jsalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 19:24:30 by jsalmi            #+#    #+#             */
/*   Updated: 2021/12/10 19:24:30 by jsalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

void	ui_slider_new(t_ui_window *win, t_ui_element *elem)
{
	t_ui_slider	*slider;
	t_ui_button	*button;

	ui_element_new(win, elem);
	elem->element = ft_memalloc(sizeof(t_ui_slider));
	elem->element_type = UI_TYPE_SLIDER;
	slider = elem->element;
	slider->elem = elem;
	ui_button_new(win, &slider->button);
	slider->button.is_a_part_of_another = 1;
	ui_element_pos_set(&slider->button, vec4(0, 0, elem->pos.h, elem->pos.h));
	slider->button.colors[UI_STATE_DEFAULT] = UI_COLOR_ORANGEISH;
	slider->button.colors[UI_STATE_HOVER] = UI_COLOR_ORANGEISH_DARKER;
	slider->button.colors[UI_STATE_CLICK] = UI_COLOR_ORANGEISH_DARKEST;
	ui_element_set_parent(&slider->button, elem, UI_TYPE_ELEMENT);
	slider->min_value = 0;
	slider->max_value = 100;
	ui_slider_value_set(elem, 50);
	slider->update = 1;
}

void	ui_slider_edit(t_ui_element *elem, t_ui_recipe *recipe)
{
	t_ui_slider	*slider;
	t_ui_window	*win;
	t_ui_recipe	*button_recipe;

	win = elem->win;
	slider = elem->element;
	if (recipe->value_set[1])
		slider->min_value = recipe->value[1];
	if (recipe->value_set[2])
		slider->max_value = recipe->value[2];
	if (recipe->value_set[0])
		ui_slider_value_set(elem, recipe->value[0]);
}

void	ui_slider_event(t_ui_element *elem, SDL_Event e)
{
	t_ui_slider	*slider;
	t_ui_button	*button;

	if (!elem->show || !elem->event)
		return ;
	slider = elem->element;
	button = slider->button.element;
	if (ui_element_is_click(elem))
	{
		slider->value
			= ui_get_slider_value(slider->min_value, slider->max_value,
				(elem->win->mouse_pos.x - elem->screen_pos.x)
				- slider->button.pos.h / 2,
				elem->pos.w - slider->button.pos.w);
		slider->update = 1;
	}
}

int	ui_slider_render(t_ui_element *elem)
{
	char		temp[20];
	t_ui_slider	*slider;
	t_ui_button	*button;

	if (!ui_element_render(elem))
		return (0);
	slider = elem->element;
	button = slider->button.element;
	if (slider->update)
	{
		slider->button.pos.x = ft_clamp(ui_set_slider_value(
					slider->value, slider->min_value,
					slider->max_value, elem->pos.w - slider->button.pos.w),
				0, elem->pos.w - slider->button.pos.w);
		ft_b_itoa(slider->value, temp);
		ui_label_set_text(&button->label, temp);
		slider->update = 0;
	}
	ui_button_render(&slider->button);
	return (1);
}

void	ui_slider_free(void *elem, size_t size)
{
	t_ui_element	*element;
	t_ui_slider		*slider;

	element = elem;
	if (!element)
		return ;
	slider = element->element;
	if (!slider)
		return ;
	free(slider);
}
