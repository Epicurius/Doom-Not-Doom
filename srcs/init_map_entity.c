/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map_entity.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 15:45:28 by nneronin          #+#    #+#             */
/*   Updated: 2021/04/24 16:10:57 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	add_spawner_to_list(t_doom *doom, t_entity *entity)
{
	t_list		*new;

	new = ft_lstnew(0, 0);
	if (!(doom->spawner))
		doom->spawner = new;
	else
		ft_lstadd(&(doom->spawner), new);
	doom->spawner->content = entity;
}

void	add_entity_to_list(t_doom *doom, t_entity *entity)
{
	t_list		*new;

	new = ft_lstnew(0, 0);
	if (!(doom->entity))
		doom->entity = new;
	else
		ft_lstadd(&(doom->entity), new);
	doom->entity->content = entity;
	doom->nb.entities	+= 1;
}

// render_list that has all
// object_list
// enemmt_list
// spawner_list

void	init_map_entity(t_doom *doom, char **arr)
{
	t_entity	*entity;

	entity 				= ft_memalloc(sizeof(t_entity));
	entity->id			= ft_atoi(arr[0]);
	entity->type		= ft_atoi(arr[1]);
	entity->where.x		= ft_atof(arr[2]) * doom->map_scale;
	entity->where.y		= ft_atof(arr[3]) * doom->map_scale;
	entity->where.z		= ft_atof(arr[4]) * doom->map_scale;
	entity->yaw			= ft_atoi(arr[5]);
	add_entity_to_list(doom, entity);
	//if (entity->type == 2)
	//	add_spawner_to_list(doom, entity);
}
