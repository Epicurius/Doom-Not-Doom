/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalmi <jsalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 18:58:47 by nneronin          #+#    #+#             */
/*   Updated: 2021/12/13 12:31:20 by jsalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "launcher.h"

void	settings_menu_init(t_launcher *launcher)
{
	launcher->settings_menu
		= ui_layout_get_element(&launcher->layout, "settings_menu");
	launcher->fov_slider
		= ui_layout_get_element(&launcher->layout, "fov_slider");
	launcher->mouse_x_slider
		= ui_layout_get_element(&launcher->layout, "mouse_x_slider");
	launcher->mouse_y_slider
		= ui_layout_get_element(&launcher->layout, "mouse_y_slider");
	launcher->texture_scale_slider
		= ui_layout_get_element(&launcher->layout, "texture_scale_slider");
	launcher->developer_checkbox
		= ui_layout_get_element(&launcher->layout, "developer_checkbox");
	launcher->resolution_drop
		= ui_layout_get_element(&launcher->layout, "resolution_drop");
	ui_dropdown_activate(launcher->resolution_drop,
		ui_list_get_element_by_id(
			ui_dropdown_get_menu_element(launcher->resolution_drop)
			->children, "1920x1080_button"));
}

void	settings_events(t_launcher *launcher)
{
	char	**res;

	if (ui_slider_updated(launcher->fov_slider))
		launcher->settings.fov = ui_slider_value_get(launcher->fov_slider);
	if (ui_slider_updated(launcher->mouse_x_slider))
		launcher->settings.mouse_x
			= ui_slider_value_get(launcher->mouse_x_slider);
	if (ui_slider_updated(launcher->mouse_y_slider))
		launcher->settings.mouse_y
			= ui_slider_value_get(launcher->mouse_y_slider);
	if (ui_slider_updated(launcher->texture_scale_slider))
		launcher->settings.texture_scale
			= ui_slider_value_get(launcher->texture_scale_slider);
	launcher->settings.developer = launcher->developer_checkbox->is_toggle;
	if (ui_dropdown_exit(launcher->resolution_drop))
	{
		res = ft_strsplit(ui_button_get_text(
					ui_dropdown_active(launcher->resolution_drop)), 'x');
		launcher->settings.width = ft_atoi(res[0]);
		launcher->settings.height = ft_atoi(res[1]);
		ft_arraydel(res);
	}
}

void	settings_init(t_settings *settings)
{
	settings->fov = 75;
	settings->mouse_x = 2;
	settings->mouse_y = 2;
	settings->texture_scale = 80;
	settings->developer = 0;
	settings->width = 1920;
	settings->height = 1080;
	settings->difficulty = 2;
}

void	settings_elem_default(t_launcher *launcher)
{
	char	*res;

	ui_slider_value_set(launcher->fov_slider, launcher->settings.fov);
	ui_slider_value_set(launcher->mouse_x_slider, launcher->settings.mouse_x);
	ui_slider_value_set(launcher->mouse_y_slider, launcher->settings.mouse_y);
	ui_slider_value_set(launcher->texture_scale_slider,
		launcher->settings.texture_scale);
	launcher->developer_checkbox->is_toggle = launcher->settings.developer;
	res = ft_sprintf("%dx%d", launcher->settings.width,
			launcher->settings.height);
	ui_dropdown_activate(launcher->resolution_drop,
		ui_list_get_button_with_text(
			ui_dropdown_get_menu_element(launcher->resolution_drop)->children,
			res));
	ft_strdel(&res);
}
