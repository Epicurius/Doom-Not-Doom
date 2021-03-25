
#include "doom.h"

void	init_alfred_nb(t_texture_sheet *sprite)
{
	sprite->nb[IDLE][FRAMES] = 1;
	sprite->nb[IDLE][ANGLES] = 8;
	sprite->nb[MOVE][FRAMES] = 1;
	sprite->nb[MOVE][ANGLES] = 8;
	sprite->nb[ATTACK][FRAMES] = 6;
	sprite->nb[ATTACK][ANGLES] = 1;
	sprite->nb[DEATH][FRAMES] = 0;
	sprite->nb[DEATH][ANGLES] = 0;
}

int	init_alfred(t_doom *doom, t_texture_sheet *sprite)
{
	int i;

	sprite->surface = IMG_Load("./bmp/entities/head_fix2.bmp");
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


	sprite->pos[0][0][4] = new_rect(45,  33, 88,  79);
	sprite->pos[0][0][5] = new_rect(133, 33, 163, 79);
	sprite->pos[0][0][6] = new_rect(210, 33, 239, 86);
	sprite->pos[0][0][7] = new_rect(283, 33, 317, 84);
	sprite->pos[0][0][0] = new_rect(362, 33, 405, 78);
	sprite->pos[0][0][1] = new_rect(424, 33, 456, 85);
	sprite->pos[0][0][2] = new_rect(500, 33, 531, 87);
	sprite->pos[0][0][3] = new_rect(576, 33, 607, 79);

	sprite->pos[1][0][4] = new_rect(45,  33, 88,  79);
	sprite->pos[1][0][5] = new_rect(133, 33, 163, 79);
	sprite->pos[1][0][6] = new_rect(210, 33, 239, 86);
	sprite->pos[1][0][7] = new_rect(283, 33, 317, 84);
	sprite->pos[1][0][0] = new_rect(362, 33, 405, 78);
	sprite->pos[1][0][1] = new_rect(424, 33, 456, 85);
	sprite->pos[1][0][2] = new_rect(500, 33, 531, 87);
	sprite->pos[1][0][3] = new_rect(576, 33, 607, 79);


	sprite->pos[2][0][0] = new_rect(44,  449,  78, 499);
	sprite->pos[2][1][0] = new_rect(122, 449, 158, 500);
	sprite->pos[2][2][0] = new_rect(203, 449, 247, 496);
	sprite->pos[2][3][0] = new_rect(291, 449, 359, 508);
	sprite->pos[2][4][0] = new_rect(403, 449, 491, 520);
	sprite->pos[2][5][0] = new_rect(539, 449, 638, 537);
	return (1);
}
