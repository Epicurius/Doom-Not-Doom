/*
 * https://github.com/Epicurius/Doom-Not-Doom
 * 
 * Created: 2021/05/20 16:07:56 nneronin
 * Updated: 2021/05/20 16:09:35 nneronin
 */

#include "bxpm.h"

void	free_bxpm(t_bxpm *bxpm)
{
	free(bxpm->clr);
	free(bxpm->pix);
	free(bxpm);
}

void	free_bmp(t_bmp *bmp)
{
	free(bmp->data);
	free(bmp);
}
