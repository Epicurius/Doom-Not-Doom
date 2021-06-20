/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bxpm_weapons2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/19 17:00:26 by nneronin          #+#    #+#             */
/*   Updated: 2021/06/20 11:12:41 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	load_kar2(t_weapon *weapon)
{
	if (!read_bxpm(&weapon->bxpm[21], BXPM_PATH"kar-21.bxpm")
		|| !read_bxpm(&weapon->bxpm[22], BXPM_PATH"kar-22.bxpm")
		|| !read_bxpm(&weapon->bxpm[23], BXPM_PATH"kar-23.bxpm")
		|| !read_bxpm(&weapon->bxpm[24], BXPM_PATH"kar-24.bxpm")
		|| !read_bxpm(&weapon->bxpm[25], BXPM_PATH"kar-25.bxpm")
		|| !read_bxpm(&weapon->bxpm[26], BXPM_PATH"kar-26.bxpm")
		|| !read_bxpm(&weapon->bxpm[27], BXPM_PATH"kar-27.bxpm")
		|| !read_bxpm(&weapon->bxpm[28], BXPM_PATH"kar-28.bxpm")
		|| !read_bxpm(&weapon->bxpm[29], BXPM_PATH"kar-29.bxpm")
		|| !read_bxpm(&weapon->bxpm[30], BXPM_PATH"kar-30.bxpm")
		|| !read_bxpm(&weapon->bxpm[31], BXPM_PATH"kar-31.bxpm")
		|| !read_bxpm(&weapon->bxpm[32], BXPM_PATH"kar-32.bxpm")
		|| !read_bxpm(&weapon->bxpm[33], BXPM_PATH"kar-33.bxpm")
		|| !read_bxpm(&weapon->bxpm[34], BXPM_PATH"kar-34.bxpm")
		|| !read_bxpm(&weapon->bxpm[35], BXPM_PATH"kar-35.bxpm")
		|| !read_bxpm(&weapon->bxpm[36], BXPM_PATH"kar-36.bxpm")
		|| !read_bxpm(&weapon->bxpm[37], BXPM_PATH"kar-37.bxpm"))
		error_msg("Loading bxpm. (weapons)\n");
}

void	load_kar(t_weapon *weapon)
{
	if (!read_bxpm(&weapon->bxpm[0], BXPM_PATH"kar-0.bxpm")
		|| !read_bxpm(&weapon->bxpm[1], BXPM_PATH"kar-1.bxpm")
		|| !read_bxpm(&weapon->bxpm[2], BXPM_PATH"kar-2.bxpm")
		|| !read_bxpm(&weapon->bxpm[3], BXPM_PATH"kar-3.bxpm")
		|| !read_bxpm(&weapon->bxpm[4], BXPM_PATH"kar-4.bxpm")
		|| !read_bxpm(&weapon->bxpm[5], BXPM_PATH"kar-5.bxpm")
		|| !read_bxpm(&weapon->bxpm[6], BXPM_PATH"kar-6.bxpm")
		|| !read_bxpm(&weapon->bxpm[7], BXPM_PATH"kar-7.bxpm")
		|| !read_bxpm(&weapon->bxpm[8], BXPM_PATH"kar-8.bxpm")
		|| !read_bxpm(&weapon->bxpm[9], BXPM_PATH"kar-9.bxpm")
		|| !read_bxpm(&weapon->bxpm[10], BXPM_PATH"kar-10.bxpm")
		|| !read_bxpm(&weapon->bxpm[11], BXPM_PATH"kar-11.bxpm")
		|| !read_bxpm(&weapon->bxpm[12], BXPM_PATH"kar-12.bxpm")
		|| !read_bxpm(&weapon->bxpm[13], BXPM_PATH"kar-13.bxpm")
		|| !read_bxpm(&weapon->bxpm[14], BXPM_PATH"kar-14.bxpm")
		|| !read_bxpm(&weapon->bxpm[15], BXPM_PATH"kar-15.bxpm")
		|| !read_bxpm(&weapon->bxpm[16], BXPM_PATH"kar-16.bxpm")
		|| !read_bxpm(&weapon->bxpm[17], BXPM_PATH"kar-17.bxpm")
		|| !read_bxpm(&weapon->bxpm[18], BXPM_PATH"kar-18.bxpm")
		|| !read_bxpm(&weapon->bxpm[19], BXPM_PATH"kar-19.bxpm")
		|| !read_bxpm(&weapon->bxpm[20], BXPM_PATH"kar-20.bxpm"))
		error_msg("Loading bxpm. (weapons)\n");
	load_kar2(weapon);
}

void	load_pump(t_weapon *weapon)
{
	if (!read_bxpm(&weapon->bxpm[0], BXPM_PATH"pump-0.bxpm")
		|| !read_bxpm(&weapon->bxpm[1], BXPM_PATH"pump-1.bxpm")
		|| !read_bxpm(&weapon->bxpm[2], BXPM_PATH"pump-2.bxpm")
		|| !read_bxpm(&weapon->bxpm[3], BXPM_PATH"pump-3.bxpm")
		|| !read_bxpm(&weapon->bxpm[4], BXPM_PATH"pump-4.bxpm")
		|| !read_bxpm(&weapon->bxpm[5], BXPM_PATH"pump-5.bxpm")
		|| !read_bxpm(&weapon->bxpm[6], BXPM_PATH"pump-6.bxpm")
		|| !read_bxpm(&weapon->bxpm[7], BXPM_PATH"pump-7.bxpm")
		|| !read_bxpm(&weapon->bxpm[8], BXPM_PATH"pump-8.bxpm"))
		error_msg("Loading bxpm. (weapons)\n");
}
