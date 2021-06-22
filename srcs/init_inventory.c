/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_inventory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 12:11:55 by nneronin          #+#    #+#             */
/*   Updated: 2021/06/22 12:20:10 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	init_inventory(t_doom *doom)
{
	doom->inv.dosh = 0;
	doom->inv.hp = doom->player.hp;
	doom->inv.armour = NULL;
	doom->inv.weapon = doom->weapon;
	doom->inv.speed = &doom->player.sprint_speed;
	doom->inv.jump = &doom->player.jump_height;
}
