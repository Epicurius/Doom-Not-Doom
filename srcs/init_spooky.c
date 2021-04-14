
#include "doom.h"
#include "../bxpm/spooky.bxpm"

void	init_spooky_nb(t_texture_sheet *sprite)
{
	sprite->nb[IDLE][FRAMES] = 1;
	sprite->nb[IDLE][ANGLES] = 8;
	sprite->nb[MOVE][FRAMES] = 6;
	sprite->nb[MOVE][ANGLES] = 8;
	sprite->nb[ATTACK][FRAMES] = 6;
	sprite->nb[ATTACK][ANGLES] = 1;
	sprite->nb[DEATH][FRAMES] = 6;
	sprite->nb[DEATH][ANGLES] = 1;
}

int	init_spooky(t_doom *doom, t_texture_sheet *sprite)
{
	int i;

	sprite->bxpm.w		= bxpm_info_spooky[0];
	sprite->bxpm.h		= bxpm_info_spooky[1];
	sprite->bxpm.clr_nb	= bxpm_info_spooky[2];
	sprite->bxpm.pix_nb	= bxpm_info_spooky[3];
	sprite->bxpm.clr	= bxpm_colors_spooky;
	sprite->bxpm.pix	= bxpm_pixels_spooky;

	//sprite->surface = IMG_Load("./bmp/entities/spooky2.bmp");
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

	sprite->pos[1][0][4] = new_rect(25,   1163, 139,  1350);
	sprite->pos[1][0][5] = new_rect(172,  1163, 308,  1350);
	sprite->pos[1][0][6] = new_rect(325,  1163, 471,  1350);
	sprite->pos[1][0][7] = new_rect(494,  1163, 618,  1350);
	sprite->pos[1][0][0] = new_rect(654,  1163, 775,  1350);
	sprite->pos[1][0][1] = new_rect(821,  1163, 945,  1350);
	sprite->pos[1][0][2] = new_rect(968,  1163, 1113, 1350);
	sprite->pos[1][0][3] = new_rect(1132, 1163, 1265, 1350);

	sprite->pos[1][1][4] = new_rect(25,   1356, 139,  1542);
	sprite->pos[1][1][5] = new_rect(172,  1356, 308,  1542);
	sprite->pos[1][1][6] = new_rect(325,  1356, 471,  1542);
	sprite->pos[1][1][7] = new_rect(494,  1356, 618,  1542);
	sprite->pos[1][1][0] = new_rect(654,  1356, 775,  1542);
	sprite->pos[1][1][1] = new_rect(821,  1356, 945,  1542);
	sprite->pos[1][1][2] = new_rect(968,  1356, 1113, 1542);
	sprite->pos[1][1][3] = new_rect(1132, 1356, 1265, 1542);

	sprite->pos[1][2][4] = new_rect(25,   1550, 139,  1734);
	sprite->pos[1][2][5] = new_rect(172,  1550, 308,  1734);
	sprite->pos[1][2][6] = new_rect(325,  1550, 471,  1734);
	sprite->pos[1][2][7] = new_rect(494,  1550, 618,  1734);
	sprite->pos[1][2][0] = new_rect(654,  1550, 775,  1734);
	sprite->pos[1][2][1] = new_rect(821,  1550, 945,  1734);
	sprite->pos[1][2][2] = new_rect(968,  1550, 1113, 1734);
	sprite->pos[1][2][3] = new_rect(1132, 1550, 1265, 1734);

	sprite->pos[1][3][4] = new_rect(25,   1742, 139,  1928);
	sprite->pos[1][3][5] = new_rect(172,  1742, 308,  1928);
	sprite->pos[1][3][6] = new_rect(325,  1742, 471,  1928);
	sprite->pos[1][3][7] = new_rect(494,  1742, 618,  1928);
	sprite->pos[1][3][0] = new_rect(654,  1742, 775,  1928);
	sprite->pos[1][3][1] = new_rect(821,  1742, 945,  1928);
	sprite->pos[1][3][2] = new_rect(968,  1742, 1113, 1928);
	sprite->pos[1][3][3] = new_rect(1132, 1742, 1265, 1928);

	sprite->pos[1][4][4] = new_rect(25,   1938, 139,  2119);
	sprite->pos[1][4][5] = new_rect(172,  1938, 308,  2119);
	sprite->pos[1][4][6] = new_rect(325,  1938, 471,  2119);
	sprite->pos[1][4][7] = new_rect(494,  1938, 618,  2119);
	sprite->pos[1][4][0] = new_rect(654,  1938, 775,  2119);
	sprite->pos[1][4][1] = new_rect(821,  1938, 945,  2119);
	sprite->pos[1][4][2] = new_rect(968,  1938, 1113, 2119);
	sprite->pos[1][4][3] = new_rect(1132, 1938, 1265, 2119);

	sprite->pos[1][5][4] = new_rect(25,   2128, 139,  2313);
	sprite->pos[1][5][5] = new_rect(172,  2128, 308,  2313);
	sprite->pos[1][5][6] = new_rect(325,  2128, 471,  2313);
	sprite->pos[1][5][7] = new_rect(494,  2128, 618,  2313);
	sprite->pos[1][5][0] = new_rect(654,  2128, 775,  2313);
	sprite->pos[1][5][1] = new_rect(821,  2128, 945,  2313);
	sprite->pos[1][5][2] = new_rect(968,  2128, 1113, 2313);
	sprite->pos[1][5][3] = new_rect(1132, 2128, 1265, 2313);



	sprite->pos[2][0][0] = new_rect(0,    0,   160,  195);
	sprite->pos[2][1][0] = new_rect(0,    195, 160,  375);
	sprite->pos[2][2][0] = new_rect(0,    375, 160,  563);
	sprite->pos[2][3][0] = new_rect(0,    584, 160,  766);
	sprite->pos[2][4][0] = new_rect(0,    774, 160,  966);
	sprite->pos[2][5][0] = new_rect(0,    972, 160,  1152);


	sprite->pos[3][0][0] = new_rect(6,    2320, 145,  2496);
	sprite->pos[3][1][0] = new_rect(150,  2333, 284,  2496);
	sprite->pos[3][2][0] = new_rect(305,  2320, 432,  2423);
	sprite->pos[3][3][0] = new_rect(438,  2320, 583,  2412);
	sprite->pos[3][4][0] = new_rect(582,  2320, 759,  2406);
	sprite->pos[3][5][0] = new_rect(774,  2320, 941,  2066);



/*
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
*/
	return (1);
}
