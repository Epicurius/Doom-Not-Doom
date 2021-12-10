/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_weapons.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 13:47:18 by nneronin          #+#    #+#             */
/*   Updated: 2021/12/10 18:06:17 by nneronin         ###   ########.fr       */
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
	init_shotgun(doom, &doom->weapon[WEAPON_SHOTGUN]);
	init_glock(doom, &doom->weapon[WEAPON_GUN]);
	init_minigun(doom, &doom->weapon[WEAPON_MINIGUN]);
	init_kar98(doom, &doom->weapon[WEAPON_KAR]);
	init_launcher(doom, &doom->weapon[WEAPON_LAUNCHER]);
	weapon_texture_array(doom);
}
