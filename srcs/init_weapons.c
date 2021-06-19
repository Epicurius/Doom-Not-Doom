/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_weapons.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 13:47:18 by nneronin          #+#    #+#             */
/*   Updated: 2021/06/19 17:17:12 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	init_weapons(t_doom *doom)
{
	init_shotgun(doom, &doom->weapon[0]);
	init_gun(doom, &doom->weapon[1]);
	init_minigun(doom, &doom->weapon[2]);
	init_kar98(doom, &doom->weapon[3]);
	init_pump(doom, &doom->weapon[4]);
	load_shotgun(&doom->weapon[0]);
	load_gun(&doom->weapon[1]);
	load_mini(&doom->weapon[2]);
	load_kar(&doom->weapon[3]);
	load_pump(&doom->weapon[4]);
}
