/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buy_menu_weapon.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalmi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 15:38:51 by jsalmi            #+#    #+#             */
/*   Updated: 2021/07/28 15:42:16 by jsalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buymenu.h"

void	weapon_menu_init(t_buymenu *buymenu)
{
	t_xywh	c;
	t_xywh	t;
	int		i;
	int		gap;

	c = new_xywh(buymenu->currency->position.x, buymenu->currency->position.y
			+ buymenu->currency->position.h, buymenu->currency->position.w, 0);
	c.h = 652 - c.y;
	buymenu->weapon_menu = bui_new_element(buymenu->menu, NULL, c);
	buymenu->weapon_menu->clear = 1;
	bui_set_element_flags(buymenu->weapon_menu, BUI_ELEMENT_DONT_UPDATE_STATE);
	bui_set_element_color(buymenu->weapon_menu, 0x00000000);
	i = 0;
	gap = 10;
	t = new_xywh(0, 0, buymenu->weapon_menu->position.w / 2, 50);
	while (i < WEAPON_AMOUNT)
	{
		c = new_xywh(t.x, (i) * t.h + ((i + 1) * gap) + 20, t.w, t.h);
		buymenu->gun_elem[i] = new_button(buymenu->weapon_menu,
				(char *)g_weapon_data[i], c);
		c = new_xywh(c.x + c.w, c.y, c.w, c.h);
		buymenu->gun_buy[i] = new_buy_button(buymenu->weapon_menu, c);
		i++;
	}
}

void	give_weapon(t_buymenu *buymenu, t_inv *inv, int i)
{
	buymenu->gun_elem[i]->update_state = 1;
	inv->weapon[i].own = 1;
	add_to_list(&buymenu->all_guns, buymenu->gun_elem[i], 0);
	buymenu->active_gun = buymenu->gun_elem[i];
}

void	update_weapon_button(t_buymenu *buymenu, t_inv *inv, int i)
{
	char	*fff;

	buymenu->gun_buy[i]->text_x = buymenu->gun_buy[i]->position.w / 9;
	bui_set_element_text(buymenu->gun_buy[i], "OWNED");
	if (!inv->weapon[i].own)
	{
		fff = ft_sprintf("BUY $%d", inv->weapon[i].price);
		bui_set_element_text(buymenu->gun_buy[i], fff);
		ft_strdel(&fff);
	}
	buymenu->gun_buy[i]->update_state = 0;
	buymenu->gun_buy[i]->font_style = TTF_STYLE_BOLD | TTF_STYLE_STRIKETHROUGH;
	if (!inv->weapon[i].own && inv->dosh >= inv->weapon[i].price)
	{
		buymenu->gun_buy[i]->update_state = 1;
		buymenu->gun_buy[i]->font_style = TTF_STYLE_BOLD;
		if (bui_button(buymenu->gun_buy[i]))
		{
			inv->dosh -= inv->weapon[i].price;
			give_weapon(buymenu, inv, i);
		}
	}
}

void	weapon_buying_events(t_buymenu *buymenu, t_inv *inv)
{
	char	*str;
	int		i;

	i = 0;
	while (i < WEAPON_AMOUNT)
	{
		update_weapon_button(buymenu, inv, i);
		i++;
	}
	str = ft_sprintf("DOSH %d", inv->dosh);
	bui_set_element_text(buymenu->currency, str);
	ft_strdel(&str);
	only_one_button_toggled_at_a_time(buymenu->all_guns, &buymenu->active_gun);
}
