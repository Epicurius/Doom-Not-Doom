/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_collision.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 15:33:51 by nneronin          #+#    #+#             */
/*   Updated: 2021/05/28 10:43:15 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	player_collision(t_doom *doom)
{
	t_collision p;

	p.where				= &doom->player.where;
	p.velocity			= &doom->player.velocity;
	p.sector			= &doom->player.sector;
	p.sectors			= doom->sectors;
	p.entities			= doom->sprite;
	p.nb_entities		= doom->nb.sprites;
	p.player			= 1;
	p.hitbox_height		= doom->player.eye_lvl + 1;
	p.hitbox_radius		= PLAYER_RADIUS;
	p.step_height		= STEP_HEIGHT;
	collision_detection(&p);
	if (!in_sector(&doom->sectors[doom->player.sector], doom->player.where))
	{
		ft_printf("%d Wrong Sector!\n", doom->player.sector);
		doom->player.sector = find_sector(doom, doom->player.where);
		if (doom->player.sector != -1)
			ft_printf("%d [ERROR]!\n", doom->player.sector);
		else
			ft_printf("%d Found Sector!\n", doom->player.sector);
	}
}
