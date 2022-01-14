/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_bxpm.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 14:42:43 by nneronin          #+#    #+#             */
/*   Updated: 2022/01/02 14:59:47 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bxpm.h"
#include <stdio.h>

static void	write_bxpm_header(t_bxpm *bxpm, FILE *fd)
{
	fwrite((const void *)&bxpm->w, 1, sizeof(uint32_t), fd);
	fwrite((const void *)&bxpm->h, 1, sizeof(uint32_t), fd);
	fwrite((const void *)&bxpm->clr_nb, 1, sizeof(uint32_t), fd);
	fwrite((const void *)&bxpm->pix_nb, 1, sizeof(uint32_t), fd);
	fwrite((const void *)&bxpm->bpp, 1, sizeof(uint32_t), fd);
}

static void	write_bxpm_colors(t_bxpm *bxpm, FILE *fd)
{
	unsigned char	*clr;

	clr = (unsigned char *)bxpm->clr;
	fwrite((const void *)clr, bxpm->clr_nb, 4, fd);
}

static void	write_bxpm_pixels(t_bxpm *bxpm, FILE *fd)
{
	unsigned char	*pix;

	pix = (unsigned char *)bxpm->pix;
	fwrite((const void *)pix, bxpm->pix_nb, 2, fd);
}

int	write_bxpm(t_bxpm *bxpm, char *path)
{
	FILE	*fd;

	fd = fopen(path, "wb");
	if (!fd)
		return (0);
	write_bxpm_header(bxpm, fd);
	write_bxpm_colors(bxpm, fd);
	write_bxpm_pixels(bxpm, fd);
	fclose(fd);
	return (1);
}
