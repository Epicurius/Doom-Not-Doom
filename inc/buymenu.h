/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buymenu.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalmi <jsalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 19:52:41 by jsalmi            #+#    #+#             */
/*   Updated: 2021/12/10 20:03:55 by jsalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUYMENU_H
# define BUYMENU_H
# include "fcntl.h"
# include "sys/stat.h"
# include "libui.h"
# include "libft.h"
# include "libpf.h"
# include "SDL.h"
# include "SDL_ttf.h"
# include "SDL_image.h"
# include "bxpm.h"
# include "doom.h"

/*
 *	t_list	*weapon_buttons;	list of t_ui_element;
 *	t_ui_element *active_weapon_button; the currently clicked weapon_button
 		from 'weapon_buttons';
 *	int				wep_type;	one of e_weapon_types; whichi
 		is currently selected;
*/
typedef struct s_buymenu
{
	bool			run;

	t_ui_layout		layout;
	t_ui_window		*main_win;
	t_ui_element	*close_button;

	t_ui_element	*weapon_button[WEAPON_AMOUNT];
	t_ui_element	*weapon_buy_button[WEAPON_AMOUNT];

	t_list			*weapon_buttons;
	t_ui_element	*active_weapon_button;
	int				wep_type;

	t_ui_element	*ammo_stat_amount_label;
	t_ui_element	*max_ammo_stat_amount_label;
	t_ui_element	*firerate_stat_amount_label;
	t_ui_element	*damage_stat_amount_label;

	t_ui_element	*damage_amount_label;
	t_ui_element	*damage_price_button;
	t_ui_element	*firerate_amount_label;
	t_ui_element	*firerate_price_button;
	t_ui_element	*ammo_amount_label;
	t_ui_element	*ammo_price_button;
	t_ui_element	*max_ammo_amount_label;
	t_ui_element	*max_ammo_price_button;

	t_ui_element	*speed_stat_amount_label;
	t_ui_element	*jump_stat_amount_label;
	t_ui_element	*armor_stat_amount_label;
	t_ui_element	*max_armor_stat_amount_label;

	t_ui_element	*speed_amount_label;
	t_ui_element	*speed_price_button;
	t_ui_element	*jump_amount_label;
	t_ui_element	*jump_price_button;
	t_ui_element	*armor_amount_label;
	t_ui_element	*armor_price_button;
	t_ui_element	*max_armor_amount_label;
	t_ui_element	*max_armor_price_button;

	t_ui_element	*currency_amount_label;

	t_inv			*inv;
}					t_buymenu;

void	weapon_buy_init(t_buymenu *buymenu);
void	weapon_menu_init(t_buymenu *buymenu);
void	weapon_upgrade_init(t_buymenu *buymenu);
void	player_upgrade_init(t_buymenu *buymenu);
void	weapon_stat_init(t_buymenu *buymenu);
void	player_stat_init(t_buymenu *buymenu);
void	buymenu_init(t_buymenu *buymenu);

void	update_currency(t_buymenu *buymenu);
void	update_amount_label(t_buymenu *buymenu, int wep_type);
void	update_upgrade_labels(t_buymenu *buymenu, int wep_type);
void	update_weapon_stats(t_buymenu *buymenu);
void	update_player_stat_amount_labels(t_buymenu *buymenu);
void	update_player_upgrade_amount_labels(t_buymenu *buymenu);
void	update_player_stats(t_buymenu *buymenu);

void	event_weapon_buy(t_buymenu *buymenu);
void	event_weapon_stat_buy(t_buymenu *buymenu);
void	event_player_stat_buy(t_buymenu *buymenu);
void	user_events(t_buymenu *buymenu, SDL_Event e);
void	check_which(t_buymenu *buymenu, int wep_type);

void	attempt_buying_weapon(t_buymenu *buymenu, int wep_type);
void	attempt_buying_stat(int *dosh, int price, int *stat, int stat_inc);
void	attempt_buying_stat_f(int *dosh, int price, float *stat, float stat_in);

void	disable_not_affordable_weapon_upgrade_buttons(t_buymenu *buymenu);
void	disable_not_affordable_player_upgrade_buttons(t_buymenu *buymenu);
void	buymenu_free(t_buymenu *buymenu);

#endif
