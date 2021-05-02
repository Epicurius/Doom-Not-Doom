/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_rift.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 17:39:41 by nneronin          #+#    #+#             */
/*   Updated: 2021/05/02 16:56:56 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	init_rift_nb(t_texture_sheet *sprite)
{
	sprite->nb[IDLE  ][FRAMES] = 1;
	sprite->nb[IDLE  ][ANGLES] = 1;
	sprite->nb[MOVE  ][FRAMES] = 0;
	sprite->nb[MOVE  ][ANGLES] = 0;
	sprite->nb[ATTACK][FRAMES] = 0;
	sprite->nb[ATTACK][ANGLES] = 0;
	sprite->nb[DEATH ][FRAMES] = 3;
	sprite->nb[DEATH ][ANGLES] = 1;
}

int	init_rift(t_texture_sheet *sprite)
{
	int i;

	init_rift_nb(sprite);
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

	sprite->pos[0][0][0] = new_rect(0,		0,	174, 315);
	//sprite->pos[0][0][0] = new_rect(533,		0,	174, 687);
	sprite->pos[3][0][0] = new_rect(174,	0,	351, 315);
	sprite->pos[3][1][0] = new_rect(351,	0,	527, 315);
	sprite->pos[3][2][0] = new_rect(527,	0,	689, 315);
	return (1);
}
