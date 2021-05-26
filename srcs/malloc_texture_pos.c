/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_texture_pos.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 10:27:28 by nneronin          #+#    #+#             */
/*   Updated: 2021/05/26 14:32:01 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static int	malloc_state_frames_and_angles(t_npc_bxpm *sprite, int state)
{
	int	i;

	i = -1;
	if (sprite->nb[state][FRAMES] <= 0)
		return (1);
	sprite->pos[state] = ft_memalloc(sizeof(t_rect *)
			* sprite->nb[state][FRAMES]);
	if (!sprite->pos[state])
		return (0);
	while (++i < sprite->nb[state][FRAMES])
	{
		sprite->pos[state][i] = ft_memalloc(sizeof(t_rect)
				* sprite->nb[state][ANGLES]);
		if (!sprite->pos[state][i])
			return (0);
	}
	return (1);
}

void	malloc_texture_pos(t_npc_bxpm *sprite)
{
	sprite->pos = (t_rect ***)ft_memalloc(sizeof(t_rect **) * 4);
	if (!sprite->pos)
		error_msg("Malloc img pos\n");
	if (!malloc_state_frames_and_angles(sprite, IDLE))
		error_msg("Malloc img pos IDLE\n");
	if (!malloc_state_frames_and_angles(sprite, MOVE))
		error_msg("Malloc img pos MOVE\n");
	if (!malloc_state_frames_and_angles(sprite, ATTACK))
		error_msg("Malloc img pos ATTACK\n");
	if (!malloc_state_frames_and_angles(sprite, DEATH))
		error_msg("Malloc img pos DEATH\n");
}
