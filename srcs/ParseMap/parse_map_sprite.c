/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_sprite.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 15:45:28 by nneronin          #+#    #+#             */
/*   Updated: 2021/12/14 18:11:22 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
 *	Parse wall sprite state.
 */
int	wsprite_state(char *str)
{
	if (ft_strequ(str, "LOOP"))
		return (LOOP);
	else if (ft_strequ(str, "ACTION"))
		return (ACTION);
	return (STATIC);
}

/*
 *	Parse wall sprite.
 */
void	parse_wsprite(t_doom *doom, int nb, char **arr)
{
	t_wsprites	*wsprite;
	t_wsprite	*sprite;

	if (nb < 7)
		error_msg("Invalid amount of wsprite arguments %s\n", arr[0]);
	wsprite = &doom->walls[ft_atoi(arr[1])].wsprite;
	wsprite->num = ft_realloc(wsprite->num, sizeof(t_wsprite) * wsprite->total,
			sizeof(t_wsprite) * ++wsprite->total);
	sprite = &wsprite->num[wsprite->total - 1];
	sprite->id = ft_atoi(arr[0]);
	sprite->where.x = ft_atof(arr[2]) * doom->map_scale;
	sprite->where.y = ft_atof(arr[3]) * doom->map_scale;
	sprite->tx = ft_atoi(arr[4]);
	sprite->scale_w = (ft_atof(arr[5]) / 100) * doom->map_scale;
	sprite->state = wsprite_state(arr[6]);
	sprite->trigger = -1;
}

/*
 *	Parse entity type.
 *	Returns -1 if not valid entity.
 */
static int	entity_type(char *str)
{
	int	i;

	i = -1;
	while (++i < ENTITY_AMOUNT)
	{
		if (ft_strequ(str, g_entity_data[i].name))
			return (i);
	}
	error_msg("%s is not a valid entity!\n", str);
	exit (1);
}

/*
 *	Parse entity.
 */
void	parse_entity(t_doom *doom, int nb, char **arr)
{
	t_entity	*entity;

	if (nb < 7)
		error_msg("Invalid amount of entity arguments %s\n", arr[0]);
	entity = protalloc(sizeof(t_entity));
	entity->type = entity_type(arr[1]);
	entity->where.x = ft_atoi(arr[2]) * doom->map_scale;
	entity->where.y = ft_atoi(arr[3]) * doom->map_scale;
	entity->where.z = ft_atoi(arr[4]) * doom->map_scale;
	entity->yaw = ft_atoi(arr[5]) * CONVERT_TO_RADIANS;
	entity->sector = ft_atoi(arr[6]);
	doom->nb.entities += 1;
	ft_lstadd_new(&doom->entity, entity, sizeof(t_entity));
}
