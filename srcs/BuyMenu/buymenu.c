#include "buymenu.h"

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
