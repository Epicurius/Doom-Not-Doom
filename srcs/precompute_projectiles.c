/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precompute_projectiles.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 13:12:25 by nneronin          #+#    #+#             */
/*   Updated: 2021/05/02 11:32:58 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
/*
t_list	*free_projectile(t_doom *doom, t_list *del)
{
	t_list *next;

	next = NULL;
	if (del->prev == NULL && del->next == NULL)
		doom->orb = NULL;
	else if (del->next != NULL && del->prev != NULL)
	{
		del->next->prev = del->prev;
		del->prev->next = del->next;
	}
	else if (del->next != NULL)
	{
		doom->orb = del->next;
		del->next->prev = NULL;
	}
	else if (del->prev != NULL)
		del->prev->next = NULL;
	if (doom->orb != NULL)
		next = del->next;
	free(del->content);
	free(del);
	doom->nb.projectiles -= 1;
	return (next);
}
*/
int	player_contact(t_doom *doom, t_xyz start, t_xyz dest)
{
	if (point_distance_3d(doom->player.where, dest) <= 5)
	{
		doom->player.hp -= 10;
		return (1);
	}
	if (point_distance_3d(start, dest) > PROJECTILE_MAX_RANGE)
		return (1);
	return (0);
}

static int		vertical_collision(t_doom *doom, t_projectile *orb, t_xyz dest)
{
	t_sector sector;

	sector = doom->sectors[orb->sector];
	if (dest.z < sector.floor.y || dest.z > sector.ceiling.y)
		return (1);
	orb->where.z += orb->velocity.z;
	return (0);
}

int		projectile_collision(t_doom *doom, t_projectile *orb, t_xyz dest)
{
	t_collision o;

	o.where				= &orb->where;
	o.velocity			= &orb->velocity;
	o.sector			= &orb->sector;
	o.sectors			= doom->sectors;
	o.hitbox_height		= 5;
	o.hitbox_radius		= 5;
	o.step_height		= 0;
	if (player_contact(doom, orb->start, dest) ||
		vertical_collision(doom, orb, dest) ||
		horizontal_collision(&o, dest))
		return (1);
	return (0);
}

void	precompute_projectiles(t_doom *doom)
{
	t_xyz dest;
	t_list *curr;
	t_projectile *orb;

	curr = doom->orb;
	while (curr)
	{
		orb = curr->content;
		dest = sum_xyz(orb->where, orb->velocity);
		if (projectile_collision(doom, orb, dest))
			curr = ft_dellstnode(&doom->orb, curr);
		else
			curr = curr->next;
	}
	//ft_printf("%d\n", doom->nb.projectiles);
}
