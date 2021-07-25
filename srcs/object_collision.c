/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_collision.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 10:52:34 by nneronin          #+#    #+#             */
/*   Updated: 2021/07/25 10:48:32 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
void	object_collision(t_doom *doom, t_player *player)
{
	if (entity->type == AMMO)
		doom->player.ammo += 50;
	else if (object->type == HEALTH)
		doom->player.hp += 50;
	else
		return ;
	entity->render = 0;	
}
*/

int	entity_collision(t_collision *e, t_v3 dest)
{
	t_list		*curr;
	t_entity	*entities;

	curr = e->entities;
	while (curr)
	{
		entities = curr->content;
		curr = curr->next;
		if (point_distance_v3(entities->where, dest) > (e->hitbox_radius + 3))
			continue ;
		return (1);
	}
	return (0);
}
