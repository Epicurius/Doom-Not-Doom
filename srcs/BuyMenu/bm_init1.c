/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bm_init1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 17:22:02 by nneronin          #+#    #+#             */
/*   Updated: 2021/12/10 17:22:39 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buymenu.h"

void	weapon_buy_init(t_buymenu *buymenu)
{
	char	str[20];

	buymenu->weapon_buy_button[WEAPON_SHOTGUN]
		= ui_layout_get_element(&buymenu->layout, "shotgun_buy_button");
	buymenu->weapon_buy_button[WEAPON_GUN]
		= ui_layout_get_element(&buymenu->layout, "glock_buy_button");
	buymenu->weapon_buy_button[WEAPON_KAR]
		= ui_layout_get_element(&buymenu->layout, "kar98_buy_button");
	buymenu->weapon_buy_button[WEAPON_LAUNCHER]
		= ui_layout_get_element(&buymenu->layout, "launcher_buy_button");
	buymenu->weapon_buy_button[WEAPON_MINIGUN]
		= ui_layout_get_element(&buymenu->layout, "minigun_buy_button");
	ft_strcpy(str, "BUY $");
	ui_button_set_text(buymenu->weapon_buy_button[WEAPON_SHOTGUN],
		&ft_b_itoa(buymenu->inv->weapon[WEAPON_SHOTGUN].price, &str[5])[-5]);
	ui_button_set_text(buymenu->weapon_buy_button[WEAPON_GUN],
		&ft_b_itoa(buymenu->inv->weapon[WEAPON_GUN].price, &str[5])[-5]);
	ui_button_set_text(buymenu->weapon_buy_button[WEAPON_KAR],
		&ft_b_itoa(buymenu->inv->weapon[WEAPON_KAR].price, &str[5])[-5]);
	ui_button_set_text(buymenu->weapon_buy_button[WEAPON_LAUNCHER],
		&ft_b_itoa(buymenu->inv->weapon[WEAPON_LAUNCHER].price, &str[5])[-5]);
	ui_button_set_text(buymenu->weapon_buy_button[WEAPON_MINIGUN],
		&ft_b_itoa(buymenu->inv->weapon[WEAPON_MINIGUN].price, &str[5])[-5]);
}

void	weapon_menu_init(t_buymenu *buymenu)
{
	buymenu->weapon_button[WEAPON_SHOTGUN]
		= ui_layout_get_element(&buymenu->layout, "shotgun_button");
	buymenu->weapon_button[WEAPON_GUN]
		= ui_layout_get_element(&buymenu->layout, "glock_button");
	buymenu->weapon_button[WEAPON_KAR]
		= ui_layout_get_element(&buymenu->layout, "kar98_button");
	buymenu->weapon_button[WEAPON_LAUNCHER]
		= ui_layout_get_element(&buymenu->layout, "launcher_button");
	buymenu->weapon_button[WEAPON_MINIGUN]
		= ui_layout_get_element(&buymenu->layout, "minigun_button");
	buymenu->active_weapon_button = buymenu->weapon_button[WEAPON_SHOTGUN];
	add_to_list(&buymenu->weapon_buttons,
		buymenu->weapon_button[WEAPON_SHOTGUN], sizeof(t_ui_element));
	add_to_list(&buymenu->weapon_buttons,
		buymenu->weapon_button[WEAPON_GUN], sizeof(t_ui_element));
	add_to_list(&buymenu->weapon_buttons,
		buymenu->weapon_button[WEAPON_KAR], sizeof(t_ui_element));
	add_to_list(&buymenu->weapon_buttons,
		buymenu->weapon_button[WEAPON_LAUNCHER], sizeof(t_ui_element));
	add_to_list(&buymenu->weapon_buttons,
		buymenu->weapon_button[WEAPON_MINIGUN], sizeof(t_ui_element));
	weapon_buy_init(buymenu);
}

void	weapon_upgrade_init(t_buymenu *buymenu)
{
	buymenu->damage_amount_label
		= ui_layout_get_element(&buymenu->layout, "damage_amount_label");
	buymenu->damage_price_button
		= ui_layout_get_element(&buymenu->layout, "damage_price_button");
	buymenu->firerate_amount_label
		= ui_layout_get_element(&buymenu->layout, "firerate_amount_label");
	buymenu->firerate_price_button
		= ui_layout_get_element(&buymenu->layout, "firerate_price_button");
	buymenu->ammo_amount_label
		= ui_layout_get_element(&buymenu->layout, "ammo_amount_label");
	buymenu->ammo_price_button
		= ui_layout_get_element(&buymenu->layout, "ammo_price_button");
	buymenu->max_ammo_amount_label
		= ui_layout_get_element(&buymenu->layout, "max_ammo_amount_label");
	buymenu->max_ammo_price_button
		= ui_layout_get_element(&buymenu->layout, "max_ammo_price_button");
}

void	player_upgrade_init(t_buymenu *buymenu)
{
	buymenu->speed_amount_label
		= ui_layout_get_element(&buymenu->layout, "speed_amount_label");
	buymenu->speed_price_button
		= ui_layout_get_element(&buymenu->layout, "speed_price_button");
	buymenu->jump_amount_label
		= ui_layout_get_element(&buymenu->layout, "jump_amount_label");
	buymenu->jump_price_button
		= ui_layout_get_element(&buymenu->layout, "jump_price_button");
	buymenu->armor_amount_label
		= ui_layout_get_element(&buymenu->layout, "armor_amount_label");
	buymenu->armor_price_button
		= ui_layout_get_element(&buymenu->layout, "armor_price_button");
	buymenu->max_armor_amount_label
		= ui_layout_get_element(&buymenu->layout, "max_armor_amount_label");
	buymenu->max_armor_price_button
		= ui_layout_get_element(&buymenu->layout, "max_armor_price_button");
}
