/*
 * https://github.com/Epicurius/Doom-Not-Doom
 * 
 * Created: 2021/05/04 12:23:36 nneronin
 * Updated: 2021/12/10 18:13:34 nneronin
 */

#include "doom.h"

/*
 *	Handels launcher projectile.
 *	Spawns a projectile and calculates it velocity.
 */
static void	fire_orb(t_doom *doom)
{
	t_projectile	*orb;

	orb = protalloc(sizeof(t_projectile));
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
			if (doom->player.equipped == WEAPON_LAUNCHER)
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
	if (doom->weapon[WEAPON_SHOTGUN].own && doom->keys[SDL_SCANCODE_1])
		doom->player.equipped = WEAPON_SHOTGUN;
	else if (doom->weapon[WEAPON_GUN].own && doom->keys[SDL_SCANCODE_2])
		doom->player.equipped = WEAPON_GUN;
	else if (doom->weapon[WEAPON_KAR].own && doom->keys[SDL_SCANCODE_3])
		doom->player.equipped = WEAPON_KAR;
	else if (doom->weapon[WEAPON_LAUNCHER].own && doom->keys[SDL_SCANCODE_4])
		doom->player.equipped = WEAPON_LAUNCHER;
	else if (doom->weapon[WEAPON_MINIGUN].own && doom->keys[SDL_SCANCODE_5])
		doom->player.equipped = WEAPON_MINIGUN;
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
