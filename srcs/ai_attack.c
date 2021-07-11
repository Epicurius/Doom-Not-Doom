/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ai_attack.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 10:41:36 by nneronin          #+#    #+#             */
/*   Updated: 2021/07/11 14:20:06 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static t_v3	projectile_movement(t_doom *doom, t_v3 curr, t_v3 dest)
{
	t_v3	move;
	double	dist;
	double	speed;

	speed = PROJECTILE_SPEED * doom->time.delta;
	move.x = dest.x - curr.x;
	move.y = dest.y - curr.y;
	move.z = dest.z - curr.z;
	if (move.x == 0 && move.y == 0 && move.z == 0)
		return (move);
	dist = space_diagonal(move);
	move.x *= speed / dist;
	move.y *= speed / dist;
	move.z *= speed / dist;
	return (move);
}

void	ai_attack(t_doom *doom, t_entity *entity)
{
	t_projectile	*orb;

	entity->yaw = angle_to_point_v2(entity->where, doom->player.where);
	if (entity->frame < doom->npc_bxpm[entity->type].nb[ATTACK][FRAMES] - 1)
		return ;
	if (g_entity_data[entity->type].attack_style == 2)
	{
		doom->player.hp -= g_entity_data[entity->type].damage;
		entity->hp = 0;
		entity->state = DEATH;
	}
	else if (g_entity_data[entity->type].attack_style == 1)
	{
		orb = ft_memalloc(sizeof(t_projectile));
		orb->velocity = projectile_movement(doom, entity->where,
				doom->player.where);
		orb->where.x = entity->where.x;
		orb->where.y = entity->where.y;
		orb->where.z = entity->where.z;
		orb->start = orb->where;
		orb->sector = entity->sector;
		ft_lstadd_new(&doom->orb, orb, sizeof(orb));
		entity->frame += 1;
		doom->nb.projectiles += 1;
	}
}
