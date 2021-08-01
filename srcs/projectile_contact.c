/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projectile_contact.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/01 13:15:50 by nneronin          #+#    #+#             */
/*   Updated: 2021/08/01 13:36:56 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

//			Maybe remove break for multy kills? will be slower.
static int	target_demon(t_doom *doom, t_projectile *orb, t_v3 dest)
{
	int		contact;
	t_list	*curr;

	contact = 0;
	curr = doom->entity;
	while (curr)
	{
		if (((t_entity *)curr->content)->type < RIFT
			&& point_distance_v3(((t_entity *)curr->content)->where, dest) <= 5)
		{
			((t_entity *)curr->content)->state = DEATH;
			contact = 1;
			break ;
		}
		curr = curr->next;
	}
	return (contact);
}

int	target_contact(t_doom *doom, t_projectile *orb, t_v3 start, t_v3 dest)
{
	if (orb->target == 0)
	{
		if (point_distance_v3(doom->player.where, dest) <= 5)
		{
			Mix_PlayChannel(-1, doom->sound[WAV_PLAYER_HIT], 0);
			doom->player.health -= 10;
			return (1);
		}
	}
	else if (orb->target == 1 && target_demon(doom, orb, dest))
		return (1);
	if (point_distance_v3(start, dest) > orb->range)
		return (1);
	return (0);
}
