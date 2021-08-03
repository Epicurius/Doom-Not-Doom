/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_sprite.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 15:45:28 by nneronin          #+#    #+#             */
/*   Updated: 2021/08/03 10:05:32 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int	wsprite_state(char *str)
{
	if (ft_strequ(str, "LOOP"))
		return (LOOP);
	else if (ft_strequ(str, "ACTION"))
		return (ACTION);
	return (STATIC);
}

void	parse_wsprite(t_doom *doom, char **arr)
{
	t_wsprites	*wsprite;
	t_wsprite	*sprite;

	wsprite = &doom->walls[ft_atoi(arr[1])].wsprite;
	wsprite->num = ft_realloc(wsprite->num, sizeof(t_wsprite) * wsprite->total,
			sizeof(t_wsprite) * ++wsprite->total);
	sprite = &wsprite->num[wsprite->total - 1];
	sprite->id = ft_atoi(arr[0]);
	sprite->where.x = ft_atof(arr[2]) * doom->map_scale;
	sprite->where.y = ft_atof(arr[3]) * doom->map_scale;
	sprite->tx = ft_atoi(arr[4]);
	sprite->scale_w = ft_atof(arr[5]) * doom->map_scale;
	sprite->state = wsprite_state(arr[6]);
	sprite->trigger = -1;
}

int	sprite_type(char *str)
{
	if (ft_strequ(str, "Alfred"))
		return (ALFRED);
	if (ft_strequ(str, "Spooky"))
		return (SPOOKY);
	if (ft_strequ(str, "Rift"))
		return (RIFT);
	if (ft_strequ(str, "Barrel"))
		return (BARREL);
	if (ft_strequ(str, "Lamp"))
		return (LAMP);
	if (ft_strequ(str, "Torch"))
		return (TORCH);
	if (ft_strequ(str, "MeatHook"))
		return (MEAT_HOOK);
	if (ft_strequ(str, "Ghost"))
		return (GHOST);
	error_msg("%s is not a valid entity!\n", str);
	return (-1);
}

void	parse_entity(t_doom *doom, char **arr)
{
	t_entity	*entity;

	entity = protalloc(sizeof(t_entity), "parse_entity");
	entity->type = sprite_type(arr[1]);
	entity->where.x = ft_atof(arr[2]) * doom->map_scale;
	entity->where.y = ft_atof(arr[3]) * doom->map_scale;
	entity->where.z = ft_atof(arr[4]) * doom->map_scale;
	entity->yaw = ft_atoi(arr[5]);
	doom->nb.entities += 1;
	ft_lstadd_new(&doom->entity, entity, sizeof(t_entity));
}
