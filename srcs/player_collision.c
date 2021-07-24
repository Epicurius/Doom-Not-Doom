/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_collision.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 15:33:51 by nneronin          #+#    #+#             */
/*   Updated: 2021/07/24 16:15:54 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static inline void	fix_sector_bug(t_doom *doom)
{
	if (!doom->settings.debug)
		printf("%d Wrong Sector!\n", doom->player.sector);
	doom->player.sector = find_sector(doom->sectors, doom->nb.sectors,
			doom->player.where);
	if (!doom->settings.debug)
	{
		if (doom->player.sector != -1)
			ft_printf("%d [ERROR]!\n", doom->player.sector);
		else
			ft_printf("%d Found Sector!\n", doom->player.sector);
	}
}

//		printf("%f %f %f\n", doom->player.where.x,
//			doom->player.where.y, doom->player.where.z);
void	player_collision(t_doom *doom)
{
	t_collision	p;

	p.where = &doom->player.where;
	p.velocity = &doom->player.velocity;
	p.sector = &doom->player.sector;
	p.sectors = doom->sectors;
	p.entities = doom->entity;
	p.nb_entities = doom->nb.entities;
	p.player = 1;
	p.hitbox_height = doom->player.eye_lvl + 1;
	p.hitbox_radius = PLAYER_RADIUS;
	p.step_height = STEP_HEIGHT;
	p.suffocate = 0;
	collision_detection(&p);
	if (p.suffocate)
		doom->player.health = 0;
	if (!in_sector(&doom->sectors[doom->player.sector], doom->player.where))
		fix_sector_bug(doom);
}
