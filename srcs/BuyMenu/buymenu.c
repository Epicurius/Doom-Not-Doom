#include "buymenu.h"

void	weapon_buy_init(t_buymenu *buymenu)
{
	char	str[20];

	buymenu->weapon_buy_button[WEAPON_SHOTGUN]
		= ui_layout_get_element(&buymenu->layout, "shotgun_buy_button");
	buymenu->weapon_buy_button[WEAPON_GUN]
		= ui_layout_get_element(&buymenu->layout, "glock_buy_button");
	buymenu->weapon_buy_button[WEAPON_KAR]
		= ui_layout_get_element(&buymenu->layout, "kar98_buy_button");
	buymenu->weapon_buy_button[WEAPON_LAUNCHER]
		= ui_layout_get_element(&buymenu->layout, "launcher_buy_button");
	buymenu->weapon_buy_button[WEAPON_MINIGUN]
		= ui_layout_get_element(&buymenu->layout, "minigun_buy_button");
	ft_strcpy(str, "BUY $");
	ui_button_set_text(buymenu->weapon_buy_button[WEAPON_SHOTGUN],
		&ft_b_itoa(buymenu->inv->weapon[WEAPON_SHOTGUN].price, &str[5])[-5]);
	ui_button_set_text(buymenu->weapon_buy_button[WEAPON_GUN],
		&ft_b_itoa(buymenu->inv->weapon[WEAPON_GUN].price, &str[5])[-5]);
	ui_button_set_text(buymenu->weapon_buy_button[WEAPON_KAR],
		&ft_b_itoa(buymenu->inv->weapon[WEAPON_KAR].price, &str[5])[-5]);
	ui_button_set_text(buymenu->weapon_buy_button[WEAPON_LAUNCHER],
		&ft_b_itoa(buymenu->inv->weapon[WEAPON_LAUNCHER].price, &str[5])[-5]);
	ui_button_set_text(buymenu->weapon_buy_button[WEAPON_MINIGUN],
		&ft_b_itoa(buymenu->inv->weapon[WEAPON_MINIGUN].price, &str[5])[-5]);
}

void	weapon_menu_init(t_buymenu *buymenu)
{
	buymenu->weapon_button[WEAPON_SHOTGUN]
		= ui_layout_get_element(&buymenu->layout, "shotgun_button");
	buymenu->weapon_button[WEAPON_GUN]
		= ui_layout_get_element(&buymenu->layout, "glock_button");
	buymenu->weapon_button[WEAPON_KAR]
		= ui_layout_get_element(&buymenu->layout, "kar98_button");
	buymenu->weapon_button[WEAPON_LAUNCHER]
		= ui_layout_get_element(&buymenu->layout, "launcher_button");
	buymenu->weapon_button[WEAPON_MINIGUN]
		= ui_layout_get_element(&buymenu->layout, "minigun_button");
	buymenu->active_weapon_button = buymenu->weapon_button[WEAPON_SHOTGUN];
	add_to_list(&buymenu->weapon_buttons,
		buymenu->weapon_button[WEAPON_SHOTGUN], sizeof(t_ui_element));
	add_to_list(&buymenu->weapon_buttons,
		buymenu->weapon_button[WEAPON_GUN], sizeof(t_ui_element));
	add_to_list(&buymenu->weapon_buttons,
		buymenu->weapon_button[WEAPON_KAR], sizeof(t_ui_element));
	add_to_list(&buymenu->weapon_buttons,
		buymenu->weapon_button[WEAPON_LAUNCHER], sizeof(t_ui_element));
	add_to_list(&buymenu->weapon_buttons,
		buymenu->weapon_button[WEAPON_MINIGUN], sizeof(t_ui_element));
	weapon_buy_init(buymenu);
}

