/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 11:32:08 by nneronin          #+#    #+#             */
/*   Updated: 2021/05/05 13:21:42 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

#include "../resources/BXPM2/bh.bxpm2"
#include "../resources/BXPM2/vent.bxpm2"
#include "../resources/BXPM2/wood.bxpm2"
#include "../resources/BXPM2/bars.bxpm2"

#include "../resources/BXPM2/land0.bxpm2"
#include "../resources/BXPM2/land1.bxpm2"
#include "../resources/BXPM2/land2.bxpm2"
#include "../resources/BXPM2/land3.bxpm2"
#include "../resources/BXPM2/land4.bxpm2"
#include "../resources/BXPM2/land5.bxpm2"

#include "../resources/BXPM2/space0.bxpm2"
#include "../resources/BXPM2/space1.bxpm2"
#include "../resources/BXPM2/space2.bxpm2"
#include "../resources/BXPM2/space3.bxpm2"
#include "../resources/BXPM2/space4.bxpm2"
#include "../resources/BXPM2/space5.bxpm2"

#include "../resources/BXPM2/alfred.bxpm2"
#include "../resources/BXPM2/spooky.bxpm2"

static void	load_mtx(t_bxpm *mtx)
{

	mtx[0].w		= bxpm_info_bh[0];
	mtx[0].h		= bxpm_info_bh[1];
	mtx[0].clr_nb	= bxpm_info_bh[2];
	mtx[0].pix_nb	= bxpm_info_bh[3];
	mtx[0].clr		= bxpm_colors_bh;
	mtx[0].pix		= bxpm_pixels_bh;

	mtx[1].w		= bxpm_info_vent[0];
	mtx[1].h		= bxpm_info_vent[1];
	mtx[1].clr_nb	= bxpm_info_vent[2];
	mtx[1].pix_nb	= bxpm_info_vent[3];
	mtx[1].clr		= bxpm_colors_vent;
	mtx[1].pix		= bxpm_pixels_vent;	

	mtx[2].w		= bxpm_info_wood[0];
	mtx[2].h		= bxpm_info_wood[1];
	mtx[2].clr_nb	= bxpm_info_wood[2];
	mtx[2].pix_nb	= bxpm_info_wood[3];
	mtx[2].clr		= bxpm_colors_wood;
	mtx[2].pix		= bxpm_pixels_wood;

	mtx[3].w		= bxpm_info_bars[0];
	mtx[3].h		= bxpm_info_bars[1];
	mtx[3].clr_nb	= bxpm_info_bars[2];
	mtx[3].pix_nb	= bxpm_info_bars[3];
	mtx[3].clr		= bxpm_colors_bars;
	mtx[3].pix		= bxpm_pixels_bars;
}

static void	load_stx(t_bxpm *stx)
{	
	stx[0].w		= bxpm_info_space4[0];
	stx[0].h		= bxpm_info_space4[1];
	stx[0].clr_nb	= bxpm_info_space4[2];
	stx[0].pix_nb	= bxpm_info_space4[3];
	stx[0].clr		= bxpm_colors_space4;
	stx[0].pix		= bxpm_pixels_space4;

	stx[1].w		= bxpm_info_space1[0];
	stx[1].h		= bxpm_info_space1[1];
	stx[1].clr_nb	= bxpm_info_space1[2];
	stx[1].pix_nb	= bxpm_info_space1[3];
	stx[1].clr		= bxpm_colors_space1;
	stx[1].pix		= bxpm_pixels_space1;

	stx[2].w		= bxpm_info_space2[0];
	stx[2].h		= bxpm_info_space2[1];
	stx[2].clr_nb	= bxpm_info_space2[2];
	stx[2].pix_nb	= bxpm_info_space2[3];
	stx[2].clr		= bxpm_colors_space2;
	stx[2].pix		= bxpm_pixels_space2;

	stx[3].w		= bxpm_info_space3[0];
	stx[3].h		= bxpm_info_space3[1];
	stx[3].clr_nb	= bxpm_info_space3[2];
	stx[3].pix_nb	= bxpm_info_space3[3];
	stx[3].clr		= bxpm_colors_space3;
	stx[3].pix		= bxpm_pixels_space3;

	stx[4].w		= bxpm_info_space0[0];
	stx[4].h		= bxpm_info_space0[1];
	stx[4].clr_nb	= bxpm_info_space0[2];
	stx[4].pix_nb	= bxpm_info_space0[3];
	stx[4].clr		= bxpm_colors_space0;
	stx[4].pix		= bxpm_pixels_space0;

	stx[5].w		= bxpm_info_space5[0];
	stx[5].h		= bxpm_info_space5[1];
	stx[5].clr_nb	= bxpm_info_space5[2];
	stx[5].pix_nb	= bxpm_info_space5[3];
	stx[5].clr		= bxpm_colors_space5;
	stx[5].pix		= bxpm_pixels_space5;
	
	stx[6].w		= bxpm_info_land4[0];
	stx[6].h		= bxpm_info_land4[1];
	stx[6].clr_nb	= bxpm_info_land4[2];
	stx[6].pix_nb	= bxpm_info_land4[3];
	stx[6].clr		= bxpm_colors_land4;
	stx[6].pix		= bxpm_pixels_land4;

	stx[7].w		= bxpm_info_land1[0];
	stx[7].h		= bxpm_info_land1[1];
	stx[7].clr_nb	= bxpm_info_land1[2];
	stx[7].pix_nb	= bxpm_info_land1[3];
	stx[7].clr		= bxpm_colors_land1;
	stx[7].pix		= bxpm_pixels_land1;

	stx[8].w		= bxpm_info_land2[0];
	stx[8].h		= bxpm_info_land2[1];
	stx[8].clr_nb	= bxpm_info_land2[2];
	stx[8].pix_nb	= bxpm_info_land2[3];
	stx[8].clr		= bxpm_colors_land2;
	stx[8].pix		= bxpm_pixels_land2;

	stx[9].w		= bxpm_info_land3[0];
	stx[9].h		= bxpm_info_land3[1];
	stx[9].clr_nb	= bxpm_info_land3[2];
	stx[9].pix_nb	= bxpm_info_land3[3];
	stx[9].clr		= bxpm_colors_land3;
	stx[9].pix		= bxpm_pixels_land3;

	stx[10].w		= bxpm_info_land0[0];
	stx[10].h		= bxpm_info_land0[1];
	stx[10].clr_nb	= bxpm_info_land0[2];
	stx[10].pix_nb	= bxpm_info_land0[3];
	stx[10].clr		= bxpm_colors_land0;
	stx[10].pix		= bxpm_pixels_land0;

	stx[11].w		= bxpm_info_land5[0];
	stx[11].h		= bxpm_info_land5[1];
	stx[11].clr_nb	= bxpm_info_land5[2];
	stx[11].pix_nb	= bxpm_info_land5[3];
	stx[11].clr		= bxpm_colors_land5;
	stx[11].pix		= bxpm_pixels_land5;
}

static void	load_sheet(t_texture_sheet *sprite)
{
	sprite[0].bxpm.w		= bxpm_info_alfred[0];
	sprite[0].bxpm.h		= bxpm_info_alfred[1];
	sprite[0].bxpm.clr_nb	= bxpm_info_alfred[2];
	sprite[0].bxpm.pix_nb	= bxpm_info_alfred[3];
	sprite[0].bxpm.clr		= bxpm_colors_alfred;
	sprite[0].bxpm.pix		= bxpm_pixels_alfred;

	sprite[1].bxpm.w		= bxpm_info_spooky[0];
	sprite[1].bxpm.h		= bxpm_info_spooky[1];
	sprite[1].bxpm.clr_nb	= bxpm_info_spooky[2];
	sprite[1].bxpm.pix_nb	= bxpm_info_spooky[3];
	sprite[1].bxpm.clr		= bxpm_colors_spooky;
	sprite[1].bxpm.pix		= bxpm_pixels_spooky;
}

void	load_bxpm2(t_doom *doom)
{
	load_mtx(doom->mtx);
	load_stx(doom->stx);
	load_sheet(doom->sheet);
}
