/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map_entity.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 15:45:28 by nneronin          #+#    #+#             */
/*   Updated: 2021/04/29 14:05:01 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		sprite_type(char *str)
{
	if (ft_strequ(str, "Alfred"))
		return (0);
	if (ft_strequ(str, "Spooky"))
		return (1);
	return (-1);
}

void	add_to_list(t_sprite *content, t_list **list)
{
	t_list		*new;

	new = ft_lstnew(0, 0);
	new->content = content;
	ft_lstadd(&(*list), new);
}

void	init_map_entity(t_doom *doom, char **arr)
{
	t_sprite	*sprite;

	sprite 				= ft_memalloc(sizeof(t_sprite));
	sprite->type		= sprite_type(arr[0]);
	sprite->where.x		= ft_atof(arr[1]) * doom->map_scale;
	sprite->where.y		= ft_atof(arr[2]) * doom->map_scale;
	sprite->where.z		= ft_atof(arr[3]) * doom->map_scale;
	sprite->yaw			= ft_atoi(arr[4]);
	doom->nb.sprites	+= 1;
	add_to_list(sprite, &doom->sprite);
	if (sprite->type == 2) //spawner
		add_to_list(sprite, &doom->spawners);
	else if (sprite->type == 0 || sprite->type == 1) //enemy
		add_to_list(sprite, &doom->entities);
	else
		add_to_list(sprite, &doom->objects); //objects
}
