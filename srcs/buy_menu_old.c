/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buy_menu.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 10:40:21 by jsalmi            #+#    #+#             */
/*   Updated: 2021/07/16 20:48:15 by jsalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buymenu.h"

typedef struct s_buymenu
{
	t_bui_element	*menu;
	t_bui_element	*exit_button;
	t_bui_element	*currency;
	t_bui_element	*dosh;
	t_bui_element	*weapon_stats;
	t_bui_element	*player_stats;
	t_bui_element	*weapon_menu;
	t_bui_element	*weapon_upgrades;
	t_bui_element	*player_menu;

	// HELP
	int				third_w;
	int				eight_h;
	SDL_Surface		*mc_button;
	SDL_Surface		*mc_button_disable;
	SDL_Surface		*mc_button_x3;
	SDL_Surface		*mc_button_x3_disable;

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

static void	copy_bxpm_pix_to_surf_pix(t_bxpm *bxpm, SDL_Surface *surface)
{
	int	i;

	i = 0;
	while (i < bxpm->pix_nb)
	{
		((Uint32 *)surface->pixels)[i] = bxpm->clr[bxpm->pix[i]];
		i++;
	}
}

SDL_Surface	*load_bxpm_to_surface(char *bxpm_file)
{
	SDL_Surface	*surface;
	t_bxpm		*bxpm;
	int			result;

	bxpm = ft_memalloc(sizeof(t_bxpm));
	result = read_bxpm(bxpm, bxpm_file);
	if (result != 1)
	{
		ft_printf("Couldnt open file: %s\n", bxpm_file);
		return (NULL);
	}
	surface = create_surface(bxpm->w, bxpm->h);
	copy_bxpm_pix_to_surf_pix(bxpm, surface);
	free(bxpm->pix);
	free(bxpm->clr);
	free(bxpm);
	return (surface);
}

t_bui_element	*new_stat(
	t_bui_element *parent, char *str, char *image_path, t_xywh pos)
{
	t_bui_element	*elem;
	t_xywh			stat_icon_pos;

	elem = bui_new_element(parent, str, pos);
	bui_set_element_text_font(elem, TTF_PATH"DroidSans.ttf", 25, 0xffffff00);
	bui_set_element_color(elem, 0x00000000);
	stat_icon_pos = ui_init_coords(elem->position.w / 2, 0,
			elem->position.w / 4, elem->position.h);
	bui_set_element_image_from_path(elem, ELEMENT_ALL,
		image_path, &stat_icon_pos);
	bui_set_element_flags(elem, BUI_ELEMENT_CLEAR);
	return (elem);
}

t_bui_element	*new_button(t_bui_element *parent, char *image_path, t_xywh c)
{
	t_bui_element	*elem;
	SDL_Surface		*image;

	elem = bui_new_element(parent, NULL, c);
	if (ft_strendswith(image_path, ".bxpm") == 0)
	{
		image = load_bxpm_to_surface(image_path);
		bui_set_element_image(elem, ELEMENT_ALL, image, NULL);
		SDL_FreeSurface(image);
	}
	else
		bui_set_element_image_from_path(elem, ELEMENT_ALL, image_path, NULL);
	bui_set_element_state_border(elem, 5, 0xff0000ff, ELEMENT_HOVER);
	bui_set_element_state_border(elem, 5, 0xff00ff00, ELEMENT_CLICK);
	bui_set_element_flags(elem, BUI_ELEMENT_DONT_UPDATE_STATE);
	return (elem);
}

t_bui_element	*new_buy_button(t_bui_element *parent, t_xywh c)
{
	t_bui_element	*buy_button;

	buy_button = bui_new_element(parent, "Buy", c);
	bui_set_element_text_font(buy_button,
		TTF_PATH"DroidSans.ttf", 25, 0xff000000);
	buy_button->text_x = c.w / 4;
	buy_button->text_y = c.h / 5;
	bui_set_element_image_to_states(buy_button,
		ROOT_PATH"ui/ui_images/mc_button.png",
		ROOT_PATH"ui/ui_images/mc_button_hover.png",
		ROOT_PATH"ui/ui_images/mc_button_click.png");
	return (buy_button);
}

t_bui_element	*new_upgrade_button(t_bui_element *parent, char *str, int i)
{
	int				x;
	int				w;
	t_xywh			c;
	t_bui_element	*elem;

	x = parent->position.w / 8;
	w = parent->position.w - (x * 2);
	c = ui_init_coords(x, i * 100 + ((i + 1) * 20) + 20, w, 100);
	elem = bui_new_element(parent, str, c);
	elem->text_x = elem->position.w / 9;
	elem->text_y = elem->position.h / 5;
	bui_set_element_text_font(elem, TTF_PATH"DroidSans.ttf", 25, 0xff000000);
	bui_set_element_image_to_states(elem,
		ROOT_PATH"ui/ui_images/mc_button_x3.png",
		ROOT_PATH"ui/ui_images/mc_button_x3_hover.png",
		ROOT_PATH"ui/ui_images/mc_button_x3_click.png");
	return (elem);
}

void	menu_init(t_bui_window *win, t_buymenu *buymenu)
{
	t_xywh	c;

	c = ui_init_coords(0, 0, win->position.w, win->position.h);
	buymenu->menu = bui_new_menu(win, NULL, c);
	buymenu->menu->update = 0;
	bui_set_element_color(buymenu->menu, 0x64222222);
	buymenu->eight_h = buymenu->menu->position.h / 4;
	buymenu->third_w = buymenu->menu->position.w / 3;
}

void	exit_button_init(t_buymenu *buymenu)
{
	t_xywh	c;

	c = ui_init_coords(0, 0, 32, 32);
	buymenu->exit_button = bui_new_element(buymenu->menu, NULL, c);
	bui_set_element_image_from_path(buymenu->exit_button, ELEMENT_ALL,
		ROOT_PATH"ui/ui_images/exit_button.png", NULL);
	bui_set_element_image_from_path(buymenu->exit_button, ELEMENT_HOVER,
		ROOT_PATH"ui/ui_images/exit_button_hover.png", NULL);
}

void	currency_init(t_buymenu *buymenu, t_inv *inv)
{
	t_xywh	c;

	c = ui_init_coords(5, 10, buymenu->third_w - 10, buymenu->eight_h);
	buymenu->currency = bui_new_element(buymenu->menu, "Dosh", c);
	bui_set_element_flags(buymenu->currency,
		BUI_ELEMENT_DONT_UPDATE_STATE | BUI_ELEMENT_CLEAR);
	bui_set_element_color(buymenu->currency, 0x7f073605);
	buymenu->currency->text_x = c.w / 2;
	buymenu->currency->text_y = c.h / 3;
	bui_set_element_text_font(buymenu->currency,
		TTF_PATH"DroidSans.ttf", 50, 0xff199515);
	bui_set_element_border(buymenu->currency, 2, 0xff199515);
	c = ui_init_coords(50, 50, 150, 100);
	buymenu->dosh = bui_new_element(buymenu->menu, NULL, c);
	bui_set_element_color(buymenu->dosh, 0x00000000);
	bui_set_element_image_from_path(buymenu->dosh, ELEMENT_ALL,
		ROOT_PATH"ui/ui_images/cash_dosh.bmp", NULL);
}

//////////////// WEAPON STATS /////////////////////
void	weapon_stats_stats_init(t_buymenu *buymenu, t_xywh r_c)
{
	t_xywh	c;

	buymenu->ammo_stat = new_stat(buymenu->weapon_stats, "Ammo",
			GAME_PATH"resources/ICON/ammo_patrons.bmp", r_c);
	c = ui_init_coords(r_c.x, r_c.y + r_c.h, r_c.w, r_c.h);
	buymenu->max_ammo_stat = new_stat(buymenu->weapon_stats, "Max Ammo",
			ROOT_PATH"ui/ui_images/max_ammo.bmp", c);
	c = ui_init_coords(r_c.x + r_c.w, r_c.y + r_c.h, r_c.w, r_c.h);
	buymenu->damage_stat = new_stat(buymenu->weapon_stats, "Damage",
			ROOT_PATH"ui/ui_images/damage.png", c);
	c = ui_init_coords(r_c.x + r_c.w, r_c.y, r_c.w, r_c.h);
	buymenu->firerate_stat = new_stat(buymenu->weapon_stats, "Firerate",
			ROOT_PATH"ui/ui_images/firerate.png", c);
}

void	weapon_stats_init(t_buymenu *buymenu)
{
	t_xywh	r_c;
	t_xywh	c;

	c = ui_init_coords(buymenu->third_w + 5, 10,
			buymenu->third_w - 10, buymenu->eight_h);
	buymenu->weapon_stats = bui_new_element(buymenu->menu, "Weapon Stats", c);
	bui_set_element_flags(buymenu->weapon_stats,
		BUI_ELEMENT_DONT_UPDATE_STATE | BUI_ELEMENT_CLEAR);
	bui_set_element_color(buymenu->weapon_stats, 0x7f073605);
	buymenu->weapon_stats->text_x = 40;
	buymenu->weapon_stats->text_y = 20;
	bui_set_element_text_font(buymenu->weapon_stats,
		TTF_PATH"DroidSans.ttf", 20, 0xff199515);
	bui_set_element_border(buymenu->weapon_stats, 2, 0xff199515);
	r_c = ui_init_coords(buymenu->weapon_stats->position.w / 12,
			buymenu->weapon_stats->position.h / 3,
			buymenu->weapon_stats->position.w / 2
			- buymenu->weapon_stats->position.w / 12,
			buymenu->weapon_stats->position.h / 4);
	weapon_stats_stats_init(buymenu, r_c);
}

//////////////// PLAYER STATS /////////////////////
void	player_stats_stats_init(t_buymenu *buymenu, t_xywh rc)
{
	t_xywh	c;

	buymenu->speed_stat = new_stat(buymenu->player_stats, "Speed",
			ROOT_PATH"ui/ui_images/speed.png", rc);
	c = ui_init_coords(rc.x, rc.y + rc.h, rc.w, rc.h);
	buymenu->jump_stat = new_stat(buymenu->player_stats, "Jump",
			ROOT_PATH"ui/ui_images/jump.png", c);
	c = ui_init_coords(rc.x + rc.w, rc.y, rc.w, rc.h);
	buymenu->armour_stat = new_stat(buymenu->player_stats, "Armor",
			GAME_PATH"resources/ICON/armour_shield.bmp", c);
	c = ui_init_coords(rc.x + rc.w, rc.y + rc.h, rc.w, rc.h);
	buymenu->max_armour_stat = new_stat(buymenu->player_stats, "Max Armor",
			ROOT_PATH"ui/ui_images/armour_plus.bmp", c);
}

void	player_stats_init(t_buymenu *buymenu)
{
	t_xywh	c;
	t_xywh	rc;

	c = ui_init_coords(buymenu->third_w * 2 + 5, 10,
			buymenu->third_w - 10, buymenu->eight_h);
	buymenu->player_stats = bui_new_element(buymenu->menu, "Player Stats", c);
	bui_set_element_flags(buymenu->player_stats,
		BUI_ELEMENT_DONT_UPDATE_STATE | BUI_ELEMENT_CLEAR);
	bui_set_element_color(buymenu->player_stats, 0x7f073605);
	buymenu->player_stats->text_x = 40;
	buymenu->player_stats->text_y = 20;
	bui_set_element_text_font(buymenu->player_stats,
		TTF_PATH"DroidSans.ttf", 20, 0xff199515);
	bui_set_element_border(buymenu->player_stats, 2, 0xff199515);
	rc = ui_init_coords(buymenu->player_stats->position.w / 12,
			buymenu->player_stats->position.h / 3,
			buymenu->player_stats->position.w / 2
			- buymenu->player_stats->position.w / 12,
			buymenu->player_stats->position.h / 4);
	player_stats_stats_init(buymenu, rc);
}

void	weapon_menu_init(t_buymenu *buymenu, t_inv *inv)
{
	t_xywh	c;
	t_xywh	t;
	int		i;
	int		gap;

	c = ui_init_coords(0, buymenu->eight_h, buymenu->third_w,
			buymenu->menu->position.h - buymenu->eight_h);
	buymenu->weapon_menu = bui_new_element(buymenu->menu, NULL, c);
	bui_set_element_flags(buymenu->weapon_menu, BUI_ELEMENT_DONT_UPDATE_STATE);
	bui_set_element_color(buymenu->weapon_menu, 0x00000000);
	i = 0;
	gap = 20;
	t.x = buymenu->weapon_menu->position.w / 8;
	t.h = 100;
	t.w = buymenu->weapon_menu->position.w - (t.x * 2) - t.h;
	while (i < WEAPON_AMOUNT)
	{
		c = ui_init_coords(t.x, (i) * t.h + ((i + 1) * gap) + 20, t.w, t.h);
		buymenu->gun_elem[i] = new_button(buymenu->weapon_menu,
				g_weapon_icon[i], c);
		c = ui_init_coords(c.x + c.w + 5, c.y, c.h, c.h);
		buymenu->gun_buy[i] = new_buy_button(buymenu->weapon_menu, c);
		i++;
	}
}

//////////////// WEAPON UPGRADES //////////////////
void	weapon_upgrades_elem_init(t_buymenu *buymenu)
{
	buymenu->damage_elem
		= new_upgrade_button(buymenu->weapon_upgrades, "+1 Damage", 0);
	buymenu->firerate_elem
		= new_upgrade_button(buymenu->weapon_upgrades, "+1 Firerate", 1);
	buymenu->ammo_elem
		= new_upgrade_button(buymenu->weapon_upgrades, "+10 Ammo", 2);
	buymenu->max_ammo_elem
		= new_upgrade_button(buymenu->weapon_upgrades, "+1 Max Ammo", 3);
}

void	weapon_upgrades_init(t_buymenu *buymenu)
{
	t_xywh	c;

	c = ui_init_coords(buymenu->third_w, buymenu->eight_h, buymenu->third_w,
			buymenu->menu->position.h - buymenu->eight_h);
	buymenu->weapon_upgrades = bui_new_element(buymenu->menu, NULL, c);
	bui_set_element_flags(buymenu->weapon_upgrades,
		BUI_ELEMENT_DONT_UPDATE_STATE);
	bui_set_element_color(buymenu->weapon_upgrades, 0x00000000);
	weapon_upgrades_elem_init(buymenu);
}

///////////////////////// PLAYER MENU ///////////////////
void	player_menu_elem_init(t_buymenu *buymenu)
{
	buymenu->armor_elem
		= new_upgrade_button(buymenu->player_menu, "+10 Armor", 0);
	buymenu->max_armor_elem
		= new_upgrade_button(buymenu->player_menu, "+1 Max Armor", 1);
	buymenu->speed_elem
		= new_upgrade_button(buymenu->player_menu, "+1 Speed", 2);
	buymenu->jump_elem
		= new_upgrade_button(buymenu->player_menu, "+1 Jump", 3);
}

void	player_menu_init(t_buymenu *buymenu)
{
	t_xywh	c;

	c = ui_init_coords(2 * buymenu->third_w, buymenu->eight_h, buymenu->third_w,
			buymenu->menu->position.h - buymenu->eight_h);
	buymenu->player_menu = bui_new_element(buymenu->menu, NULL, c);
	bui_set_element_flags(buymenu->player_menu, BUI_ELEMENT_DONT_UPDATE_STATE);
	bui_set_element_color(buymenu->player_menu, 0x00000000);
	player_menu_elem_init(buymenu);
}

/////////////// EVENTS //////////////////////////
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
	bui_change_element_text(buymenu->gun_buy[i], "Owned");
	if (!inv->weapon[i].own)
	{
		fff = ft_sprintf("Buy\n$%d", inv->weapon[i].price);
		bui_change_element_text(buymenu->gun_buy[i], fff);
		ft_strdel(&fff);
	}
	bui_set_element_image(buymenu->gun_buy[i], ELEMENT_DEFAULT,
		buymenu->mc_button_disable, NULL);
	buymenu->gun_buy[i]->update_state = 0;
	if (!inv->weapon[i].own && inv->dosh >= inv->weapon[i].price)
	{
		bui_set_element_image(buymenu->gun_buy[i], ELEMENT_DEFAULT,
			buymenu->mc_button, NULL);
		buymenu->gun_buy[i]->update_state = 1;
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
	str = ft_itoa(inv->dosh);
	bui_change_element_text(buymenu->currency, str);
	ft_strdel(&str);
	only_one_button_toggled_at_a_time(buymenu->all_guns, &buymenu->active_gun);
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
		ffa = ft_itoa(inv->weapon[i].damage);
		bui_change_element_text(buymenu->damage_stat, ffa);
		ft_strdel(&ffa);
		ffa = ft_itoa(inv->weapon[i].cur_ammo);
		bui_change_element_text(buymenu->ammo_stat, ffa);
		ft_strdel(&ffa);
		ffa = ft_itoa(inv->weapon[i].max_ammo);
		bui_change_element_text(buymenu->max_ammo_stat, ffa);
		ft_strdel(&ffa);
		ffa = ft_itoa(inv->weapon[i].frame_rate);
		bui_change_element_text(buymenu->firerate_stat, ffa);
		ft_strdel(&ffa);
	}
}

/////////////////////////// WEAPON UPGRADING EVENTS ////////////
void	update_weapon_upgrade_buttons(t_buymenu *buymenu, t_inv *inv, int a)
{
	char	*aaa;

	aaa = ft_sprintf("+%d Damage\n$%d",
			inv->weapon[a].damage_increase,
			inv->weapon[a].damage_price);
	bui_change_element_text(buymenu->damage_elem, aaa);
	ft_strdel(&aaa);
	aaa = ft_sprintf("%d Firerate\n$%d",
			inv->weapon[a].firerate_increase,
			inv->weapon[a].firerate_price);
	bui_change_element_text(buymenu->firerate_elem, aaa);
	ft_strdel(&aaa);
	aaa = ft_sprintf("+%d Ammo\n$%d",
			inv->weapon[a].ammo_increase,
			inv->weapon[a].ammo_price);
	bui_change_element_text(buymenu->ammo_elem, aaa);
	ft_strdel(&aaa);
	aaa = ft_sprintf("+%d Max Ammo\n$%d",
			inv->weapon[a].max_ammo_increase,
			inv->weapon[a].max_ammo_price);
	bui_change_element_text(buymenu->max_ammo_elem, aaa);
	ft_strdel(&aaa);
}

void	buy_weapon_events1(t_buymenu *buymenu, t_inv *inv, int a)
{
	if (inv->dosh >= inv->weapon[a].damage_price)
	{
		buymenu->damage_elem->update_state = 1;
		bui_set_element_image(buymenu->damage_elem, ELEMENT_DEFAULT,
			buymenu->mc_button_x3, NULL);
		if (bui_button(buymenu->damage_elem))
		{
			inv->weapon[a].damage += inv->weapon[a].damage_increase;
			inv->dosh -= inv->weapon[a].damage_price;
		}
	}
	if (inv->dosh >= inv->weapon[a].firerate_price)
	{
		buymenu->firerate_elem->update_state = 1;
		bui_set_element_image(buymenu->firerate_elem, ELEMENT_DEFAULT,
			buymenu->mc_button_x3, NULL);
		if (bui_button(buymenu->firerate_elem))
		{
			inv->weapon[a].frame_rate += inv->weapon[a].firerate_increase;
			inv->dosh -= inv->weapon[a].firerate_price;
		}
	}
}

void	buy_weapon_events2(t_buymenu *buymenu, t_inv *inv, int a)
{
	if (inv->dosh >= inv->weapon[a].ammo_price
		&& inv->weapon[a].cur_ammo < inv->weapon[a].max_ammo)
	{
		buymenu->ammo_elem->update_state = 1;
		bui_set_element_image(buymenu->ammo_elem, ELEMENT_DEFAULT,
			buymenu->mc_button_x3, NULL);
		if (bui_button(buymenu->ammo_elem))
		{
			inv->weapon[a].cur_ammo += min(inv->weapon[a].ammo_increase,
					inv->weapon[a].max_ammo - inv->weapon[a].cur_ammo);
			inv->dosh -= inv->weapon[a].ammo_price;
		}
	}
	if (inv->dosh >= inv->weapon[a].max_ammo_price)
	{
		buymenu->max_ammo_elem->update_state = 1;
		bui_set_element_image(buymenu->max_ammo_elem, ELEMENT_DEFAULT,
			buymenu->mc_button_x3, NULL);
		if (bui_button(buymenu->max_ammo_elem))
		{
			inv->weapon[a].max_ammo += inv->weapon[a].max_ammo_increase;
			inv->dosh -= inv->weapon[a].max_ammo_price;
		}
	}
}

int	get_active_gun(t_buymenu *buymenu)
{
	int	a;

	a = 0;
	if (!buymenu->active_gun)
		return (-1);
	while (a < WEAPON_AMOUNT)
	{
		if (buymenu->active_gun == buymenu->gun_elem[a])
			return (a);
		a++;
	}
	return (-2);
}

void	weapon_upgrading_events(t_buymenu *buymenu, t_inv *inv)
{
	int	a;

	buymenu->damage_elem->update_state = 0;
	bui_set_element_image(buymenu->damage_elem, ELEMENT_DEFAULT,
		buymenu->mc_button_x3_disable, NULL);
	buymenu->firerate_elem->update_state = 0;
	bui_set_element_image(buymenu->firerate_elem, ELEMENT_DEFAULT,
		buymenu->mc_button_x3_disable, NULL);
	buymenu->ammo_elem->update_state = 0;
	bui_set_element_image(buymenu->ammo_elem, ELEMENT_DEFAULT,
		buymenu->mc_button_x3_disable, NULL);
	buymenu->max_ammo_elem->update_state = 0;
	bui_set_element_image(buymenu->max_ammo_elem, ELEMENT_DEFAULT,
		buymenu->mc_button_x3_disable, NULL);
	if (buymenu->active_gun)
	{
		a = get_active_gun(buymenu);
		update_weapon_upgrade_buttons(buymenu, inv, a);
		buy_weapon_events1(buymenu, inv, a);
		buy_weapon_events2(buymenu, inv, a);
	}
}

void	player_stat_events(t_buymenu *buymenu, t_inv *inv)
{
	char	*lll;

	lll = ft_itoa((int)*inv->speed);
	bui_change_element_text(buymenu->speed_stat, lll);
	ft_strdel(&lll);
	lll = ft_itoa((int)*inv->jump);
	bui_change_element_text(buymenu->jump_stat, lll);
	ft_strdel(&lll);
	lll = ft_itoa(*inv->armour);
	bui_change_element_text(buymenu->armour_stat, lll);
	ft_strdel(&lll);
	lll = ft_itoa(inv->max_armour);
	bui_change_element_text(buymenu->max_armour_stat, lll);
	ft_strdel(&lll);
}

/////////////// PLAYER UPGRADE EVENTS ///////////////////////
void	update_player_upgrade_buttons(t_buymenu *buymenu, t_inv *inv)
{
	char	*ooo;

	ooo = ft_sprintf("+10 Armor\n$%d", inv->armour_price);
	bui_change_element_text(buymenu->armor_elem, ooo);
	ft_strdel(&ooo);
	ooo = ft_sprintf("+1 Max Armor\n$%d", inv->max_armour_price);
	bui_change_element_text(buymenu->max_armor_elem, ooo);
	ft_strdel(&ooo);
	ooo = ft_sprintf("+1 Speed\n$%d", inv->speed_price);
	bui_change_element_text(buymenu->speed_elem, ooo);
	ft_strdel(&ooo);
	ooo = ft_sprintf("+1 Jump\n$%d", inv->jump_price);
	bui_change_element_text(buymenu->jump_elem, ooo);
	ft_strdel(&ooo);
}

void	buy_player_upgrades_events1(t_buymenu *buymenu, t_inv *inv)
{
	if (inv->dosh >= inv->armour_price
		&& *inv->armour < inv->max_armour)
	{
		buymenu->armor_elem->update_state = 1;
		bui_set_element_image(buymenu->armor_elem, ELEMENT_DEFAULT,
			buymenu->mc_button_x3, NULL);
		if (bui_button(buymenu->armor_elem))
		{
			*inv->armour += min(10, inv->max_armour - *inv->armour);
			inv->dosh -= inv->armour_price;
		}
	}
	if (inv->dosh >= inv->max_armour_price)
	{
		buymenu->max_armor_elem->update_state = 1;
		bui_set_element_image(buymenu->max_armor_elem, ELEMENT_DEFAULT,
			buymenu->mc_button_x3, NULL);
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
		bui_set_element_image(buymenu->speed_elem, ELEMENT_DEFAULT,
			buymenu->mc_button_x3, NULL);
		if (bui_button(buymenu->speed_elem))
		{
			*inv->speed += 1;
			inv->dosh -= inv->speed_price;
		}
	}
	if (inv->dosh >= inv->jump_price)
	{
		buymenu->jump_elem->update_state = 1;
		bui_set_element_image(buymenu->jump_elem, ELEMENT_DEFAULT,
			buymenu->mc_button_x3, NULL);
		if (bui_button(buymenu->jump_elem))
		{
			*inv->jump += 1;
			inv->dosh -= inv->jump_price;
		}
	}
}

void	player_upgrading_events(t_buymenu *buymenu, t_inv *inv)
{
	update_player_upgrade_buttons(buymenu, inv);
	bui_set_element_image(buymenu->armor_elem, ELEMENT_DEFAULT,
		buymenu->mc_button_x3_disable, NULL);
	buymenu->armor_elem->update_state = 0;
	bui_set_element_image(buymenu->max_armor_elem, ELEMENT_DEFAULT,
		buymenu->mc_button_x3_disable, NULL);
	buymenu->max_armor_elem->update_state = 0;
	bui_set_element_image(buymenu->speed_elem, ELEMENT_DEFAULT,
		buymenu->mc_button_x3_disable, NULL);
	buymenu->speed_elem->update_state = 0;
	bui_set_element_image(buymenu->jump_elem, ELEMENT_DEFAULT,
		buymenu->mc_button_x3_disable, NULL);
	buymenu->jump_elem->update_state = 0;
	buy_player_upgrades_events1(buymenu, inv);
	buy_player_upgrades_events2(buymenu, inv);
}

//////////////// BUY MENU STUFF ////////////////
t_buymenu	*buymenu_init(void)
{
	t_buymenu	*buymenu;

	buymenu = ft_memalloc(sizeof(t_buymenu));
	buymenu->mc_button
		= load_image(ROOT_PATH"ui/ui_images/mc_button.png");
	buymenu->mc_button_disable
		= load_image(ROOT_PATH"ui/ui_images/mc_button_disable.png");
	buymenu->mc_button_x3
		= load_image(ROOT_PATH"ui/ui_images/mc_button_x3.png");
	buymenu->mc_button_x3_disable
		= load_image(ROOT_PATH"ui/ui_images/mc_button_x3_disable.png");
	buymenu->active_gun = NULL;
	buymenu->all_guns = NULL;
	return (buymenu);
}

void	buymenu_quit(t_buymenu *buymenu)
{
	SDL_FreeSurface(buymenu->mc_button);
	SDL_FreeSurface(buymenu->mc_button_disable);
	SDL_FreeSurface(buymenu->mc_button_x3);
	SDL_FreeSurface(buymenu->mc_button_x3_disable);
	ft_lstdel(&buymenu->all_guns, &dummy_free_er);
}

void	buymenu_new(SDL_Window *window, SDL_Renderer *renderer, SDL_Surface *surface, t_inv *inv)
{
	ft_putstr("we are in the buymenu\n");

	t_buymenu *buymenu;
	SDL_Texture *texture;
	t_bui_libui *libui;
	int ww;
	int wh;
	SDL_Surface *mukamas;
	t_bui_window *win;
	SDL_Surface *s;
	
	SDL_GetWindowSize(window, &ww, &wh);
	mukamas = create_surface(ww, wh);
	libui = bui_new_libui();
	win = bui_new_window_from_window(libui, window, mukamas);
	win->update = 0;
	win->free_window_surface = 1;
	buymenu = buymenu_init();
	s = create_surface(ww, wh);
//	SDL_BlitSurface(surface , NULL, s, NULL);
	texture = SDL_CreateTextureFromSurface(renderer, win->active_surface);

	ft_putstr("starting init\n");
	menu_init(win, buymenu);
	exit_button_init(buymenu);
	currency_init(buymenu, inv);
	weapon_stats_init(buymenu);
	player_stats_init(buymenu);
	weapon_menu_init(buymenu, inv);
	weapon_upgrades_init(buymenu);
	player_menu_init(buymenu);
	ft_putstr("inits done\n");

	give_weapon(buymenu, inv, WEAPON_SHOTGUN);
	while (libui->run)
	{
		bui_event_handler_new(libui);
//		SDL_BlitSurface(s, NULL, win->active_surface, NULL);
/////////////////// Bedugging buttons
		if (key_pressed(libui, KEY_A))
			inv->dosh -= 10;
		if (key_pressed(libui, KEY_D))
			inv->dosh += 10;
		if (key_pressed(libui, KEY_S)) // Remember that this doesnt remove from the owned guns list.
		{
			inv->weapon[WEAPON_GUN].own = 0;
			inv->weapon[WEAPON_SHOTGUN].own = 0;
			inv->weapon[WEAPON_MINIGUN].own = 0;
		}
////////////////// END BUGGIN
		if (bui_button(buymenu->exit_button))
			libui->run = 0;
		weapon_buying_events(buymenu, inv);
		weapon_stat_events(buymenu, inv);
		weapon_upgrading_events(buymenu, inv);
		player_stat_events(buymenu, inv);
		player_upgrading_events(buymenu, inv);
		bui_render_new(libui);
		SDL_UpdateTexture(texture, NULL, win->active_surface->pixels, win->active_surface->pitch);
		SDL_RenderCopy(renderer, texture, NULL, NULL);
		SDL_RenderPresent(renderer);
	}
	SDL_DestroyTexture(texture);
	buymenu_quit(buymenu);
	bui_libui_quit(libui);
}
