/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buy_menu_player.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalmi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 15:38:44 by jsalmi            #+#    #+#             */
/*   Updated: 2021/07/28 15:38:46 by jsalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buymenu.h"

void	player_menu_elem_init(t_buymenu *buymenu)
{
	buymenu->armor_elem
		= new_upgrade_button(buymenu->player_menu, "+10 Armor", 0);
	buymenu->max_armor_elem
		= new_upgrade_button(buymenu->player_menu, "+1 Max Armor", 1);
	buymenu->speed_elem
		= new_upgrade_button(buymenu->player_menu, "+1 Speed", 2);
	buymenu->jump_elem
		= new_upgrade_button(buymenu->player_menu, "+1 Jump", 3);
}

void	player_menu_init(t_buymenu *buymenu)
{
	t_xywh	c;

	c = buymenu->weapon_menu->position;
	c.x = buymenu->player_stats->position.x;
	buymenu->player_menu = bui_new_element(buymenu->menu, NULL, c);
	buymenu->player_menu->update_state = 0;
	buymenu->player_menu->clear = 1;
	bui_set_element_flags(buymenu->player_menu, BUI_ELEMENT_DONT_UPDATE_STATE);
	bui_set_element_color(buymenu->player_menu, 0x00000000);
	player_menu_elem_init(buymenu);
}
