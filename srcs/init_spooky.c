
#include "doom.h"

void	init_spooky_nb(t_texture_sheet *sprite)
{
	sprite->nb[IDLE][FRAMES] = 1;
	sprite->nb[IDLE][ANGLES] = 8;
	sprite->nb[MOVE][FRAMES] = 6;
	sprite->nb[MOVE][ANGLES] = 8;
	sprite->nb[ATTACK][FRAMES] = 6;
	sprite->nb[ATTACK][ANGLES] = 8;
	sprite->nb[DEATH][FRAMES] = 0;//7;
	sprite->nb[DEATH][ANGLES] = 0;//1;
}

int	init_spooky(t_doom *doom, t_texture_sheet *sprite)
{
	int i;

	sprite->surface = IMG_Load("./bmp/entities/spooky2.bmp");
	sprite->pos = (t_rect***)ft_memalloc(sizeof(t_rect**) * 4);
	init_spooky_nb(sprite);
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

	sprite->pos[0][0][4] = new_rect(25,   1153, 139,  1350);
	sprite->pos[0][0][5] = new_rect(172,  1153, 308,  1350);
	sprite->pos[0][0][6] = new_rect(325,  1153, 471,  1350);
	sprite->pos[0][0][7] = new_rect(494,  1153, 618,  1350);
	sprite->pos[0][0][0] = new_rect(654,  1153, 775,  1350);
	sprite->pos[0][0][1] = new_rect(821,  1153, 945,  1350);
	sprite->pos[0][0][2] = new_rect(968,  1153, 1113, 1350);
	sprite->pos[0][0][3] = new_rect(1132, 1153, 1265, 1350);

	sprite->pos[1][0][4] = new_rect(25,   1153, 139,  1350);
	sprite->pos[1][0][5] = new_rect(172,  1153, 308,  1350);
	sprite->pos[1][0][6] = new_rect(325,  1153, 471,  1350);
	sprite->pos[1][0][7] = new_rect(494,  1153, 618,  1350);
	sprite->pos[1][0][0] = new_rect(654,  1153, 775,  1350);
	sprite->pos[1][0][1] = new_rect(821,  1153, 945,  1350);
	sprite->pos[1][0][2] = new_rect(968,  1153, 1113, 1350);
	sprite->pos[1][0][3] = new_rect(1132, 1153, 1265, 1350);

	sprite->pos[1][1][4] = new_rect(0,    1350, 160,  1542);
	sprite->pos[1][1][5] = new_rect(160,  1350, 320,  1542);
	sprite->pos[1][1][6] = new_rect(320,  1350, 480,  1542);
	sprite->pos[1][1][7] = new_rect(480,  1350, 640,  1542);
	sprite->pos[1][1][0] = new_rect(640,  1350, 800,  1542);
	sprite->pos[1][1][1] = new_rect(960,  1350, 1020, 1542);
	sprite->pos[1][1][2] = new_rect(1020, 1350, 1180, 1542);
	sprite->pos[1][1][3] = new_rect(1180, 1350, 1280, 1542);

	sprite->pos[1][2][4] = new_rect(0,    1542, 160,  1734);
	sprite->pos[1][2][5] = new_rect(160,  1542, 320,  1734);
	sprite->pos[1][2][6] = new_rect(320,  1542, 480,  1734);
	sprite->pos[1][2][7] = new_rect(480,  1542, 640,  1734);
	sprite->pos[1][2][0] = new_rect(640,  1542, 800,  1734);
	sprite->pos[1][2][1] = new_rect(960,  1542, 1020, 1734);
	sprite->pos[1][2][2] = new_rect(1020, 1542, 1180, 1734);
	sprite->pos[1][2][3] = new_rect(1180, 1542, 1280, 1734);

	sprite->pos[1][3][4] = new_rect(0,    1734, 160,  1926);
	sprite->pos[1][3][5] = new_rect(160,  1734, 320,  1926);
	sprite->pos[1][3][6] = new_rect(320,  1734, 480,  1926);
	sprite->pos[1][3][7] = new_rect(480,  1734, 640,  1926);
	sprite->pos[1][3][0] = new_rect(640,  1734, 800,  1926);
	sprite->pos[1][3][1] = new_rect(960,  1734, 1020, 1926);
	sprite->pos[1][3][2] = new_rect(1020, 1734, 1180, 1926);
	sprite->pos[1][3][3] = new_rect(1180, 1734, 1280, 1926);

	sprite->pos[1][4][4] = new_rect(0,    1926, 160,  2118);
	sprite->pos[1][4][5] = new_rect(160,  1926, 320,  2118);
	sprite->pos[1][4][6] = new_rect(320,  1926, 480,  2118);
	sprite->pos[1][4][7] = new_rect(480,  1926, 640,  2118);
	sprite->pos[1][4][0] = new_rect(640,  1926, 800,  2118);
	sprite->pos[1][4][1] = new_rect(960,  1926, 1020, 2118);
	sprite->pos[1][4][2] = new_rect(1020, 1926, 1180, 2118);
	sprite->pos[1][4][3] = new_rect(1180, 1926, 1280, 2118);

	sprite->pos[1][5][4] = new_rect(0,    2118, 160,  2310);
	sprite->pos[1][5][5] = new_rect(160,  2118, 320,  2310);
	sprite->pos[1][5][6] = new_rect(320,  2118, 480,  2310);
	sprite->pos[1][5][7] = new_rect(480,  2118, 640,  2310);
	sprite->pos[1][5][0] = new_rect(640,  2118, 800,  2310);
	sprite->pos[1][5][1] = new_rect(960,  2118, 1020, 2310);
	sprite->pos[1][5][2] = new_rect(1020, 2118, 1180, 2310);
	sprite->pos[1][5][3] = new_rect(1180, 2118, 1280, 2310);


	sprite->pos[2][0][4] = new_rect(0,    0, 160,  195);
	sprite->pos[2][0][5] = new_rect(160,  0, 320,  195);
	sprite->pos[2][0][6] = new_rect(320,  0, 480,  195);
	sprite->pos[2][0][7] = new_rect(480,  0, 640,  195);
	sprite->pos[2][0][0] = new_rect(640,  0, 800,  195);
	sprite->pos[2][0][1] = new_rect(960,  0, 1020, 195);
	sprite->pos[2][0][2] = new_rect(1020, 0, 1180, 195);
	sprite->pos[2][0][3] = new_rect(1180, 0, 1280, 195);

	sprite->pos[2][1][4] = new_rect(0,    195, 160,  375);
	sprite->pos[2][1][5] = new_rect(160,  195, 320,  375);
	sprite->pos[2][1][6] = new_rect(320,  195, 480,  375);
	sprite->pos[2][1][7] = new_rect(480,  195, 640,  375);
	sprite->pos[2][1][0] = new_rect(640,  195, 800,  375);
	sprite->pos[2][1][1] = new_rect(960,  195, 1020, 375);
	sprite->pos[2][1][2] = new_rect(1020, 195, 1180, 375);
	sprite->pos[2][1][3] = new_rect(1180, 195, 1280, 375);

	sprite->pos[2][2][4] = new_rect(0,    375, 160,  563);
	sprite->pos[2][2][5] = new_rect(160,  375, 320,  563);
	sprite->pos[2][2][6] = new_rect(320,  375, 480,  563);
	sprite->pos[2][2][7] = new_rect(480,  375, 640,  563);
	sprite->pos[2][2][0] = new_rect(640,  375, 800,  563);
	sprite->pos[2][2][1] = new_rect(960,  375, 1020, 563);
	sprite->pos[2][2][2] = new_rect(1020, 375, 1180, 563);
	sprite->pos[2][2][3] = new_rect(1180, 375, 1280, 563);

	sprite->pos[2][3][4] = new_rect(0,    584, 160,  766);
	sprite->pos[2][3][5] = new_rect(160,  584, 320,  766);
	sprite->pos[2][3][6] = new_rect(320,  584, 480,  766);
	sprite->pos[2][3][7] = new_rect(480,  584, 640,  766);
	sprite->pos[2][3][0] = new_rect(640,  584, 800,  766);
	sprite->pos[2][3][1] = new_rect(960,  584, 1020, 766);
	sprite->pos[2][3][2] = new_rect(1020, 584, 1180, 766);
	sprite->pos[2][3][3] = new_rect(1180, 584, 1280, 766);

	sprite->pos[2][4][4] = new_rect(0,    774, 160,  966);
	sprite->pos[2][4][5] = new_rect(160,  774, 320,  966);
	sprite->pos[2][4][6] = new_rect(320,  774, 480,  966);
	sprite->pos[2][4][7] = new_rect(480,  774, 640,  966);
	sprite->pos[2][4][0] = new_rect(640,  774, 800,  966);
	sprite->pos[2][4][1] = new_rect(960,  774, 1020, 966);
	sprite->pos[2][4][2] = new_rect(1020, 774, 1180, 966);
	sprite->pos[2][4][3] = new_rect(1180, 774, 1280, 966);

	sprite->pos[2][5][4] = new_rect(0,    972, 160,  1152);
	sprite->pos[2][5][5] = new_rect(160,  972, 320,  1152);
	sprite->pos[2][5][6] = new_rect(320,  972, 480,  1152);
	sprite->pos[2][5][7] = new_rect(480,  972, 640,  1152);
	sprite->pos[2][5][0] = new_rect(640,  972, 800,  1152);
	sprite->pos[2][5][1] = new_rect(960,  972, 1020, 1152);
	sprite->pos[2][5][2] = new_rect(1020, 972, 1180, 1152);
	sprite->pos[2][5][3] = new_rect(1180, 972, 1280, 1152);

	return (1);
}
