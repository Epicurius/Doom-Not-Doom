/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_inv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 12:11:55 by nneronin          #+#    #+#             */
/*   Updated: 2021/05/20 13:06:20 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	init_inv(t_doom *doom)
{
	doom->inv.dosh = 0;
	doom->inv.hp = doom->player.hp;
	doom->inv.armour = NULL;
	doom->inv.weapon = doom->weapon;
	doom->inv.speed = &doom->player.sprint_speed;
	doom->inv.jump = &doom->player.jump_height;
}
