/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_bxpm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 13:20:28 by nneronin          #+#    #+#             */
/*   Updated: 2022/01/02 13:21:59 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bxpm.h"

static int	read_bxpm_header(FILE *fd, t_bxpm *bxpm)
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
	bxpm->pix = malloc(sizeof(unsigned short) * bxpm->pix_nb);
	if (!bxpm->pix)
		return (0);
	return (1);
}

int	read_bxpm(t_bxpm *bxpm, char *file)
{
	FILE	*fd;

	fd = fopen(file, "rb");
	if (fd == NULL)
		return (0);
	if (!read_bxpm_header(fd, bxpm))
		return (0);
	if (fread(bxpm->clr, bxpm->clr_nb, 4, fd) != 4)
		return (0);
	if (fread(bxpm->pix, bxpm->pix_nb, 2, fd) != 2)
		return (0);
	fclose(fd);
	return (1);
}

int	multithread_read_bxpm(void *arg)
{
	if (read_bxpm(((t_thread_bxpm *)arg)->bxpm, ((t_thread_bxpm *)arg)->path))
		return (1);
	ft_printf("Could not read %s\n", ((t_thread_bxpm *)arg)->path);
	return (0);
}
