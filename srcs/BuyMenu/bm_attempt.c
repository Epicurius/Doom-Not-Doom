/*
 * https://github.com/Epicurius/Doom-Not-Doom
 * 
 * Created: 2021/12/10 17:43:58 nneronin
 * Updated: 2021/12/10 17:46:21 nneronin
 */

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
