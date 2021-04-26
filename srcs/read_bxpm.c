
#include "doom.h"

int32_t	read_int32(unsigned char *str, int index)
{
	int32_t		res;

	res = str[index + 3] << 24
		| str[index + 2] << 16
		| str[index + 1] << 8
		| str[index];
	return (res);
}

uint32_t	read_color32(unsigned char *str, int index)
{
	uint32_t	res;

	res = str[index + 3] << 24
		| str[index + 2] << 16
		| str[index + 1] << 8
		| str[index + 0];
	return (res);
}

uint32_t	read_color24(unsigned char *str, int i)
{
	uint32_t	res;

	res = 255 << 24
		| str[i + 2] << 16
		| str[i + 1] << 8
		| str[i + 0] << 0;
	return (res);
}

int32_t	read_int16(unsigned char *str, int i)
{
	int32_t res;

	res = str[i + 1] << 8
		| str[i];
	return (res);
}

t_bxpm read_bxpm(char *file)
{
	int i;
	int fd;
	t_bxpm *bxpm;

	bxpm = malloc(sizeof(t_bxpm));
	fd = open(file, O_RDONLY);

	unsigned char header[20];
	read(fd, header, 20);
	bxpm->w = read_int32(header, 0);
	bxpm->h = read_int32(header, 4);
	bxpm->clr_nb = read_int32(header, 8);
	bxpm->pix_nb = read_int32(header, 12);
	bxpm->bpp = read_int32(header, 16);
	bxpm->clr = malloc(sizeof(uint32_t) * bxpm->clr_nb);
	bxpm->pix = malloc(sizeof(unsigned short) * bxpm->pix_nb);

	unsigned char clr[bxpm->clr_nb * 4];
	read(fd, clr, bxpm->clr_nb * 4);
	i = 0;
	int x = 0;
	while (i < bxpm->clr_nb * 4)
	{
		bxpm->clr[x] = read_color32(clr, i);
		i += 4;
		x++;
	}

	unsigned char pix[bxpm->pix_nb * 2];
	read(fd, pix, bxpm->pix_nb * 2);
	i = 0;
	x = 0;
	while (i < bxpm->pix_nb * 2)
	{
		bxpm->pix[x] = read_int16(pix, i);
		i += 2;
		x++;
	}
	close(fd);
	return (*bxpm);

}
