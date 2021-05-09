/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   surface_to_bmp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 12:48:53 by nneronin          #+#    #+#             */
/*   Updated: 2021/05/09 14:58:04 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#define NUM_PLANE           1
#define COMPRESSION         0
#define NUM_COLORS          0
#define IMPORTANT_COLORS    0
#define BITS_PER_BYTE       8

typedef struct	s_header
{
	uint16_t	type;
	uint32_t	size;
	uint16_t	reserved1;
	uint16_t	reserved2;
	uint32_t	offset;
	uint32_t	header_size;
	int32_t		width_px;
	int32_t		height_px;
	uint16_t	num_planes;
	uint16_t	bits_per_pixel;
	uint32_t	compression;
	uint32_t	image_size_bytes;
	int32_t		x_res_ppm;
	int32_t		y_res_ppm;
	uint32_t	num_colors;
	uint32_t	important_colors;
}				t_header;

void	get_bpm_header(SDL_Surface *surface, t_header *header, int bpp)
{
	header->type				= 0x4D42;
	header->size				= surface->w * surface->h * bpp + 54;
	header->reserved1			= 0;
	header->reserved2			= 0;
	header->offset				= 54;
	header->header_size			= 40;
	header->width_px			= surface->w;
	header->height_px			= surface->h;
	header->num_planes			= 1;
	header->bits_per_pixel		= bpp * 8;
	header->compression			= 0;
	header->image_size_bytes	= surface->w * surface->h * bpp;
	header->x_res_ppm			= 0;
	header->y_res_ppm			= 0;
	header->num_colors			= 1;
	header->important_colors	= 0;
}

void	write_bpm_header(int fd, SDL_Surface *surface, t_header *header)
{
	write(fd, (const void *)&header->type, sizeof(uint16_t));
	write(fd, (const void *)&header->size, sizeof(uint32_t));
	write(fd, (const void *)&header->reserved1, sizeof(uint16_t));
	write(fd, (const void *)&header->reserved2, sizeof(uint16_t));
	write(fd, (const void *)&header->offset, sizeof(uint32_t));
	write(fd, (const void *)&header->header_size, sizeof(uint32_t));
	write(fd, (const void *)&header->width_px, sizeof(int32_t));
	write(fd, (const void *)&header->height_px, sizeof(int32_t));
	write(fd, (const void *)&header->num_planes, sizeof(uint16_t));
	write(fd, (const void *)&header->bits_per_pixel, sizeof(uint16_t));
	write(fd, (const void *)&header->compression, sizeof(uint32_t));
	write(fd, (const void *)&header->image_size_bytes, sizeof(uint32_t));
	write(fd, (const void *)&header->x_res_ppm, sizeof(int32_t));
	write(fd, (const void *)&header->y_res_ppm, sizeof(int32_t));
	write(fd, (const void *)&header->num_colors, sizeof(uint32_t));
	write(fd, (const void *)&header->important_colors, sizeof(uint32_t));
}

void	write_bpm_pixeldata(int fd, SDL_Surface *surface, int bpp)
{
	int x;
	int y;

	y = surface->h;
	while (y--)
	{
		x = -1;
		while (++x < surface->w)
			write(fd, &((uint32_t*)surface->pixels)[y * surface->w + x], bpp);
	}
}

void	surface_to_bmp(SDL_Surface *surface, char *name, int bytes_per_pixel)
{
	int			fd;
	t_header	header;

	if (bytes_per_pixel!= 3 && bytes_per_pixel != 4)
	{
		write(1, "[ERROR]\tNot supported bpp.\n", 28);
		return ;
	}
	fd = creat(name, S_IRUSR | S_IWUSR);
	get_bpm_header(surface, &header, bytes_per_pixel);
	write_bpm_header(fd, surface, &header);
	write_bpm_pixeldata(fd, surface, bytes_per_pixel);
	close(fd);
}
