/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Niklas Neronin <niklas.neronin@gmail.com>
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
