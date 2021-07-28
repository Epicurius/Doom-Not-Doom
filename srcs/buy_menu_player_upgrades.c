/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buy_menu_player_upgrades.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalmi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 15:38:49 by jsalmi            #+#    #+#             */
/*   Updated: 2021/07/28 15:38:50 by jsalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buymenu.h"

void	update_player_upgrade_buttons(t_buymenu *buymenu, t_inv *inv)
{
	char	*ooo;

	ooo = ft_sprintf("+10 ARMOR $%d", inv->armour_price);
	bui_set_element_text(buymenu->armor_elem, ooo);
	ft_strdel(&ooo);
	ooo = ft_sprintf("+1 MAX ARMOR $%d", inv->max_armour_price);
	bui_set_element_text(buymenu->max_armor_elem, ooo);
	ft_strdel(&ooo);
	ooo = ft_sprintf("+1 SPEED $%d", inv->speed_price);
	bui_set_element_text(buymenu->speed_elem, ooo);
	ft_strdel(&ooo);
	ooo = ft_sprintf("+1 JUMP $%d", inv->jump_price);
	bui_set_element_text(buymenu->jump_elem, ooo);
	ft_strdel(&ooo);
}

void	buy_player_upgrades_events1(t_buymenu *buymenu, t_inv *inv)
{
	if (inv->dosh >= inv->armour_price
		&& *inv->armour < inv->max_armour)
	{
		buymenu->armor_elem->update_state = 1;
		bui_element_set_text_style(buymenu->armor_elem, TTF_STYLE_BOLD);
		if (bui_button(buymenu->armor_elem))
		{
			*inv->armour += ft_min(10, inv->max_armour - *inv->armour);
			inv->dosh -= inv->armour_price;
		}
	}
	if (inv->dosh >= inv->max_armour_price)
	{
		buymenu->max_armor_elem->update_state = 1;
		bui_element_set_text_style(buymenu->max_armor_elem, TTF_STYLE_BOLD);
		if (bui_button(buymenu->max_armor_elem))
		{
			inv->max_armour += 1;
			inv->dosh -= inv->max_armour_price;
		}
	}
}

void	buy_player_upgrades_events2(t_buymenu *buymenu, t_inv *inv)
{
	if (inv->dosh >= inv->speed_price)
	{
		buymenu->speed_elem->update_state = 1;
		bui_element_set_text_style(buymenu->speed_elem, TTF_STYLE_BOLD);
		if (bui_button(buymenu->speed_elem))
		{
			*inv->speed += 1;
			inv->dosh -= inv->speed_price;
		}
	}
	if (inv->dosh >= inv->jump_price)
	{
		buymenu->jump_elem->update_state = 1;
		bui_element_set_text_style(buymenu->jump_elem, TTF_STYLE_BOLD);
		if (bui_button(buymenu->jump_elem))
		{
			*inv->jump += 1;
			inv->dosh -= inv->jump_price;
		}
	}
}

void	player_upgrading_events(t_buymenu *buymenu, t_inv *inv)
{
	int	font_style;

	font_style = TTF_STYLE_BOLD | TTF_STYLE_STRIKETHROUGH;
	update_player_upgrade_buttons(buymenu, inv);
	buymenu->armor_elem->update_state = 0;
	buymenu->max_armor_elem->update_state = 0;
	buymenu->speed_elem->update_state = 0;
	buymenu->jump_elem->update_state = 0;
	bui_element_set_text_style(buymenu->armor_elem, font_style);
	bui_element_set_text_style(buymenu->max_armor_elem, font_style);
	bui_element_set_text_style(buymenu->speed_elem, font_style);
	bui_element_set_text_style(buymenu->jump_elem, font_style);
	buy_player_upgrades_events1(buymenu, inv);
	buy_player_upgrades_events2(buymenu, inv);
}
