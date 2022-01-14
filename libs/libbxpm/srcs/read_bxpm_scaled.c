/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_bxpm_scaled.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 12:50:40 by nneronin          #+#    #+#             */
/*   Updated: 2022/01/02 13:51:20 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bxpm.h"

static int	read_bxpm_header_scaled(FILE *fd, t_bxpm *bxpm)
{
	unsigned char	header[20];

	if (fread(header, 20, 1, fd) != 1)
		return (0);
	bxpm->w = read_int32(&header[0]);
	bxpm->h = read_int32(&header[4]);
	bxpm->clr_nb = read_int32(&header[8]);
	bxpm->pix_nb = read_int32(&header[12]);
	bxpm->bpp = read_int32(&header[16]);
	bxpm->clr = malloc(sizeof(uint32_t) * bxpm->clr_nb);
	if (!bxpm->clr)
		return (0);
	return (1);
}

static inline void	copy_column(unsigned short *pix_w, t_bxpm *bxpm,
	int dy, int w)
{
	int				inc;
	int				pos;
	int				dx;
	int				sx;
	unsigned short	*pix;

	pix = &bxpm->pix[dy * w];
	pos = 0x10000;
	inc = (bxpm->w << 16) / w;
	sx = 0;
	dx = 0;
	while (dx < w)
	{
		pix[dx] = pix_w[sx];
		while (pos > 0x10000L)
		{
			if (sx < bxpm->w - 1)
				sx++;
			pos -= 0x10000L;
		}
		pos += inc;
		dx++;
	}
}

static inline void	bxpm_scale(FILE *fd, t_bxpm *bxpm, int w, int h)
{
	int				pos;
	int				inc;
	int				dy;
	int				sy;
	unsigned short	*pix_w;

	pix_w = malloc(2 * bxpm->w);
	pos = 0x10000;
	inc = (bxpm->h << 16) / h;
	sy = 0;
	dy = 0;
	fread(pix_w, bxpm->w, 2, fd);
	while (dy < h)
	{
		copy_column(pix_w, bxpm, dy, w);
		while (pos > 0x10000L)
		{
			if (++sy < bxpm->h)
				fread(pix_w, bxpm->w, 2, fd);
			pos -= 0x10000L;
		}
		pos += inc;
		dy++;
	}
	free(pix_w);
}

int	read_bxpm_scaled(t_bxpm *bxpm, char *file, float scale)
{
	FILE	*fd;
	int		w;
	int		h;

	fd = fopen(file, "rb");
	if (fd == NULL)
		return (0);
	if (!read_bxpm_header_scaled(fd, bxpm))
		return (0);
	w = bxpm->w * scale;
	h = bxpm->h * scale;
	w -= w % 10;
	h -= h % 10;
	bxpm->pix = malloc(sizeof(unsigned short) * w * h);
	if (!bxpm->pix)
		return (0);
	if (fread(bxpm->clr, bxpm->clr_nb, 4, fd) != 4)
		return (0);
	bxpm_scale(fd, bxpm, w, h);
	bxpm->w = w;
	bxpm->h = h;
	bxpm->pix_nb = w * h;
	fclose(fd);
	return (1);
}

int	multithread_read_bxpm_scaled(void *arg)
{
	if (read_bxpm_scaled(((t_thread_bxpm *)arg)->bxpm,
			((t_thread_bxpm *)arg)->path, ((t_thread_bxpm *)arg)->scale))
		return (1);
	ft_printf("Could not read %s\n", ((t_thread_bxpm *)arg)->path);
	return (0);
}
