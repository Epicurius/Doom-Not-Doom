/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Niklas Neronin <niklas.neronin@gmail.com>
 */

#include "bxpm.h"

static unsigned short	check_clr(t_bxpm *bxpm, uint32_t clr, uint32_t *buf)
{
	unsigned short	i;

	i = -1;
	while (++i < bxpm->clr_nb)
	{
		if (buf[i] == clr)
			return (i);
	}
	buf[bxpm->clr_nb] = clr;
	if (++bxpm->clr_nb > 65534)
		ft_printf("[ERROR] Color amount:[%d / 65534]\n", bxpm->clr_nb);
	return (bxpm->clr_nb - 1);
}

static void	bxpm_data(t_bxpm *bxpm, t_bmp *bmp, int x, int y)
{
	unsigned short	*pix;
	int				bpc;
	int				pitch;
	int				padding;
	uint32_t		clr[65535];

	bpc = bmp->header.bits_per_pixel >> 3;
	padding = (4 - (bmp->header.width_px * bpc) % 4) % 4;
	pitch = bmp->header.width_px * bpc + padding;
	pix = &bxpm->pix[0];
	y = bmp->header.height_px;
	while (y > 0)
	{
		y -= 1;
		x = 0;
		while (x < pitch - padding)
		{
			*pix++ = check_clr(bxpm,
					bpp_clr(&bmp->data[y * pitch + x], bpc), clr);
			x += bpc;
		}
	}
	bxpm->clr = malloc(sizeof(uint32_t) * bxpm->clr_nb);
	ft_memcpy(bxpm->clr, clr, bxpm->clr_nb * 4);
}

int	bmp_to_bxpm(t_bmp *bmp, t_bxpm *bxpm)
{
	bxpm->w = bmp->header.width_px;
	bxpm->h = bmp->header.height_px;
	bxpm->bpp = bmp->header.bits_per_pixel;
	bxpm->clr_nb = 0;
	bxpm->pix_nb = bxpm->w * bxpm->h;
	bxpm->pix = malloc(sizeof(unsigned short) * bxpm->pix_nb);
	bxpm_data(bxpm, bmp, 0, 0);
	return (1);
}
