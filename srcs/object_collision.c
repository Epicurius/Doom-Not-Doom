/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_collision.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 10:52:34 by nneronin          #+#    #+#             */
/*   Updated: 2021/05/20 16:31:10 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
/*
void	object_collision(t_doom *doom, t_player *player)
{
	if (sprite->type == AMMO)
		doom->player.ammo += 50;
	else if (object->type == HEALTH)
		doom->player.hp += 50;
	else
		return ;
	sprite->render = 0;	
}
*/

int	sprite_collision(t_collision *e, t_xyz dest)
{
	t_list *curr;
	t_entity *entities;

	curr = e->entities;
	while (curr)
	{
		entities = curr->content;
		curr = curr->next;
		if (point_distance_3d(entities->where, dest) > (e->hitbox_radius + 3))
			continue ;
		//if (sprite->entities[i].animate)
		//	return (1);
		//else if (player)
		//	object_collision(doom, &doom->sprite[i]);
		return (1);
	}
	return (0);
}
