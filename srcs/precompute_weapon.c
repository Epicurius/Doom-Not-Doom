/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precompute_weapon.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 12:23:36 by nneronin          #+#    #+#             */
/*   Updated: 2021/08/01 15:09:27 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	fire_orb(t_doom *doom)
{
	t_projectile	*orb;

	orb = protalloc(sizeof(t_projectile), "player_projectile");
	orb->velocity.x = cos(doom->player.pitch) * doom->player.anglecos;
	orb->velocity.y = cos(doom->player.pitch) * doom->player.anglesin;
	orb->velocity.z = -sin(doom->player.pitch);
	orb->where = doom->player.where;
	orb->where.z += 4.5;
	orb->where = add_v3(orb->where, mult_v3(orb->velocity, 5));
	orb->start = orb->where;
	orb->sector = doom->player.sector;
	orb->target = 1;
	orb->range = PLAYER_PROJECTILE_MAX_RANGE;
	ft_lstadd_new(&doom->orb, orb, sizeof(t_projectile));
	doom->nb.projectiles += 1;
}

void	weapon_fire_animate(t_doom *doom, t_weapon *weapon)
{
	if (weapon->frame == 0 && weapon->mag_ammo > 0)
		Mix_PlayChannel(CHANNEL_WEAPON, doom->sound[weapon->sound], 0);
	if (doom->time.curr - weapon->time > weapon->frame_rate)
	{
		if (!weapon->frame)
		{
			if (doom->player.equiped == 4)
				fire_orb(doom);
			else
				doom->player.action = SHOOTING;
			weapon->mag_ammo -= 1;
		}
		weapon->frame++;
		weapon->time = doom->time.curr;
	}
	if (weapon->frame >= weapon->fire_frames)
		weapon->frame = 0;
}

void	weapon_reload_animate(t_doom *doom, t_weapon *weapon)
{
	if (!weapon->frame)
		weapon->frame = weapon->fire_frames;
	if (doom->time.curr - weapon->time > weapon->frame_rate)
	{
		weapon->frame++;
		weapon->time = doom->time.curr;
	}
	if (weapon->frame >= weapon->reload_frames + weapon->fire_frames
		|| !weapon->reload_frames)
	{
		weapon->frame = 0;
		weapon->mag_ammo = ft_min(weapon->mag_size, weapon->cur_ammo);
		weapon->cur_ammo -= ft_min(weapon->mag_size, weapon->cur_ammo);
	}
}

void	equip_weapon(t_doom *doom)
{
	if (doom->weapon[0].own && doom->keys[KEY_1])
		doom->player.equiped = 0;
	else if (doom->weapon[1].own && doom->keys[KEY_2])
		doom->player.equiped = 1;
	else if (doom->weapon[2].own && doom->keys[KEY_3])
		doom->player.equiped = 2;
	else if (doom->weapon[3].own && doom->keys[KEY_4])
		doom->player.equiped = 3;
	else if (doom->weapon[4].own && doom->keys[KEY_5])
		doom->player.equiped = 5;
}

//		move doom->player.action = NONE;
void	precompute_weapon(t_doom *doom)
{
	t_weapon	*weapon;

	doom->player.action = NONE;
	equip_weapon(doom);
	if (doom->player.equiped < 0)
		return ;
	weapon = &doom->weapon[doom->player.equiped];
	if ((weapon->frame && (weapon->frame < weapon->fire_frames))
		|| (doom->keys[MOUSE_LEFT] && weapon->mag_ammo > 0))
		weapon_fire_animate(doom, weapon);
	else if (!weapon->frame && doom->keys[MOUSE_LEFT] && weapon->mag_ammo <= 0)
		Mix_PlayChannel(CHANNEL_WEAPON, doom->sound[WAV_EMPTY_CLIP], 0);
	else if (weapon->frame >= weapon->fire_frames)
		weapon_reload_animate(doom, weapon);
	else if (doom->keys[KEY_R] && !weapon->frame
		&& !weapon->mag_ammo && weapon->cur_ammo)
		weapon_reload_animate(doom, weapon);
}
