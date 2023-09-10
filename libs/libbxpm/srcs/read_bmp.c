/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Niklas Neronin <niklas.neronin@gmail.com>
 */

#include "bxpm.h"

static int	bmp_header(FILE *fd, t_header *header)
{
	if (fread(&header->type, 1, 2, fd) != 2
		|| fread(&header->size, 1, 4, fd) != 4
		|| fread(&header->reserved1, 1, 2, fd) != 2
		|| fread(&header->reserved2, 1, 2, fd) != 2
		|| fread(&header->offset, 1, 4, fd) != 4
		|| fread(&header->header_size, 1, 4, fd) != 4
		|| fread(&header->width_px, 1, 4, fd) != 4
		|| fread(&header->height_px, 1, 4, fd) != 4
		|| fread(&header->num_planes, 1, 2, fd) != 2
		|| fread(&header->bits_per_pixel, 1, 2, fd) != 2
		|| fread(&header->compression, 1, 4, fd) != 4
		|| fread(&header->image_bytes, 1, 4, fd) != 4
		|| fread(&header->x_pix_per_m, 1, 4, fd) != 4
		|| fread(&header->y_pix_per_m, 1, 4, fd) != 4
		|| fread(&header->num_colors, 1, 4, fd) != 4
		|| fread(&header->import_colors, 1, 4, fd) != 4)
		return (0);
	return (1);
}

int	read_bmp(t_bmp *bmp, char *file)
{
	FILE	*fd;

	fd = fopen(file, "rb");
	if (fd == NULL)
		return (0);
	if (!bmp_header(fd, &bmp->header))
		return (0);
	bmp->data = malloc(bmp->header.image_bytes);
	if (!bmp->data)
		return (0);
	if (fread(bmp->data, 1, bmp->header.image_bytes, fd)
		!= bmp->header.image_bytes)
		return (0);
	fclose(fd);
	return (1);
}
