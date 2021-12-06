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

enum e_weapon_types // if nikals has this, remove from here;
{
	WEP_TYPE_SHOTGUN = 0,
	WEP_TYPE_GLOCK,
	WEP_TYPE_KAR98,
	WEP_TYPE_LAUNCHER,
	WEP_TYPE_MINIGUN,
	WEP_TYPE_AMOUNT
};

enum e_weapon_stat_types
{
	WEP_STAT_DAMAGE = 0,
	WEP_STAT_FIRERATE,
	WEP_STAT_AMMO,
	WEP_STAT_MAX_AMMO,
	WEP_STAT_AMOUNT
};

/*
 *	t_list	*weapon_buttons;	list of t_ui_element;
 *	t_ui_element *active_weapon_button; the currently clicked weapon_button from 'weapon_buttons';
 *	int				wep_type;	one of e_weapon_types; whichi is currently selected;
*/
typedef struct s_buymenu
{
	bool			run;

	t_ui_layout		layout;
	t_ui_window		*main_win;
	t_ui_element	*close_button;

	t_ui_element	*weapon_button[WEP_TYPE_AMOUNT];
	t_ui_element	*weapon_buy_button[WEP_TYPE_AMOUNT];

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

#endif
