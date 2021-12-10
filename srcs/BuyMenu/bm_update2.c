/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bm_update2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 17:26:35 by nneronin          #+#    #+#             */
/*   Updated: 2021/12/10 17:27:00 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "buymenu.h"

void	update_player_upgrade_amount_labels(t_buymenu *buymenu)
{
	char	str[20];

	str[0] = '+';
	ui_label_set_text(buymenu->speed_amount_label,
		&ft_b_itoa(1, &str[1])[-1]);
	ui_label_set_text(buymenu->jump_amount_label,
		&ft_b_itoa(1, &str[1])[-1]);
	ui_label_set_text(buymenu->armor_amount_label,
		&ft_b_itoa(10, &str[1])[-1]);
	ui_label_set_text(buymenu->max_armor_amount_label,
		&ft_b_itoa(1, &str[1])[-1]);
	str[0] = '$';
	ui_button_set_text(buymenu->speed_price_button,
		&ft_b_itoa(buymenu->inv->speed_price, &str[1])[-1]);
	ui_button_set_text(buymenu->jump_price_button,
		&ft_b_itoa(buymenu->inv->jump_price, &str[1])[-1]);
	ui_button_set_text(buymenu->armor_price_button,
		&ft_b_itoa(buymenu->inv->armour_price, &str[1])[-1]);
	ui_button_set_text(buymenu->max_armor_price_button,
		&ft_b_itoa(buymenu->inv->max_armour_price, &str[1])[-1]);
}

void	update_player_stats(t_buymenu *buymenu)
{
	update_player_stat_amount_labels(buymenu);
	update_player_upgrade_amount_labels(buymenu);
}