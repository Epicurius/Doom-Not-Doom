/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ai_attack.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 10:41:36 by nneronin          #+#    #+#             */
/*   Updated: 2021/12/12 10:54:02 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
 *	Function calculates projectile direction and velocity towards the player.
 */
static t_v3	projectile_movement(t_doom *doom, t_v3 curr, t_v3 dest)
{
	t_v3	velocity;
	float	dist;

	curr.z += 4.5;
	dest.z += doom->player.eyelvl - 1;
	velocity = sub_v3(dest, curr);
	if (velocity.x == 0 && velocity.y == 0 && velocity.z == 0)
		return (velocity);
	dist = space_diagonal(velocity);
	velocity = mult_v3(velocity, PROJECTILE_SPEED / dist);
	return (velocity);
}

/*
 *	Function spawns and inits projectile.
 */
static void	spawn_projectile(t_doom *doom, t_entity *entity)
{
	t_projectile	*orb;

	orb = protalloc(sizeof(t_projectile));
	orb->velocity = projectile_movement(doom,
			entity->where, doom->player.where);
	orb->where = entity->where;
	orb->where.z += 4.5;
	orb->start = orb->where;
	orb->sector = entity->sector;
	orb->target = 0;
	orb->range = ENTITY_PROJECTILE_MAX_RANGE;
	ft_lstadd_new(&doom->orb, orb, sizeof(t_projectile));
	entity->frame += 1;
	doom->nb.projectiles += 1;
	Mix_PlayChannel(CHANNEL_EXPLOSION, doom->sound[WAV_ORB], 0);
}

/*
 *	Function handles the entity attack state.
 */
void	ai_attack(t_doom *doom, t_entity *entity)
{
	entity->yaw = degree_to_point_v2(entity->where, doom->player.where);
	if (entity->frame < doom->eframes[entity->type].nb[ATTACK][FRAMES] - 1)
		return ;
	if (g_entity_data[entity->type].type == MELEE)
	{
		doom->player.health -= g_entity_data[entity->type].damage;
		Mix_PlayChannel(-1, doom->sound[WAV_PLAYER_HIT], 0);
	}
	else if (g_entity_data[entity->type].type == KAMIKAZE)
	{
		doom->player.health -= g_entity_data[entity->type].damage;
		Mix_PlayChannel(-1, doom->sound[WAV_PLAYER_HIT], 0);
		entity->hp = 0;
		entity->state = DEATH;
	}
	else if (g_entity_data[entity->type].type == RANGE)
		spawn_projectile(doom, entity);
}
