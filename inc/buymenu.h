/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buymenu.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalmi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 10:39:17 by jsalmi            #+#    #+#             */
/*   Updated: 2021/07/07 10:53:20 by jsalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUYMENU_H
# define BUYMENU_H

# include "better_libui.h"
# include "path.h"
# include "doom.h"

typedef struct s_buymenu
{
	t_bui_element	*menu;
	t_bui_element	*exit_button;
	t_bui_element	*currency;
	t_bui_element	*weapon_stats;
	t_bui_element	*player_stats;
	t_bui_element	*weapon_menu;
	t_bui_element	*weapon_upgrades;
	t_bui_element	*player_menu;

	//WEAPON STATS ELEMENTS
	t_bui_element	*damage_stat;
	t_bui_element	*ammo_stat;
	t_bui_element	*max_ammo_stat;
	t_bui_element	*firerate_stat;

	//PLAYER STATS ELEMENTS
	t_bui_element	*speed_stat;
	t_bui_element	*jump_stat;
	t_bui_element	*armour_stat;
	t_bui_element	*max_armour_stat;

	//WEAPON MENU ELEMENTS
	t_bui_element	*gun_elem[WEAPON_AMOUNT];
	t_bui_element	*gun_buy[WEAPON_AMOUNT];

	//PLAYER MENU ELEMENTS
	t_bui_element	*damage_elem;
	t_bui_element	*firerate_elem;
	t_bui_element	*ammo_elem;
	t_bui_element	*max_ammo_elem;

	//PLAYER MENU ELEMENTS
	t_bui_element	*armor_elem;
	t_bui_element	*max_armor_elem;
	t_bui_element	*jump_elem;
	t_bui_element	*speed_elem;

	// EVENT HANDLING
	t_bui_element	*active_gun;
	t_list			*all_guns;
}					t_buymenu;

/* INITS */
t_buymenu			*buymenu_init(void);
void				menu_init(t_bui_window *win, t_buymenu *buymenu);
void				exit_button_init(t_buymenu *buymenu);
void				currency_init(t_buymenu *buymenu);
void				weapon_stats_init(t_buymenu *buymenu);
void				player_stats_init(t_buymenu *buymenu);
void				weapon_menu_init(t_buymenu *buymenu);
void				weapon_upgrades_init(t_buymenu *buymenu);
void				player_menu_init(t_buymenu *buymenu);

/* EVENTS */
void				weapon_stat_events(t_buymenu *buymenu, t_inv *inv);
void				player_stat_events(t_buymenu *buymenu, t_inv *inv);
void				weapon_buying_events(t_buymenu *buymenu, t_inv *inv);
void				weapon_upgrading_events(t_buymenu *buymenu, t_inv *inv);
void				player_upgrading_events(t_buymenu *buymenu, t_inv *inv);

/* BUTTONS */
t_bui_element		*new_stat(t_bui_element *parent, char *str, t_xywh pos);
t_bui_element		*new_button(t_bui_element *parent, char *name, t_xywh c);
t_bui_element		*new_buy_button(t_bui_element *parent, t_xywh c);
t_bui_element		*new_upgrade_button(t_bui_element *parent, char *str, int i);

/* HELP */
int					get_active_gun(t_buymenu *buymenu);
void				give_weapon(t_buymenu *buymenu, t_inv *inv, int i);

/* FREE */
void				buymenu_quit(t_buymenu *buymenu);

#endif
