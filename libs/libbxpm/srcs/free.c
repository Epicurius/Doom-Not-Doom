/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 16:07:56 by nneronin          #+#    #+#             */
/*   Updated: 2021/05/20 16:09:35 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
