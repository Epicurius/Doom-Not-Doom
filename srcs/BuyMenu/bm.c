/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 10:22:02 by jsalmi            #+#    #+#             */
/*   Updated: 2022/01/14 15:00:32 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buymenu.h"

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
		< buymenu->inv->weapon[buymenu->wep_type].ammo_price
		|| buymenu->inv->weapon[buymenu->wep_type].cur_ammo
		>= buymenu->inv->weapon[buymenu->wep_type].max_ammo)
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
	if (buymenu->inv->dosh < buymenu->inv->armour_price
		|| *buymenu->inv->armour >= buymenu->inv->max_armour)
		buymenu->armor_price_button->state = UI_STATE_DEFAULT;
	if (buymenu->inv->dosh < buymenu->inv->max_armour_price)
		buymenu->max_armor_price_button->state = UI_STATE_DEFAULT;
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
	buymenu_init(&buymenu, window);
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
