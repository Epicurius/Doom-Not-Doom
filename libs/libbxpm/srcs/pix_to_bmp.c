/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Niklas Neronin <niklas.neronin@gmail.com>
 */

#include "bxpm.h"

static void	get_bmp_header(t_header *header, int w, int h, int bpp)
{
	header->type = 0x4D42;
	header->size = w * h * bpp + 54;
	header->reserved1 = 0;
	header->reserved2 = 0;
	header->offset = 54;
	header->header_size = 40;
	header->width_px = w;
	header->height_px = h;
	header->num_planes = 1;
	header->bits_per_pixel = bpp * 8;
	header->compression = 0;
	header->image_bytes = w * h * bpp;
	header->x_pix_per_m = 0;
	header->y_pix_per_m = 0;
	header->num_colors = 1;
	header->import_colors = 0;
}

static void	pixel_clr(uint32_t clr, unsigned char *data, int bpp)
{
	if (bpp == 4)
	{
		data[0] = clr;
		data[1] = clr >> 8;
		data[2] = clr >> 16;
		data[3] = clr >> 24;
	}
	else if (bpp == 3)
	{
		data[0] = clr;
		data[1] = clr >> 8;
		data[2] = clr >> 16;
	}
}

static void	get_bmp_pixel_data(t_bmp *bmp, void *pixels, int bpp)
{
	int				x;
	int				y;
	unsigned char	*pix;

	bmp->data = malloc(bmp->header.image_bytes + 1);
	pix = &bmp->data[0];
	y = bmp->header.height_px;
	while (y--)
	{
		x = -1;
		while (++x < bmp->header.width_px)
		{
			pixel_clr(((uint32_t *)pixels)[y * bmp->header.width_px + x],
				pix, bpp);
			pix += bpp;
		}
	}
}

t_bmp	*pix_to_bmp(int w, int h, int bpp, void *pixels)
{
	t_bmp	*bmp;

	if (bpp == 3 || bpp == 4)
	{
		bmp = malloc(sizeof(t_bmp));
		get_bmp_header(&bmp->header, w, h, bpp);
		get_bmp_pixel_data(bmp, pixels, bpp);
		return (bmp);
	}
	write(1, "[ERROR] bpp\n", 12);
	return (NULL);
}
