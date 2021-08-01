/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_collision.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 10:52:34 by nneronin          #+#    #+#             */
/*   Updated: 2021/08/01 13:38:30 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

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
		curr = curr->next;
		if (point_distance_v3(entity->where, dest)
			< g_entity_data[entity->type].hitbox_radius)
		{
			*velocity = new_v3(0, 0, 0);
			return (1);
		}
	}
	return (0);
}