void	weapon_upgrade_init(t_buymenu *buymenu)
{
	buymenu->damage_amount_label
		= ui_layout_get_element(&buymenu->layout, "damage_amount_label");
	buymenu->damage_price_button
		= ui_layout_get_element(&buymenu->layout, "damage_price_button");
	buymenu->firerate_amount_label
		= ui_layout_get_element(&buymenu->layout, "firerate_amount_label");
	buymenu->firerate_price_button
		= ui_layout_get_element(&buymenu->layout, "firerate_price_button");
	buymenu->ammo_amount_label
		= ui_layout_get_element(&buymenu->layout, "ammo_amount_label");
	buymenu->ammo_price_button
		= ui_layout_get_element(&buymenu->layout, "ammo_price_button");
	buymenu->max_ammo_amount_label
		= ui_layout_get_element(&buymenu->layout, "max_ammo_amount_label");
	buymenu->max_ammo_price_button
		= ui_layout_get_element(&buymenu->layout, "max_ammo_price_button");
}

void	player_upgrade_init(t_buymenu *buymenu)
{
	buymenu->speed_amount_label
		= ui_layout_get_element(&buymenu->layout, "speed_amount_label");
	buymenu->speed_price_button
		= ui_layout_get_element(&buymenu->layout, "speed_price_button");
	buymenu->jump_amount_label
		= ui_layout_get_element(&buymenu->layout, "jump_amount_label");
	buymenu->jump_price_button
		= ui_layout_get_element(&buymenu->layout, "jump_price_button");
	buymenu->armor_amount_label
		= ui_layout_get_element(&buymenu->layout, "armor_amount_label");
	buymenu->armor_price_button
		= ui_layout_get_element(&buymenu->layout, "armor_price_button");
	buymenu->max_armor_amount_label
		= ui_layout_get_element(&buymenu->layout, "max_armor_amount_label");
	buymenu->max_armor_price_button
		= ui_layout_get_element(&buymenu->layout, "max_armor_price_button");
}

void	weapon_stat_init(t_buymenu *buymenu)
{
	buymenu->ammo_stat_amount_label
		= ui_layout_get_element(&buymenu->layout, "ammo_stat_amount_label");
	buymenu->max_ammo_stat_amount_label
		= ui_layout_get_element(&buymenu->layout, "max_ammo_stat_amount_label");
	buymenu->firerate_stat_amount_label
		= ui_layout_get_element(&buymenu->layout, "firerate_stat_amount_label");
	buymenu->damage_stat_amount_label
		= ui_layout_get_element(&buymenu->layout, "damage_stat_amount_label");
}

void	player_stat_init(t_buymenu *buymenu)
{
	buymenu->speed_stat_amount_label
		= ui_layout_get_element(&buymenu->layout, "speed_stat_amount_label");
	buymenu->jump_stat_amount_label
		= ui_layout_get_element(&buymenu->layout, "jump_stat_amount_label");
	buymenu->armor_stat_amount_label
		= ui_layout_get_element(&buymenu->layout, "armor_stat_amount_label");
	buymenu->max_armor_stat_amount_label = ui_layout_get_element(
			&buymenu->layout, "max_armor_stat_amount_label");
}

void	buymenu_init(t_buymenu *buymenu)
{
	buymenu->run = 1;
	ui_layout_load(&buymenu->layout, GAME_PATH"srcs/BuyMenu/layout.ui");
	buymenu->main_win = ui_layout_get_window(&buymenu->layout, "main_win");
	buymenu->close_button
		= ui_layout_get_element(&buymenu->layout, "close_button");
	weapon_menu_init(buymenu);
	weapon_upgrade_init(buymenu);
	player_upgrade_init(buymenu);
	weapon_stat_init(buymenu);
	player_stat_init(buymenu);
	buymenu->currency_amount_label
		= ui_layout_get_element(&buymenu->layout, "currency_amount_label");
}

