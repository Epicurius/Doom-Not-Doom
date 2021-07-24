/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_weapons.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 13:47:18 by nneronin          #+#    #+#             */
/*   Updated: 2021/07/24 10:22:01 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	weapon_texture_array(t_doom *doom)
{
	int	i;

	i = -1;
	while (++i < WEAPON_AMOUNT)
	{
		doom->weapon[i].bxpm = malloc(sizeof(t_bxpm)
				* (doom->weapon[i].fire_frames
					+ doom->weapon[i].reload_frames));
		if (!doom->weapon[i].bxpm)
			error_msg("Weapon bxpm array nb %d.", i);
	}
}

void	init_weapons(t_doom *doom)
{
	init_shotgun(doom, &doom->weapon[0]);
	init_glock(doom, &doom->weapon[1]);
	init_minigun(doom, &doom->weapon[2]);
	init_kar98(doom, &doom->weapon[3]);
	init_pump(doom, &doom->weapon[4]);
	weapon_texture_array(doom);
}
