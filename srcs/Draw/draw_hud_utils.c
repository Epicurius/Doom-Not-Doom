/*
 * https://github.com/Epicurius/Doom-Not-Doom
 * 
 * Created: 2021/05/19 18:12:37 nneronin
 * Updated: 2022/01/18 13:11:25 Niklas Neronin
 */

#include "doom.h"

/*
 *	Draw Heath icon and amount.
 *	blit_bxpm_scaled(doom->surface,
 *	rect_xywh(10 + surf->w + 10, dstr->y, doom->itx[0].w /
 *		(1080 / doom->surface->h), doom->itx[0].h / (1080 / doom->surface->h)),
 *	&doom->itx[0],
 *	rect_xywh(0, 0, doom->itx[0].w, doom->itx[0].h));
 */
void	hud_health(t_doom *doom, SDL_Rect *dstr)
{
	char		*str;
	SDL_Surface	*surf;

	str = ft_itoa(doom->player.health);
	surf = TTF_RenderText_Blended(doom->font.amaz, str, doom->time.color);
	if (!surf)
		LG_ERROR("TTF_RenderText_Blended error: %s.", TTF_GetError());
	dstr->y = dstr->y - surf->h;
	dstr->w = surf->w;
	dstr->h = surf->h;
	SDL_BlitSurface(surf, NULL, doom->surface, dstr);
	blit_bxpm(doom->surface, &doom->itx[0], 10 + surf->w + 10, dstr->y);
	free(str);
	SDL_FreeSurface(surf);
}

/*
 *	Draw Armour icon and amount.
 */
void	hud_armour(t_doom *doom, SDL_Rect *dstr)
{
	char		*str;
	SDL_Surface	*surf;

	str = ft_itoa(doom->player.armour);
	surf = TTF_RenderText_Blended(doom->font.amaz, str, doom->time.color);
	if (!surf)
		LG_ERROR("TTF_RenderText_Blended error: %s.", TTF_GetError());
	dstr->y = dstr->y - surf->h;
	dstr->w = surf->w;
	dstr->h = surf->h;
	SDL_BlitSurface(surf, NULL, doom->surface, dstr);
	blit_bxpm(doom->surface, &doom->itx[1], 10 + surf->w + 10, dstr->y);
	free(str);
	SDL_FreeSurface(surf);
}

/*
 *	Draw total ammo icon and amount.
 */
void	hud_curr_ammo(t_doom *doom, SDL_Rect *dstr)
{
	char		*str;
	SDL_Surface	*surf;

	str = ft_itoa(doom->weapon[doom->player.equipped].cur_ammo);
	surf = TTF_RenderText_Blended(doom->font.amaz, str, doom->time.color);
	if (!surf)
		LG_ERROR("TTF_RenderText_Blended error: %s.", TTF_GetError());
	dstr->y = dstr->y - surf->h;
	dstr->w = surf->w;
	dstr->h = surf->h;
	SDL_BlitSurface(surf, NULL, doom->surface, dstr);
	blit_bxpm(doom->surface, &doom->itx[2], 10 + surf->w + 10, dstr->y);
	free(str);
	SDL_FreeSurface(surf);
}

/*
 *	Draw ammo in magazine icon and amount.
 */
void	hud_mag_ammo(t_doom *doom, SDL_Rect *dstr)
{
	char		*str;
	SDL_Surface	*surf;

	str = ft_itoa(doom->weapon[doom->player.equipped].mag_ammo);
	surf = TTF_RenderText_Blended(doom->font.amaz, str, doom->time.color);
	if (!surf)
		LG_ERROR("TTF_RenderText_Blended error: %s.", TTF_GetError());
	dstr->y = dstr->y - surf->h;
	dstr->w = surf->w;
	dstr->h = surf->h;
	SDL_BlitSurface(surf, NULL, doom->surface, dstr);
	blit_bxpm(doom->surface, &doom->itx[3], 10 + surf->w + 10, dstr->y);
	free(str);
	SDL_FreeSurface(surf);
}

/*
 *	Draw Dosh (Money) icon and amount.
 */
void	hud_dosh(t_doom *doom, SDL_Rect *dstr)
{
	char		*str;
	SDL_Surface	*surf;

	str = ft_itoa(doom->inv.dosh);
	surf = TTF_RenderText_Blended(doom->font.amaz, str, doom->time.color);
	if (!surf)
		LG_ERROR("TTF_RenderText_Blended error: %s.", TTF_GetError());
	dstr->y = dstr->y - surf->h;
	dstr->w = surf->w;
	dstr->h = surf->h;
	SDL_BlitSurface(surf, NULL, doom->surface, dstr);
	blit_bxpm(doom->surface, &doom->itx[4], 10 + surf->w + 10, dstr->y);
	free(str);
	SDL_FreeSurface(surf);
}