void	attempt_buying_weapon(t_buymenu *buymenu, int wep_type)
{
	if (!buymenu->inv->weapon[wep_type].own)
		buymenu->weapon_button[wep_type]->event = 0;
	if (buymenu->inv->dosh < buymenu->inv->weapon[wep_type].price)
		buymenu->weapon_buy_button[wep_type]->state = UI_STATE_DEFAULT;
	if (buymenu->weapon_buy_button[wep_type]->event
		&& buymenu->inv->weapon[wep_type].own)
	{
		buymenu->weapon_buy_button[wep_type]->event = 0;
		buymenu->weapon_buy_button[wep_type]->state = UI_STATE_DEFAULT;
		ui_label_set_text(ui_button_get_label_element(
				buymenu->weapon_buy_button[wep_type]), "OWNED");
	}
	else if (buymenu->weapon_buy_button[wep_type]->state == UI_STATE_CLICK)
	{
		if (buymenu->inv->dosh >= buymenu->inv->weapon[wep_type].price)
		{
			buymenu->inv->dosh -= buymenu->inv->weapon[wep_type].price;
			buymenu->inv->weapon[wep_type].own = 1;
			buymenu->active_weapon_button = buymenu->weapon_button[wep_type];
		}
	}
}

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

void	attempt_buying_stat(
		int *dosh, int price, int *stat, int stat_increase)
{
	if (*dosh >= price)
	{
		*dosh -= price;
		*stat += stat_increase;
	}
}

void	attempt_buying_stat_f(
		int *dosh, int price, float *stat, float stat_increase)
{
	if (*dosh >= price)
	{
		*dosh -= price;
		*stat += stat_increase;
	}
}

/*
 * All weapon stats you cant afford will be disabled here;
*/
void	disable_not_affordable_weapon_upgrade_buttons(t_buymenu *buymenu)
{
	if (buymenu->inv->dosh
		< buymenu->inv->weapon[buymenu->wep_type].damage_price)
		buymenu->damage_price_button->state = UI_STATE_DEFAULT;
	if (buymenu->inv->dosh
		< buymenu->inv->weapon[buymenu->wep_type].firerate_price)
		buymenu->firerate_price_button->state = UI_STATE_DEFAULT;
	if (buymenu->inv->dosh
		< buymenu->inv->weapon[buymenu->wep_type].ammo_price)
		buymenu->ammo_price_button->state = UI_STATE_DEFAULT;
	if (buymenu->inv->dosh
		< buymenu->inv->weapon[buymenu->wep_type].max_ammo_price)
		buymenu->max_ammo_price_button->state = UI_STATE_DEFAULT;
}

