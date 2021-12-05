/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precompute_weapon.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 12:23:36 by nneronin          #+#    #+#             */
/*   Updated: 2021/12/05 15:47:32 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
 *	Handels launcher projectile.
 *	Spawns a projectile and calculates it velocity.
 */
static void	fire_orb(t_doom *doom)
{
	t_projectile	*orb;

	orb = PROT_ALLOC(sizeof(t_projectile));
	orb->velocity.x = doom->player.anglecos;
	orb->velocity.y = doom->player.anglesin;
	orb->velocity.z = -sin(doom->player.pitch);
	orb->where = doom->player.where;
	orb->where.z += 2.5;
	orb->where = add_v3(orb->where, mult_v3(orb->velocity, 5));
	orb->velocity = mult_v3(orb->velocity, 70);
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
			if (doom->player.equipped == 4)
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
 *	Checks witch weapon player has equipped.
 */
void	equip_weapon(t_doom *doom)
{
	if (doom->weapon[0].own && doom->keys[SDL_SCANCODE_1])
		doom->player.equipped = 0;
	else if (doom->weapon[1].own && doom->keys[SDL_SCANCODE_2])
		doom->player.equipped = 1;
	else if (doom->weapon[2].own && doom->keys[SDL_SCANCODE_3])
		doom->player.equipped = 2;
	else if (doom->weapon[3].own && doom->keys[SDL_SCANCODE_4])
		doom->player.equipped = 3;
	else if (doom->weapon[4].own && doom->keys[SDL_SCANCODE_5])
		doom->player.equipped = 4;
}

/*
 *	Handels all the player weapon calculations.
 *	TODO: "move doom->player.action = NONE" some where else
 *	makes not sense or int to be here.
 */
void	precompute_weapon(t_doom *doom)
{
	t_weapon	*weapon;

	doom->player.action = NONE;
	equip_weapon(doom);
	if (doom->player.equipped < 0)
		return ;
	weapon = &doom->weapon[doom->player.equipped];
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
