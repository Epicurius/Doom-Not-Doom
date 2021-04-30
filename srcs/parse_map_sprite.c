/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map_entity.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 15:45:28 by nneronin          #+#    #+#             */
/*   Updated: 2021/04/30 14:25:39 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	parse_wsprite(t_doom *doom, char **arr)
{
	t_wsprites	*wsprite;
	t_wsprite	*sprite;

	wsprite			= &doom->walls[ft_atoi(arr[1])].wsprite;
	wsprite->total 		+= 1;
	wsprite->num 		= ft_realloc(wsprite->num, sizeof(t_wsprite)
						* wsprite->total);
	sprite			= &wsprite->num[wsprite->total - 1];
	sprite->id		= ft_atoi(arr[0]);
	sprite->where.x		= ft_atof(arr[2]) * doom->map_scale;
	sprite->where.y		= ft_atof(arr[3]) * doom->map_scale;
	sprite->scale_w		= ft_atof(arr[4]) * doom->map_scale;
	sprite->tx		= ft_atoi(arr[5]);
}

int		sprite_type(char *str)
{
	if (ft_strequ(str, "Alfred"))
		return (0);
	if (ft_strequ(str, "Spooky"))
		return (1);
	return (-1);
}

void	parse_entity(t_doom *doom, char **arr)
{
	t_sprite	*sprite;

	sprite 				= ft_memalloc(sizeof(t_sprite));
	sprite->type		= sprite_type(arr[0]);
	sprite->where.x		= ft_atof(arr[1]) * doom->map_scale;
	sprite->where.y		= ft_atof(arr[2]) * doom->map_scale;
	sprite->where.z		= ft_atof(arr[3]) * doom->map_scale;
	sprite->yaw			= ft_atoi(arr[4]);
	doom->nb.sprites	+= 1;
	ft_lstadd_new(&doom->sprite, sprite, sizeof(sprite));
	if (sprite->type == 2) //spawner
		ft_lstadd_new(&doom->spawners, sprite, sizeof(sprite));
	else if (sprite->type == 0 || sprite->type == 1) //enemy
		ft_lstadd_new(&doom->entities, sprite, sizeof(sprite));
	else
		ft_lstadd_new(&doom->objects, sprite, sizeof(sprite));
}
