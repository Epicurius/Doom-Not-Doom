/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buy_menu_player_stats.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalmi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 15:38:47 by jsalmi            #+#    #+#             */
/*   Updated: 2021/07/28 15:38:48 by jsalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buymenu.h"

void	player_stats_stats_init(t_buymenu *buymenu, t_xywh rc)
{
	t_xywh	c;

	buymenu->speed_stat = new_stat(buymenu->player_stats, "Speed", rc);
	c = new_xywh(rc.x, rc.y + rc.h, rc.w, rc.h);
	buymenu->jump_stat = new_stat(buymenu->player_stats, "Jump", c);
	c = new_xywh(rc.x + rc.w, rc.y, rc.w, rc.h);
	buymenu->armour_stat = new_stat(buymenu->player_stats, "Armor", c);
	c = new_xywh(rc.x + rc.w, rc.y + rc.h, rc.w, rc.h);
	buymenu->max_armour_stat = new_stat(buymenu->player_stats, "Max Armor", c);
}

void	player_stats_init(t_buymenu *buymenu)
{
	t_xywh	c;
	t_xywh	rc;

	c = buymenu->currency->position;
	c.x = buymenu->weapon_stats->position.x + buymenu->weapon_stats->position.w
		+ (buymenu->weapon_stats->position.x - (buymenu->currency->position.x
				+ buymenu->currency->position.w));
	buymenu->player_stats = bui_new_element(buymenu->menu, NULL, c);
	bui_set_element_flags(buymenu->player_stats,
		BUI_ELEMENT_DONT_UPDATE_STATE | BUI_ELEMENT_CLEAR);
	bui_set_element_color(buymenu->player_stats, 0x00);
	buymenu->player_stats->text_x = 40;
	buymenu->player_stats->text_y = 20;
	bui_set_element_text_font(buymenu->player_stats,
		TTF_PATH"DroidSans.ttf", 20, 0xff199515);
	rc = new_xywh(0, buymenu->player_stats->position.h / 7,
			buymenu->player_stats->position.w / 2,
			buymenu->player_stats->position.h / 3);
	player_stats_stats_init(buymenu, rc);
}

void	player_stat_events(t_buymenu *buymenu, t_inv *inv)
{
	char	*lll;

	lll = ft_sprintf("SPEED %d", (int)*inv->speed);
	bui_set_element_text(buymenu->speed_stat, lll);
	ft_strdel(&lll);
	lll = ft_sprintf("JUMP %d", (int)*inv->jump);
	bui_set_element_text(buymenu->jump_stat, lll);
	ft_strdel(&lll);
	lll = ft_sprintf("ARMOR %d", *inv->armour);
	bui_set_element_text(buymenu->armour_stat, lll);
	ft_strdel(&lll);
	lll = ft_sprintf("MAXARMOR %d", inv->max_armour);
	bui_set_element_text(buymenu->max_armour_stat, lll);
	ft_strdel(&lll);
}
