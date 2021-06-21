/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bxpm_weapons1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/19 17:00:26 by nneronin          #+#    #+#             */
/*   Updated: 2021/06/21 13:09:09 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	bxpm_shotgun(t_weapon *weapon)
{
	if (!read_bxpm(&weapon->bxpm[0], BXPM_PATH"shotgun-0.bxpm")
		|| !read_bxpm(&weapon->bxpm[1], BXPM_PATH"shotgun-1.bxpm")
		|| !read_bxpm(&weapon->bxpm[2], BXPM_PATH"shotgun-2.bxpm")
		|| !read_bxpm(&weapon->bxpm[3], BXPM_PATH"shotgun-3.bxpm")
		|| !read_bxpm(&weapon->bxpm[4], BXPM_PATH"shotgun-4.bxpm")
		|| !read_bxpm(&weapon->bxpm[5], BXPM_PATH"shotgun-5.bxpm")
		|| !read_bxpm(&weapon->bxpm[6], BXPM_PATH"shotgun-6.bxpm")
		|| !read_bxpm(&weapon->bxpm[7], BXPM_PATH"shotgun-7.bxpm")
		|| !read_bxpm(&weapon->bxpm[8], BXPM_PATH"shotgun-8.bxpm")
		|| !read_bxpm(&weapon->bxpm[9], BXPM_PATH"shotgun-9.bxpm")
		|| !read_bxpm(&weapon->bxpm[10], BXPM_PATH"shotgun-10.bxpm")
		|| !read_bxpm(&weapon->bxpm[11], BXPM_PATH"shotgun-11.bxpm")
		|| !read_bxpm(&weapon->bxpm[12], BXPM_PATH"shotgun-12.bxpm")
		|| !read_bxpm(&weapon->bxpm[13], BXPM_PATH"shotgun-13.bxpm"))
		error_msg("Loading bxpm. (weapons)\n");
}

void	bxpm_glock(t_weapon *weapon)
{
	if (!read_bxpm(&weapon->bxpm[0], BXPM_PATH"glock-0.bxpm")
		|| !read_bxpm(&weapon->bxpm[1], BXPM_PATH"glock-1.bxpm")
		|| !read_bxpm(&weapon->bxpm[2], BXPM_PATH"glock-2.bxpm")
		|| !read_bxpm(&weapon->bxpm[3], BXPM_PATH"glock-3.bxpm")
		|| !read_bxpm(&weapon->bxpm[4], BXPM_PATH"glock-4.bxpm")
		|| !read_bxpm(&weapon->bxpm[5], BXPM_PATH"glock-5.bxpm"))
		error_msg("Loading bxpm. (weapons)\n");
}

void	bxpm_minigun(t_weapon *weapon)
{
	if (!read_bxpm(&weapon->bxpm[0], BXPM_PATH"minigun-0.bxpm")
		|| !read_bxpm(&weapon->bxpm[1], BXPM_PATH"minigun-1.bxpm")
		|| !read_bxpm(&weapon->bxpm[2], BXPM_PATH"minigun-2.bxpm")
		|| !read_bxpm(&weapon->bxpm[3], BXPM_PATH"minigun-3.bxpm")
		|| !read_bxpm(&weapon->bxpm[4], BXPM_PATH"minigun-4.bxpm")
		|| !read_bxpm(&weapon->bxpm[5], BXPM_PATH"minigun-5.bxpm"))
		error_msg("Loading bxpm. (weapons)\n");
}
