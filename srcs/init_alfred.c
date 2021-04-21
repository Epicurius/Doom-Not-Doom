
#include "doom.h"
#include "../resources/bxpm/alfred.bxpm"

void	init_alfred_nb(t_texture_sheet *sprite)
{
	sprite->nb[IDLE][FRAMES] = 1;
	sprite->nb[IDLE][ANGLES] = 8;
	sprite->nb[MOVE][FRAMES] = 1;
	sprite->nb[MOVE][ANGLES] = 8;
	sprite->nb[ATTACK][FRAMES] = 6;
	sprite->nb[ATTACK][ANGLES] = 1;
	sprite->nb[DEATH][FRAMES] = 6;
	sprite->nb[DEATH][ANGLES] = 1;
}

int	init_alfred(t_texture_sheet *sprite)
{
	int i;

	sprite->bxpm.w		= bxpm_info_alfred[0];
	sprite->bxpm.h		= bxpm_info_alfred[1];
	sprite->bxpm.clr_nb	= bxpm_info_alfred[2];
	sprite->bxpm.pix_nb	= bxpm_info_alfred[3];
	sprite->bxpm.clr	= bxpm_colors_alfred;
	sprite->bxpm.pix	= bxpm_pixels_alfred;

	sprite->pos = (t_rect***)ft_memalloc(sizeof(t_rect**) * 4);
	init_alfred_nb(sprite);
	i = -1;
	if (sprite->nb[IDLE][FRAMES] > 0)
		sprite->pos[IDLE] = ft_memalloc(sizeof(t_rect*) * sprite->nb[IDLE][FRAMES]);
	while (++i < sprite->nb[IDLE][FRAMES])
		sprite->pos[IDLE][i] = ft_memalloc(sizeof(t_rect) * sprite->nb[IDLE][ANGLES]);
	i = -1;
	if (sprite->nb[MOVE][FRAMES] > 0)
		sprite->pos[MOVE] = ft_memalloc(sizeof(t_rect*) * sprite->nb[MOVE][FRAMES]);
	while (++i < sprite->nb[MOVE][FRAMES])
		sprite->pos[MOVE][i] = ft_memalloc(sizeof(t_rect) * sprite->nb[MOVE][ANGLES]);
	i = -1;
	if (sprite->nb[ATTACK][FRAMES] > 0)
		sprite->pos[ATTACK] = ft_memalloc(sizeof(t_rect*) * sprite->nb[ATTACK][FRAMES]);
	while (++i < sprite->nb[ATTACK][FRAMES])
		sprite->pos[ATTACK][i] = ft_memalloc(sizeof(t_rect) * sprite->nb[ATTACK][ANGLES]);
	i = -1;
	if (sprite->nb[DEATH][FRAMES] > 0)
		sprite->pos[DEATH] = ft_memalloc(sizeof(t_rect*) * sprite->nb[DEATH][FRAMES]);
	while (++i < sprite->nb[DEATH][FRAMES])
		sprite->pos[DEATH][i] = ft_memalloc(sizeof(t_rect) * sprite->nb[DEATH][ANGLES]);


	sprite->pos[0][0][4] = new_rect(0,		0,		43,		47);
	sprite->pos[0][0][5] = new_rect(88,		0,		120,	47);
	sprite->pos[0][0][6] = new_rect(164,	0,		195,	52);
	sprite->pos[0][0][7] = new_rect(239,	0,		274,	52);
	sprite->pos[0][0][0] = new_rect(318,	0,		362,	46);
	sprite->pos[0][0][1] = new_rect(377,	0,		412,	51);
	sprite->pos[0][0][2] = new_rect(456,	0,		487,	54);
	sprite->pos[0][0][3] = new_rect(531,	0,		562,	47);

	sprite->pos[1][0][4] = new_rect(0,		55,		44,		98);
	sprite->pos[1][0][5] = new_rect(48,		55, 	107,	91);
	sprite->pos[1][0][6] = new_rect(123,	55,		188,	89);
	sprite->pos[1][0][7] = new_rect(196,	55,		251,	87);
	sprite->pos[1][0][0] = new_rect(260,	55,		303,	80);
	sprite->pos[1][0][1] = new_rect(308,	55,		362,	86);
	sprite->pos[1][0][2] = new_rect(369,	55,		436,	88);
	sprite->pos[1][0][3] = new_rect(451,	55,		511,	90);

	sprite->pos[2][0][0] = new_rect(0,		103, 	33,		153);
	sprite->pos[2][1][0] = new_rect(78,		103,	114,	155);
	sprite->pos[2][2][0] = new_rect(158,	103,	202,	150);
	sprite->pos[2][3][0] = new_rect(247,	103,	315,	161);
	sprite->pos[2][4][0] = new_rect(359,	103,	447,	174);
	sprite->pos[2][5][0] = new_rect(491,	103,	594,	192);

	sprite->pos[3][0][0] = new_rect(0,		103, 	33,		153);
	sprite->pos[3][1][0] = new_rect(78,		103,	114,	155);
	sprite->pos[3][2][0] = new_rect(158,	103,	202,	150);
	sprite->pos[3][3][0] = new_rect(247,	103,	315,	161);
	sprite->pos[3][4][0] = new_rect(359,	103,	447,	174);
	sprite->pos[3][5][0] = new_rect(491,	103,	594,	192);
	return (1);
}
