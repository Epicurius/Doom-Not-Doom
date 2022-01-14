/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bm_update1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 17:25:48 by nneronin          #+#    #+#             */
/*   Updated: 2022/01/14 15:00:32 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buymenu.h"

void	update_currency(t_buymenu *buymenu)
{
	char	temp_str[20];

	ui_label_set_text(buymenu->currency_amount_label,
		ft_b_itoa(buymenu->inv->dosh, temp_str));
}

void	update_amount_label(t_buymenu *buymenu, int wep_type)
{
	char	temp_str[20];

	ui_label_set_text(buymenu->ammo_stat_amount_label,
		ft_b_itoa(buymenu->inv->weapon[wep_type].cur_ammo, temp_str));
	ui_label_set_text(buymenu->max_ammo_stat_amount_label,
		ft_b_itoa(buymenu->inv->weapon[wep_type].max_ammo, temp_str));
	ui_label_set_text(buymenu->firerate_stat_amount_label,
		ft_b_itoa(buymenu->inv->weapon[wep_type].frame_rate, temp_str));
	ui_label_set_text(buymenu->damage_stat_amount_label,
		ft_b_itoa(buymenu->inv->weapon[wep_type].damage, temp_str));
}

void	update_upgrade_labels(t_buymenu *buymenu, int wep_type)
{
	char	str[20];

	str[0] = '+';
	ui_label_set_text(buymenu->damage_amount_label,
		&ft_b_itoa(buymenu->inv->weapon[wep_type].damage_increase,
			&str[1])[-1]);
	ui_label_set_text(buymenu->ammo_amount_label,
		&ft_b_itoa(buymenu->inv->weapon[wep_type].ammo_increase, &str[1])[-1]);
	ui_label_set_text(buymenu->max_ammo_amount_label,
		&ft_b_itoa(buymenu->inv->weapon[wep_type].max_ammo_increase,
			&str[1])[-1]);
	ui_label_set_text(buymenu->firerate_amount_label,
		ft_b_itoa(buymenu->inv->weapon[wep_type].firerate_increase, str));
	str[0] = '$';
	ui_button_set_text(buymenu->damage_price_button,
		&ft_b_itoa(buymenu->inv->weapon[wep_type].damage_price, &str[1])[-1]);
	ui_button_set_text(buymenu->ammo_price_button,
		&ft_b_itoa(buymenu->inv->weapon[wep_type].ammo_price, &str[1])[-1]);
	ui_button_set_text(buymenu->max_ammo_price_button,
		&ft_b_itoa(buymenu->inv->weapon[wep_type].max_ammo_price, &str[1])[-1]);
	ui_button_set_text(buymenu->firerate_price_button,
		&ft_b_itoa(buymenu->inv->weapon[wep_type].firerate_price, &str[1])[-1]);
}

/*
 * Both the stats showing in the top mid menu,
 * and the prices and increases on the bot mid menu;
*/
void	update_weapon_stats(t_buymenu *buymenu)
{
	update_amount_label(buymenu, buymenu->wep_type);
	update_upgrade_labels(buymenu, buymenu->wep_type);
}

void	update_player_stat_amount_labels(t_buymenu *buymenu)
{
	char	temp_str[20];

	ui_label_set_text(buymenu->jump_stat_amount_label,
		ft_b_itoa(*buymenu->inv->jump, temp_str));
	ui_label_set_text(buymenu->speed_stat_amount_label,
		ft_b_itoa(*buymenu->inv->speed, temp_str));
	ui_label_set_text(buymenu->armor_stat_amount_label,
		ft_b_itoa(*buymenu->inv->armour, temp_str));
	ui_label_set_text(buymenu->max_armor_stat_amount_label,
		ft_b_itoa(buymenu->inv->max_armour, temp_str));
}
