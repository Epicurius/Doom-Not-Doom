/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Niklas Neronin <niklas.neronin@gmail.com>
 */

#include "bxpm.h"

static void	write_bxpm2_header(t_bxpm *bxpm, int fd, char *name)
{
	ft_dprintf(fd, "static int\t\tbxpm_info_%s[5] = {\n%d,%d,%d,%d,%d};\n",
		name, bxpm->w, bxpm->h, bxpm->clr_nb, bxpm->pix_nb, bxpm->bpp);
}

static void	write_bxpm2_colors(t_bxpm *bxpm, int fd, char *name)
{
	int	i;

	i = -1;
	ft_dprintf(fd, "static uint32_t\t\tbxpm_colors_%s[%d] = {\n",
		name, bxpm->clr_nb);
	while (++i < bxpm->clr_nb)
	{
		if (i + 1 == bxpm->clr_nb)
			ft_dprintf(fd, "0x%8x};\n", bxpm->clr[i]);
		else if (i % 7 == 6)
			ft_dprintf(fd, "0x%8x,\n", bxpm->clr[i]);
		else
			ft_dprintf(fd, "0x%8x,", bxpm->clr[i]);
	}
}

static void	write_bxpm2_pixels(t_bxpm *bxpm, int fd, char *name)
{
	int	i;

	i = -1;
	ft_dprintf(fd, "static unsigned short\tbxpm_pixels_%s[%d] = {\n",
		name, bxpm->pix_nb);
	while (++i < bxpm->pix_nb)
	{
		if (i + 1 == bxpm->pix_nb)
			ft_dprintf(fd, "%d};", bxpm->pix[i]);
		else if ((i % bxpm->w) == (bxpm->w - 1))
			ft_dprintf(fd, "%d,\n", bxpm->pix[i]);
		else
			ft_dprintf(fd, "%d,", bxpm->pix[i]);
	}
}

void	write_bxpm2(t_bxpm *bxpm, char *path, char *name)
{
	int		fd;
	char	*full;

	full = ft_strjoin(path, ".bxpm2");
	fd = creat(full, S_IRUSR | S_IWUSR);
	write_bxpm2_header(bxpm, fd, name);
	write_bxpm2_colors(bxpm, fd, name);
	write_bxpm2_pixels(bxpm, fd, name);
	free(full);
	close(fd);
}
