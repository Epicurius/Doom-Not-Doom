/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 10:52:28 by nneronin          #+#    #+#             */
/*   Updated: 2021/09/13 11:43:02 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
 *	Get the player speed, depending on if walking, sprinting and current FPS.
 *	Strafing speed is 80% of forward movement speed.
 */
//Quake 2.0
static void	get_base_speed(t_doom *doom, t_v2 *speed)
{
	if (doom->keys[SDL_SCANCODE_LSHIFT])
		speed->y = doom->player.sprint_speed;
	else
		speed->y = doom->player.walk_speed;
	speed->y *= doom->time.delta;
	speed->x = speed->y * 0.8;
}

/*
 *	Handle the footsteps sound and fadeout.
 */
static inline void	foot_steps(t_doom *doom, t_player *player)
{
	if ((doom->keys[SDL_SCANCODE_W] || doom->keys[SDL_SCANCODE_S]
			|| doom->keys[SDL_SCANCODE_A] || doom->keys[SDL_SCANCODE_D])
		&& floor_at(&doom->sectors[player->sector], player->where) >= player->where.z)// + 0.1
	{
		if (!Mix_Playing(CHANNEL_STEPS))
			Mix_PlayChannel(CHANNEL_STEPS, doom->sound[WAV_FOOT_STEPS], -1);
	}
	else if (Mix_Playing(CHANNEL_STEPS))
	{
		Mix_FadeOutChannel(CHANNEL_STEPS, 600);
		Mix_HaltChannel(CHANNEL_STEPS);
	}	
}

/*
 *	Get the direction the player is moving.
 *	z if the player is flying.
 */
static void	get_movement(t_doom *doom, t_player *player, t_v2 *speed)
{
	if (doom->keys[SDL_SCANCODE_W])
	{
		player->wishdir.x += player->anglecos * speed->y;
		player->wishdir.y += player->anglesin * speed->y;
		if (player->flight)
			player->wishdir.z += -player->pitch * player->sprint_speed;
	}
	if (doom->keys[SDL_SCANCODE_S])
	{
		player->wishdir.x += player->anglecos * -speed->y;
		player->wishdir.y += player->anglesin * -speed->y;
		if (player->flight)
			player->wishdir.z += player->pitch * player->sprint_speed;
	}
	if (doom->keys[SDL_SCANCODE_A])
	{
		player->wishdir.x += player->anglesin *  speed->x;
		player->wishdir.y += player->anglecos * -speed->x;
	}
	if (doom->keys[SDL_SCANCODE_D])
	{
		player->wishdir.x += player->anglesin * -speed->x;
		player->wishdir.y += player->anglecos *  speed->x;
	}
	foot_steps(doom, player);
}

/*
 *	Calculates the velocity depending on player movement and jump.
 */
static void	get_velocity(t_doom *doom)
{
	t_player	*player;
	t_sector	*sector;

	player = &doom->player;
	sector = &doom->sectors[player->sector];
	if (doom->keys[SDL_SCANCODE_SPACE] && player->where.z
		<= floor_at(sector, player->where) + 0.1)
	{
		Mix_PlayChannel(CHANNEL_JUMP, doom->sound[WAV_JUMP], 0);
		player->velocity.z = doom->player.jump_height;
	}
	player->velocity.x = doom->player.wishdir.x;
	player->velocity.y = doom->player.wishdir.y;
	if (player->flight)
		player->velocity.z = doom->player.wishdir.z;
}

/*
 *	Calculates the velocity depending on player movement and jump.
 */
# define MAX_SPEED			3.2
# define MAX_ACCEL			(10.0 * MAX_SPEED)
# define MAX_ACCEL_AIR		0.3
# define GROUND_FRICTION	4.0
# define STOP_SPEED			1.0

static void	get_velocity_v2(t_doom *doom, t_player *player)
{
	double speed;
	double wishspeed;
	double currentspeed;
	double accelspeed;
	
	wishspeed = normalize_v3(&player->wishdir);
	if (wishspeed > MAX_SPEED)
	{
		player->wishdir = mult_v3(player->wishdir, MAX_SPEED / wishspeed);
		wishspeed = MAX_SPEED;
	}
	if (player->where.z <= floor_at(&doom->sectors[player->sector], player->where))
	{
		speed = sqrt(player->velocity.x * player->velocity.x + player->velocity.y * player->velocity.y);
		if (speed)
		{
			speed = ft_fmax(0, speed - doom->time.delta * ft_fmax(speed, STOP_SPEED) * GROUND_FRICTION) / speed;
			player->velocity.x *= speed;
			player->velocity.y *= speed;
		}
		if (doom->keys[SDL_SCANCODE_SPACE])
		{
			Mix_PlayChannel(CHANNEL_JUMP, doom->sound[WAV_JUMP], 0);
			player->velocity.z = player->jump_height;
		}
	}
	else if (wishspeed > MAX_ACCEL_AIR)
			wishspeed = MAX_ACCEL_AIR;	
	currentspeed = dot_product_v3(player->velocity, player->wishdir);
	accelspeed = ft_fclamp(wishspeed - currentspeed, 0, MAX_ACCEL * doom->time.delta * wishspeed);
	player->velocity.x += player->wishdir.x * accelspeed;
	player->velocity.y += player->wishdir.y * accelspeed;
	if (player->flight)
		player->velocity.z += player->wishdir.z * accelspeed;
}

/*
 *	Handels all the player movement.
 */
void	movement(t_doom *doom)
{
	t_v2		speed;
	t_motion	motion;

	if (doom->keys[SDL_SCANCODE_LCTRL])
		doom->player.eyelvl = PLAYER_HEIGHT - 4;
	else if (doom->player.eyelvl == PLAYER_HEIGHT - 4
		&& !crouch_collision(doom, &doom->player))
		doom->player.eyelvl = PLAYER_HEIGHT - 1;
	update_camera(doom);
	ft_bzero(&doom->player.wishdir, sizeof(t_v3));
	get_base_speed(doom, &speed);
	get_movement(doom, &doom->player, &speed);
	get_velocity_v2(doom, &doom->player);
	if (entity_collision(doom, &doom->player.where, &doom->player.velocity))
		return ;
	motion.height = doom->player.eyelvl + 1;
	motion.sector = doom->player.sector;
	motion.flight = doom->player.flight;
	doom->player.sector = collision_detection(doom, motion,
			&doom->player.where, &doom->player.velocity);
	if (doom->player.sector == -1)
		doom->player.health = 0;
}
