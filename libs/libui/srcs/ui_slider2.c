/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_slider2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalmi <jsalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 19:24:33 by jsalmi            #+#    #+#             */
/*   Updated: 2021/12/10 19:24:33 by jsalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

int	ui_slider_value_get(t_ui_element *elem)
{
	t_ui_slider	*slider;

	slider = elem->element;
	return (ui_get_slider_value(
			slider->min_value, slider->max_value,
			slider->button.pos.x, elem->pos.w - slider->button.pos.w));
}

void	ui_slider_value_set(t_ui_element *elem, int value)
{
	t_ui_slider	*slider;

	slider = elem->element;
	slider->value = value;
	slider->button.pos.x = ft_clamp(
			ui_set_slider_value(
				value, slider->min_value, slider->max_value,
				elem->pos.w - slider->button.pos.w),
			0, elem->pos.w - slider->button.pos.w);
	slider->update = 1;
}

int	ui_get_slider_value(int min, int max, int pos_x, int w)
{
	float	pixels_per_value;
	int		total_values;
	int		nth_value;
	int		curr_value;

	total_values = abs(max - min);
	pixels_per_value = (float)total_values / (float)w;
	nth_value = pixels_per_value * (float)pos_x;
	curr_value = min + nth_value;
	return (ft_clamp(curr_value, min, max));
}

int	ui_set_slider_value(int value, int min, int max, int w)
{
	return (ft_clamp(((float)w / (float)(abs(max - min)))
		* (float)(abs(min - value)), 0, w));
}

int	ui_slider_updated(t_ui_element *elem)
{
	return (ui_slider_get_slider(elem)->update);
}
