/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bm_init2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 17:22:48 by nneronin          #+#    #+#             */
/*   Updated: 2021/12/18 10:10:20 by jsalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buymenu.h"

void	weapon_stat_init(t_buymenu *buymenu)
{
	buymenu->ammo_stat_amount_label
		= ui_layout_get_element(&buymenu->layout, "ammo_stat_amount_label");
	buymenu->max_ammo_stat_amount_label
		= ui_layout_get_element(&buymenu->layout, "max_ammo_stat_amount_label");
	buymenu->firerate_stat_amount_label
		= ui_layout_get_element(&buymenu->layout, "firerate_stat_amount_label");
	buymenu->damage_stat_amount_label
		= ui_layout_get_element(&buymenu->layout, "damage_stat_amount_label");
}

void	player_stat_init(t_buymenu *buymenu)
{
	buymenu->speed_stat_amount_label
		= ui_layout_get_element(&buymenu->layout, "speed_stat_amount_label");
	buymenu->jump_stat_amount_label
		= ui_layout_get_element(&buymenu->layout, "jump_stat_amount_label");
	buymenu->armor_stat_amount_label
		= ui_layout_get_element(&buymenu->layout, "armor_stat_amount_label");
	buymenu->max_armor_stat_amount_label = ui_layout_get_element(
			&buymenu->layout, "max_armor_stat_amount_label");
}

void	buymenu_init(t_buymenu *buymenu, SDL_Window *window)
{
	buymenu->run = 1;
	buymenu->main_win = ft_memalloc(sizeof(t_ui_window));
	ui_window_new_from(buymenu->main_win, window);
	ui_window_texture_pos_set(buymenu->main_win, vec2i(1920, 1080));
	ui_window_id_set(buymenu->main_win, "main_win");
	add_to_list(&buymenu->layout.windows, buymenu->main_win, UI_TYPE_WINDOW);
	ui_layout_load(&buymenu->layout, GAME_PATH, "srcs/BuyMenu/layout.ui");
	buymenu->main_win = ui_layout_get_window(&buymenu->layout, "main_win");
	buymenu->close_button
		= ui_layout_get_element(&buymenu->layout, "close_button");
	weapon_menu_init(buymenu);
	weapon_upgrade_init(buymenu);
	player_upgrade_init(buymenu);
	weapon_stat_init(buymenu);
	player_stat_init(buymenu);
	buymenu->currency_amount_label
		= ui_layout_get_element(&buymenu->layout, "currency_amount_label");
}
