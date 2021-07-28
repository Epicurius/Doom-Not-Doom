/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buy_menu_weapon_stats.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalmi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 15:38:53 by jsalmi            #+#    #+#             */
/*   Updated: 2021/07/28 15:38:54 by jsalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buymenu.h"

void	weapon_stats_stats_init(t_buymenu *buymenu, t_xywh r_c)
{
	t_xywh	c;

	buymenu->ammo_stat = new_stat(buymenu->weapon_stats, "Ammo", r_c);
	c = new_xywh(r_c.x, r_c.y + r_c.h, r_c.w, r_c.h);
	buymenu->max_ammo_stat = new_stat(buymenu->weapon_stats, "Max Ammo", c);
	c = new_xywh(r_c.x + r_c.w, r_c.y + r_c.h, r_c.w, r_c.h);
	buymenu->damage_stat = new_stat(buymenu->weapon_stats, "Damage", c);
	c = new_xywh(r_c.x + r_c.w, r_c.y, r_c.w, r_c.h);
	buymenu->firerate_stat = new_stat(buymenu->weapon_stats, "Firerate", c);
}

void	weapon_stats_init(t_buymenu *buymenu)
{
	t_xywh	r_c;
	t_xywh	c;

	c = buymenu->currency->position;
	c.x = 824;
	buymenu->weapon_stats = bui_new_element(buymenu->menu, NULL, c);
	bui_set_element_flags(buymenu->weapon_stats,
		BUI_ELEMENT_DONT_UPDATE_STATE | BUI_ELEMENT_CLEAR);
	bui_set_element_color(buymenu->weapon_stats, 0x00);
	r_c = new_xywh(0, buymenu->weapon_stats->position.h / 7,
			buymenu->weapon_stats->position.w / 2,
			buymenu->weapon_stats->position.h / 3);
	weapon_stats_stats_init(buymenu, r_c);
}

void	weapon_stat_events(t_buymenu *buymenu, t_inv *inv)
{
	int		i;
	char	*ffa;

	if (buymenu->active_gun)
	{
		i = 0;
		while (i < WEAPON_AMOUNT)
		{
			if (buymenu->active_gun == buymenu->gun_elem[i])
				break ;
			i++;
		}
		ffa = ft_sprintf("DAMAGE %d", inv->weapon[i].damage);
		bui_set_element_text(buymenu->damage_stat, ffa);
		ft_strdel(&ffa);
		ffa = ft_sprintf("AMMO %d", inv->weapon[i].cur_ammo);
		bui_set_element_text(buymenu->ammo_stat, ffa);
		ft_strdel(&ffa);
		ffa = ft_sprintf("MAX AMMO %d", inv->weapon[i].max_ammo);
		bui_set_element_text(buymenu->max_ammo_stat, ffa);
		ft_strdel(&ffa);
		ffa = ft_sprintf("FIRERATE %d", inv->weapon[i].frame_rate);
		bui_set_element_text(buymenu->firerate_stat, ffa);
		ft_strdel(&ffa);
	}
}
