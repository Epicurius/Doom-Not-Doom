/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bm_event.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 17:40:02 by nneronin          #+#    #+#             */
/*   Updated: 2022/01/14 15:00:32 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buymenu.h"

void	check_which(t_buymenu *buymenu, int wep_type)
{
	if (buymenu->active_weapon_button == buymenu->weapon_button[wep_type])
	{
		if (!buymenu->inv->weapon[wep_type].own)
			buymenu->active_weapon_button = NULL;
		else
		{
			buymenu->wep_type = wep_type;
			buymenu->weapon_button[wep_type]->event = 1;
		}
	}
}

void	event_weapon_buy(t_buymenu *buymenu)
{
	ui_list_radio_event(buymenu->weapon_buttons,
		&buymenu->active_weapon_button);
	check_which(buymenu, WEAPON_SHOTGUN);
	check_which(buymenu, WEAPON_GUN);
	check_which(buymenu, WEAPON_KAR);
	check_which(buymenu, WEAPON_LAUNCHER);
	check_which(buymenu, WEAPON_MINIGUN);
	attempt_buying_weapon(buymenu, WEAPON_SHOTGUN);
	attempt_buying_weapon(buymenu, WEAPON_GUN);
	attempt_buying_weapon(buymenu, WEAPON_KAR);
	attempt_buying_weapon(buymenu, WEAPON_LAUNCHER);
	attempt_buying_weapon(buymenu, WEAPON_MINIGUN);
}

void	event_weapon_stat_buy(t_buymenu *buymenu)
{
	disable_not_affordable_weapon_upgrade_buttons(buymenu);
	if (buymenu->damage_price_button->state == UI_STATE_CLICK)
		attempt_buying_stat(&buymenu->inv->dosh,
			buymenu->inv->weapon[buymenu->wep_type].damage_price,
			&buymenu->inv->weapon[buymenu->wep_type].damage,
			buymenu->inv->weapon[buymenu->wep_type].damage_increase);
	else if (buymenu->firerate_price_button->state == UI_STATE_CLICK)
		attempt_buying_stat(&buymenu->inv->dosh,
			buymenu->inv->weapon[buymenu->wep_type].firerate_price,
			&buymenu->inv->weapon[buymenu->wep_type].frame_rate,
			buymenu->inv->weapon[buymenu->wep_type].firerate_increase);
	else if (buymenu->ammo_price_button->state == UI_STATE_CLICK)
		attempt_buying_stat(&buymenu->inv->dosh,
			buymenu->inv->weapon[buymenu->wep_type].ammo_price,
			&buymenu->inv->weapon[buymenu->wep_type].cur_ammo,
			buymenu->inv->weapon[buymenu->wep_type].ammo_increase);
	else if (buymenu->max_ammo_price_button->state == UI_STATE_CLICK)
		attempt_buying_stat(&buymenu->inv->dosh,
			buymenu->inv->weapon[buymenu->wep_type].max_ammo_price,
			&buymenu->inv->weapon[buymenu->wep_type].max_ammo,
			buymenu->inv->weapon[buymenu->wep_type].max_ammo_increase);
}

void	event_player_stat_buy(t_buymenu *buymenu)
{
	disable_not_affordable_player_upgrade_buttons(buymenu);
	if (buymenu->speed_price_button->state == UI_STATE_CLICK)
		attempt_buying_stat_f(&buymenu->inv->dosh,
			buymenu->inv->speed_price,
			buymenu->inv->speed, 1);
	else if (buymenu->jump_price_button->state == UI_STATE_CLICK)
		attempt_buying_stat_f(&buymenu->inv->dosh,
			buymenu->inv->jump_price,
			buymenu->inv->jump, 1);
	else if (buymenu->armor_price_button->state == UI_STATE_CLICK)
		attempt_buying_stat(&buymenu->inv->dosh,
			buymenu->inv->armour_price,
			buymenu->inv->armour, 10);
	else if (buymenu->max_armor_price_button->state == UI_STATE_CLICK)
		attempt_buying_stat(&buymenu->inv->dosh,
			buymenu->inv->max_armour_price,
			&buymenu->inv->max_armour, 1);
}

void	user_events(t_buymenu *buymenu, SDL_Event e)
{
	event_weapon_buy(buymenu);
	update_weapon_stats(buymenu);
	event_weapon_stat_buy(buymenu);
	update_player_stats(buymenu);
	event_player_stat_buy(buymenu);
	update_currency(buymenu);
	if (e.key.keysym.scancode == SDL_SCANCODE_ESCAPE
		|| buymenu->close_button->state == UI_STATE_CLICK)
		buymenu->run = 0;
}
