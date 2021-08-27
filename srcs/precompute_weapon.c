/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precompute_weapon.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 12:23:36 by nneronin          #+#    #+#             */
/*   Updated: 2021/08/27 14:53:27 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
 *	Handels launcher projectile.
 *	Spawns a projectile and calulates it velocity.
 */
static void	fire_orb(t_doom *doom)
{
	t_projectile	*orb;

	orb = PROT_ALLOC(sizeof(t_projectile));
	orb->velocity.x = doom->player.anglecos;
	orb->velocity.y = doom->player.anglesin;
	orb->velocity.z = -sin(doom->player.pitch);
	orb->where = doom->player.where;
	orb->where.z += 4.5;
	orb->where = add_v3(orb->where, mult_v3(orb->velocity, 5));
	orb->velocity = mult_v3(orb->velocity, 3);
	orb->start = orb->where;
	orb->sector = doom->player.sector;
	orb->target = 1;
	orb->range = PLAYER_PROJECTILE_MAX_RANGE;
	ft_lstadd_new(&doom->orb, orb, sizeof(t_projectile));
	doom->nb.projectiles += 1;
}

/*
 *	Handels weapon fire frames.
 */
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

/*
 *	Handels weapon reload frames.
 */
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

/*
 *	Checks witch weapon player has equiped.
 */
void	equip_weapon(t_doom *doom)
{
	if (doom->weapon[0].own && doom->keys[SDL_SCANCODE_1])
		doom->player.equiped = FALSE;
	else if (doom->weapon[1].own && doom->keys[SDL_SCANCODE_2])
		doom->player.equiped = TRUE;
	else if (doom->weapon[2].own && doom->keys[SDL_SCANCODE_3])
		doom->player.equiped = 2;
	else if (doom->weapon[3].own && doom->keys[SDL_SCANCODE_4])
		doom->player.equiped = 3;
	else if (doom->weapon[4].own && doom->keys[SDL_SCANCODE_5])
		doom->player.equiped = 5;
}

/*
 *	Handels all the player weapon calulations.
 *	TODO: "move doom->player.action = NONE" some where else
 *	makes not sense or int to be here.
 */
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
	else if (doom->keys[SDL_SCANCODE_R] && !weapon->frame
		&& !weapon->mag_ammo && weapon->cur_ammo)
		weapon_reload_animate(doom, weapon);
}
