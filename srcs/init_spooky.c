
#include "doom.h"

void	init_spooky_nb(t_texture_sheet *sprite)
{
	sprite->nb[IDLE][FRAMES] = 1;
	sprite->nb[IDLE][ANGLES] = 8;
	sprite->nb[MOVE][FRAMES] = 6;
	sprite->nb[MOVE][ANGLES] = 8;
	sprite->nb[ATTACK][FRAMES] = 5;
	sprite->nb[ATTACK][ANGLES] = 1;
	sprite->nb[DEATH][FRAMES] = 6;
	sprite->nb[DEATH][ANGLES] = 1;
}

int	init_spooky(t_texture_sheet *sprite)
{
	int i;
	
	init_spooky_nb(sprite);
	sprite->pos = (t_rect***)ft_memalloc(sizeof(t_rect**) * 4);
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

	sprite->pos[0][0][4] = new_rect(25,   193, 139,  377);
	sprite->pos[0][0][5] = new_rect(172,  193, 308,  377);
	sprite->pos[0][0][6] = new_rect(325,  193, 471,  377);
	sprite->pos[0][0][7] = new_rect(494,  193, 618,  377);
	sprite->pos[0][0][0] = new_rect(654,  193, 775,  377);
	sprite->pos[0][0][1] = new_rect(821,  193, 945,  377);
	sprite->pos[0][0][2] = new_rect(968,  193, 1113, 377);
	sprite->pos[0][0][3] = new_rect(1132, 193, 1265, 377);

	sprite->pos[1][0][4] = new_rect(25,   383, 139,  570);
	sprite->pos[1][0][5] = new_rect(172,  383, 308,  570);
	sprite->pos[1][0][6] = new_rect(325,  383, 471,  570);
	sprite->pos[1][0][7] = new_rect(494,  383, 618,  570);
	sprite->pos[1][0][0] = new_rect(654,  383, 775,  570);
	sprite->pos[1][0][1] = new_rect(821,  383, 945,  570);
	sprite->pos[1][0][2] = new_rect(968,  383, 1113, 570);
	sprite->pos[1][0][3] = new_rect(1132, 383, 1265, 570);

	sprite->pos[1][1][4] = new_rect(25,   579, 139,  764);
	sprite->pos[1][1][5] = new_rect(172,  579, 308,  764);
	sprite->pos[1][1][6] = new_rect(325,  579, 471,  764);
	sprite->pos[1][1][7] = new_rect(494,  579, 618,  764);
	sprite->pos[1][1][0] = new_rect(654,  579, 775,  764);
	sprite->pos[1][1][1] = new_rect(821,  579, 945,  764);
	sprite->pos[1][1][2] = new_rect(968,  579, 1113, 764);
	sprite->pos[1][1][3] = new_rect(1132, 579, 1265, 764);

	sprite->pos[1][2][4] = new_rect(25,   768, 139,  957);
	sprite->pos[1][2][5] = new_rect(172,  768, 308,  957);
	sprite->pos[1][2][6] = new_rect(325,  768, 471,  957);
	sprite->pos[1][2][7] = new_rect(494,  768, 618,  957);
	sprite->pos[1][2][0] = new_rect(654,  768, 775,  957);
	sprite->pos[1][2][1] = new_rect(821,  768, 945,  957);
	sprite->pos[1][2][2] = new_rect(968,  768, 1113, 957);
	sprite->pos[1][2][3] = new_rect(1132, 768, 1265, 957);

	sprite->pos[1][3][4] = new_rect(25,   965, 139,  1152);
	sprite->pos[1][3][5] = new_rect(172,  965, 308,  1152);
	sprite->pos[1][3][6] = new_rect(325,  965, 471,  1152);
	sprite->pos[1][3][7] = new_rect(494,  965, 618,  1152);
	sprite->pos[1][3][0] = new_rect(654,  965, 775,  1152);
	sprite->pos[1][3][1] = new_rect(821,  965, 945,  1152);
	sprite->pos[1][3][2] = new_rect(968,  965, 1113, 1152);
	sprite->pos[1][3][3] = new_rect(1132, 965, 1265, 1152);

	sprite->pos[1][4][4] = new_rect(25,   1158, 139,  1344);
	sprite->pos[1][4][5] = new_rect(172,  1158, 308,  1344);
	sprite->pos[1][4][6] = new_rect(325,  1158, 471,  1344);
	sprite->pos[1][4][7] = new_rect(494,  1158, 618,  1344);
	sprite->pos[1][4][0] = new_rect(654,  1158, 775,  1344);
	sprite->pos[1][4][1] = new_rect(821,  1158, 945,  1344);
	sprite->pos[1][4][2] = new_rect(968,  1158, 1113, 1344);
	sprite->pos[1][4][3] = new_rect(1132, 1158, 1265, 1344);

	sprite->pos[1][5][4] = new_rect(25,   1350, 139,  1536);
	sprite->pos[1][5][5] = new_rect(172,  1350, 308,  1536);
	sprite->pos[1][5][6] = new_rect(325,  1350, 471,  1536);
	sprite->pos[1][5][7] = new_rect(494,  1350, 618,  1536);
	sprite->pos[1][5][0] = new_rect(654,  1350, 775,  1536);
	sprite->pos[1][5][1] = new_rect(821,  1350, 945,  1536);
	sprite->pos[1][5][2] = new_rect(968,  1350, 1113, 1536);
	sprite->pos[1][5][3] = new_rect(1132, 1350, 1265, 1536);

	sprite->pos[2][0][0] = new_rect(27,	 0,	138,  192);
	sprite->pos[2][1][0] = new_rect(177, 0,	288,  192);
	sprite->pos[2][2][0] = new_rect(320, 0,	443,  192);
	sprite->pos[2][3][0] = new_rect(466, 0,	600,  192);
	sprite->pos[2][4][0] = new_rect(617, 0,	751,  192);

	sprite->pos[3][0][0] = new_rect(6,    1541, 145,  1719);
	sprite->pos[3][1][0] = new_rect(150,  1541, 284,  1706);
	sprite->pos[3][2][0] = new_rect(305,  1541, 432,  1644);
	sprite->pos[3][3][0] = new_rect(438,  1541, 583,  1637);
	sprite->pos[3][4][0] = new_rect(582,  1541, 759,  1627);
	sprite->pos[3][5][0] = new_rect(774,  1541, 941,  1627);

	return (1);
}
