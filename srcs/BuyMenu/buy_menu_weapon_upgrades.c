/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buy_menu_weapon_upgrades.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalmi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 15:38:55 by jsalmi            #+#    #+#             */
/*   Updated: 2021/07/28 15:38:56 by jsalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buymenu.h"

void	weapon_upgrades_init(t_buymenu *buymenu)
{
	t_xywh	c;

	c = buymenu->weapon_menu->position;
	c.x = buymenu->weapon_stats->position.x;
	buymenu->weapon_upgrades = bui_new_element(buymenu->menu, NULL, c);
	buymenu->weapon_upgrades->update_state = 0;
	buymenu->weapon_upgrades->clear = 1;
	bui_set_element_color(buymenu->weapon_upgrades, 0x00000000);
	buymenu->damage_elem
		= new_upgrade_button(buymenu->weapon_upgrades, "+1 Damage", 0);
	buymenu->firerate_elem
		= new_upgrade_button(buymenu->weapon_upgrades, "+1 Firerate", 1);
	buymenu->ammo_elem
		= new_upgrade_button(buymenu->weapon_upgrades, "+10 Ammo", 2);
	buymenu->max_ammo_elem
		= new_upgrade_button(buymenu->weapon_upgrades, "+1 Max Ammo", 3);
}

void	update_weapon_upgrade_buttons(t_buymenu *buymenu, t_inv *inv, int a)
{
	char	*aaa;
	int		font_style;

	font_style = TTF_STYLE_BOLD | TTF_STYLE_STRIKETHROUGH;
	aaa = ft_sprintf("+%d DAMAGE $%d", inv->weapon[a].damage_increase,
			inv->weapon[a].damage_price);
	buymenu->damage_elem->font_style = font_style;
	bui_set_element_text(buymenu->damage_elem, aaa);
	ft_strdel(&aaa);
	aaa = ft_sprintf("%d FIRERATE $%d", inv->weapon[a].firerate_increase,
			inv->weapon[a].firerate_price);
	buymenu->firerate_elem->font_style = font_style;
	bui_set_element_text(buymenu->firerate_elem, aaa);
	ft_strdel(&aaa);
	aaa = ft_sprintf("+%d AMMO $%d", inv->weapon[a].ammo_increase,
			inv->weapon[a].ammo_price);
	buymenu->ammo_elem->font_style = font_style;
	bui_set_element_text(buymenu->ammo_elem, aaa);
	ft_strdel(&aaa);
	aaa = ft_sprintf("+%d MAX AMMO $%d", inv->weapon[a].max_ammo_increase,
			inv->weapon[a].max_ammo_price);
	buymenu->max_ammo_elem->font_style = font_style;
	bui_set_element_text(buymenu->max_ammo_elem, aaa);
	ft_strdel(&aaa);
}

void	buy_weapon_events1(t_buymenu *buymenu, t_inv *inv, int a)
{
	if (inv->dosh >= inv->weapon[a].damage_price)
	{
		buymenu->damage_elem->update_state = 1;
		bui_element_set_text_style(buymenu->damage_elem, TTF_STYLE_BOLD);
		if (bui_button(buymenu->damage_elem))
		{
			inv->weapon[a].damage += inv->weapon[a].damage_increase;
			inv->dosh -= inv->weapon[a].damage_price;
		}
	}
	if (inv->dosh >= inv->weapon[a].firerate_price)
	{
		buymenu->firerate_elem->update_state = 1;
		bui_element_set_text_style(buymenu->firerate_elem, TTF_STYLE_BOLD);
		if (bui_button(buymenu->firerate_elem))
		{
			inv->weapon[a].frame_rate += inv->weapon[a].firerate_increase;
			inv->dosh -= inv->weapon[a].firerate_price;
		}
	}
}

void	buy_weapon_events2(t_buymenu *buymenu, t_inv *inv, int a)
{
	if (inv->dosh >= inv->weapon[a].ammo_price
		&& inv->weapon[a].cur_ammo < inv->weapon[a].max_ammo)
	{
		buymenu->ammo_elem->update_state = 1;
		bui_element_set_text_style(buymenu->ammo_elem, TTF_STYLE_BOLD);
		if (bui_button(buymenu->ammo_elem))
		{
			inv->weapon[a].cur_ammo += ft_min(inv->weapon[a].ammo_increase,
					inv->weapon[a].max_ammo - inv->weapon[a].cur_ammo);
			inv->dosh -= inv->weapon[a].ammo_price;
		}
	}
	if (inv->dosh >= inv->weapon[a].max_ammo_price)
	{
		buymenu->max_ammo_elem->update_state = 1;
		bui_element_set_text_style(buymenu->max_ammo_elem, TTF_STYLE_BOLD);
		if (bui_button(buymenu->max_ammo_elem))
		{
			inv->weapon[a].max_ammo += inv->weapon[a].max_ammo_increase;
			inv->dosh -= inv->weapon[a].max_ammo_price;
		}
	}
}

void	weapon_upgrading_events(t_buymenu *buymenu, t_inv *inv)
{
	int	a;

	buymenu->damage_elem->update_state = 0;
	buymenu->firerate_elem->update_state = 0;
	buymenu->ammo_elem->update_state = 0;
	buymenu->max_ammo_elem->update_state = 0;
	if (buymenu->active_gun)
	{
		a = get_active_gun(buymenu);
		update_weapon_upgrade_buttons(buymenu, inv, a);
		buy_weapon_events1(buymenu, inv, a);
		buy_weapon_events2(buymenu, inv, a);
	}
}
