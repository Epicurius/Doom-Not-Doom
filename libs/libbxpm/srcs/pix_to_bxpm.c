/*
 * https://github.com/Epicurius/Doom-Not-Doom
 * 
 * Created: 2021/05/01 14:20:47 nneronin
 * Updated: 2022/01/02 13:52:26 nneronin
 */

#include "bxpm.h"

static void	get_bxpm_header(t_bxpm *bxpm, int w, int h, int bpp)
{
	bxpm->w = w;
	bxpm->h = h;
	bxpm->bpp = bpp;
	bxpm->clr_nb = 0;
	bxpm->pix_nb = w * h;
}

static unsigned short	check_clr(t_bxpm *bxpm, uint32_t clr)
{
	unsigned short	i;

	i = -1;
	while (++i < bxpm->clr_nb)
	{
		if (bxpm->clr[i] == clr)
			return (i);
	}
	bxpm->clr_nb += 1;
	bxpm->clr = realloc(bxpm->clr, sizeof(uint32_t) * (bxpm->clr_nb));
	bxpm->clr[bxpm->clr_nb - 1] = clr;
	return (bxpm->clr_nb - 1);
}

static void	get_bxpm_pixel_data(t_bxpm *bxpm, void *pixels)
{
	int	i;

	i = -1;
	bxpm->clr = malloc(sizeof(uint32_t));
	bxpm->pix = malloc(sizeof(unsigned short) * bxpm->pix_nb);
	while (++i < bxpm->pix_nb)
	{
		bxpm->pix[i] = check_clr(bxpm, ((uint32_t *)pixels)[i]);
	}
}

t_bxpm	*pix_to_bxpm(int w, int h, int bpp, void *pixels)
{
	t_bxpm	*bxpm;

	bxpm = ft_memalloc(sizeof(t_bxpm));
	get_bxpm_header(bxpm, w, h, bpp);
	get_bxpm_pixel_data(bxpm, pixels);
	return (bxpm);
}
