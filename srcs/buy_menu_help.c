/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buy_menu_help.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalmi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 15:38:40 by jsalmi            #+#    #+#             */
/*   Updated: 2021/07/28 15:38:42 by jsalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buymenu.h"

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