/*
 * All player stats you cant afford will be disabled here;
*/
void	disable_not_affordable_player_upgrade_buttons(t_buymenu *buymenu)
{
	if (buymenu->inv->dosh < buymenu->inv->speed_price)
		buymenu->speed_price_button->state = UI_STATE_DEFAULT;
	if (buymenu->inv->dosh < buymenu->inv->jump_price)
		buymenu->jump_price_button->state = UI_STATE_DEFAULT;
	if (buymenu->inv->dosh < buymenu->inv->armour_price)
		buymenu->armor_price_button->state = UI_STATE_DEFAULT;
	if (buymenu->inv->dosh < buymenu->inv->max_armour_price)
		buymenu->max_armor_price_button->state = UI_STATE_DEFAULT;
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

void	update_currency(t_buymenu *buymenu)
{
	char	temp_str[20];

	ui_label_set_text(buymenu->currency_amount_label,
		ft_b_itoa(buymenu->inv->dosh, temp_str));
}

void	update_amount_label(t_buymenu *buymenu, int wep_type)
{
	char	temp_str[20];

	ui_label_set_text(buymenu->ammo_stat_amount_label,
		ft_b_itoa(buymenu->inv->weapon[wep_type].cur_ammo, temp_str));
	ui_label_set_text(buymenu->max_ammo_stat_amount_label,
		ft_b_itoa(buymenu->inv->weapon[wep_type].max_ammo, temp_str));
	ui_label_set_text(buymenu->firerate_stat_amount_label,
		ft_b_itoa(buymenu->inv->weapon[wep_type].frame_rate, temp_str));
	ui_label_set_text(buymenu->damage_stat_amount_label,
		ft_b_itoa(buymenu->inv->weapon[wep_type].damage, temp_str));
}

void	update_upgrade_labels(t_buymenu *buymenu, int wep_type)
{
	char	str[20];

	str[0] = '+';
	ui_label_set_text(buymenu->damage_amount_label,
		&ft_b_itoa(buymenu->inv->weapon[wep_type].damage_increase,
			&str[1])[-1]);
	ui_label_set_text(buymenu->ammo_amount_label,
		&ft_b_itoa(buymenu->inv->weapon[wep_type].ammo_increase, &str[1])[-1]);
	ui_label_set_text(buymenu->max_ammo_amount_label,
		&ft_b_itoa(buymenu->inv->weapon[wep_type].max_ammo_increase,
			&str[1])[-1]);
	ui_label_set_text(buymenu->firerate_amount_label,
		ft_b_itoa(buymenu->inv->weapon[wep_type].firerate_increase, str));
	str[0] = '$';
	ui_button_set_text(buymenu->damage_price_button,
		&ft_b_itoa(buymenu->inv->weapon[wep_type].damage_price, &str[1])[-1]);
	ui_button_set_text(buymenu->ammo_price_button,
		&ft_b_itoa(buymenu->inv->weapon[wep_type].ammo_price, &str[1])[-1]);
	ui_button_set_text(buymenu->max_ammo_price_button,
		&ft_b_itoa(buymenu->inv->weapon[wep_type].max_ammo_price, &str[1])[-1]);
	ui_button_set_text(buymenu->firerate_price_button,
		&ft_b_itoa(buymenu->inv->weapon[wep_type].firerate_price, &str[1])[-1]);
}

/*
 * Both the stats showing in the top mid menu,
 * and the prices and increases on the bot mid menu;
*/
void	update_weapon_stats(t_buymenu *buymenu)
{
	update_amount_label(buymenu, buymenu->wep_type);
	update_upgrade_labels(buymenu, buymenu->wep_type);
}

void	update_player_stat_amount_labels(t_buymenu *buymenu)
{
	char	temp_str[20];

	ui_label_set_text(buymenu->jump_stat_amount_label,
		ft_b_itoa(*buymenu->inv->jump, temp_str));
	ui_label_set_text(buymenu->speed_stat_amount_label,
		ft_b_itoa(*buymenu->inv->speed, temp_str));
	ui_label_set_text(buymenu->armor_stat_amount_label,
		ft_b_itoa(*buymenu->inv->armour, temp_str));
	ui_label_set_text(buymenu->max_armor_stat_amount_label,
		ft_b_itoa(buymenu->inv->max_armour, temp_str));
}

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

void	buymenu_free(t_buymenu *buymenu)
{
	ui_layout_free(&buymenu->layout);
	ft_lstdel(&buymenu->weapon_buttons, &dummy_free_er);
}

void	buymenu(SDL_Window *window, SDL_Surface *surf, t_inv *inv)
{
	t_buymenu	buymenu;
	SDL_Event	e;
	SDL_Texture	*bg_texture;

	ui_sdl_init();
	memset(&buymenu, 0, sizeof(t_buymenu));
	buymenu.inv = inv;
	buymenu_init(&buymenu);
	ui_window_replace_win(buymenu.main_win, window);
	ui_window_texture_pos_set(buymenu.main_win, vec2i(1920, 1080));
	bg_texture = SDL_CreateTextureFromSurface(buymenu.main_win->renderer, surf);
	while (buymenu.run)
	{
		while (SDL_PollEvent(&e))
		{
			ui_layout_event(&buymenu.layout, e);
			user_events(&buymenu, e);
		}
		ui_window_render_texture(buymenu.main_win, bg_texture);
		ui_layout_render(&buymenu.layout);
	}
	SDL_DestroyTexture(bg_texture);
	buymenu_free(&buymenu);
}
