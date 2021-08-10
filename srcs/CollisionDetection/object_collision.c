/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_collision.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 10:52:34 by nneronin          #+#    #+#             */
/*   Updated: 2021/08/04 12:20:58 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static int	collided_with_entity(t_doom *doom, t_v3 *velocity,
		t_list *curr, t_entity *entity)
{
	if (g_entity_data[entity->type].pickup == TRUE)
	{
		if (entity->type == MED_KIT)
			doom->player.health += g_entity_data[MED_KIT].health;
		curr = ft_dellstnode(&doom->entity, curr);
		doom->nb.entities -= 1;
		return (0);
	}
	*velocity = new_v3(0, 0, 0);
	return (1);
}

int	entity_collision(t_doom *doom, t_v3 *where, t_v3 *velocity)
{
	t_v3		dest;
	t_list		*curr;
	t_entity	*entity;

	curr = doom->entity;
	if (!curr)
		return (0);
	dest = add_v3(*where, *velocity);
	while (curr)
	{
		entity = curr->content;
		if (point_distance_v3(entity->where, dest)
			< g_entity_data[entity->type].hitbox_radius)
		{
			if (collided_with_entity(doom, velocity, curr, entity))
				return (1);
		}
		else
			curr = curr->next;
	}
	return (0);
}
