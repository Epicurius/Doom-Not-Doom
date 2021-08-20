/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 10:52:28 by nneronin          #+#    #+#             */
/*   Updated: 2021/08/15 17:20:42 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
 *	Get the player speed, depending on if walking, sprinting and current FPS.
 */
static void	get_base_speed(t_doom *doom, float *speed)
{
	if (doom->keys[KEY_LSHIFT])
		*speed = doom->player.sprint_speed;
	else
		*speed = doom->player.walk_speed;
	*speed *= doom->time.delta;
}

/*
 *	Handle the footsteps sound and fadeout.
 */
static inline void	foot_steps(t_doom *doom, t_player player)
{
	if ((doom->keys[KEY_W] || doom->keys[KEY_S]
			|| doom->keys[KEY_A] || doom->keys[KEY_D])
		&& floor_at(&doom->sectors[player.sector], player.where) + 0.01
		>= player.where.z)
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
static void	get_movement(t_doom *doom, t_player player, float speed, t_v3 *move)
{
	if (doom->keys[KEY_W])
	{
		move->x += player.anglecos * speed;
		move->y += player.anglesin * speed;
		if (player.flight)
			move->z += -player.pitch * speed;
	}
	if (doom->keys[KEY_S])
	{
		move->x += player.anglecos * -speed;
		move->y += player.anglesin * -speed;
		if (player.flight)
			move->z += player.pitch * speed;
	}
	if (doom->keys[KEY_A])
	{
		move->x += player.anglesin * speed;
		move->y += player.anglecos * -speed;
	}
	if (doom->keys[KEY_D])
	{
		move->x += player.anglesin * -speed;
		move->y += player.anglecos * speed;
	}
	foot_steps(doom, player);
}

/*
 *	Calculates the velocity depending on player movement and jump.
 */
//player->velocity.x = (player->velocity.x + move.x) * ACCELERATION;
//player->velocity.y = (player->velocity.y + move.y) * ACCELERATION;
//if (player->flight)
//	player->velocity.z = (player->velocity.z + move.z) * ACCELERATION;
//if (player->velocity.x < 0.001 && player->velocity.x > -0.001)
//	player->velocity.x = 0.0;
//if (player->velocity.y < 0.001 && player->velocity.y > -0.001)
//	player->velocity.y = 0.0;
static void	get_velocity(t_doom *doom, t_v3 move)
{
	t_player	*player;
	t_sector	*sector;

	player = &doom->player;
	sector = &doom->sectors[player->sector];
	if (doom->keys[KEY_SPACE] && player->where.z
		<= floor_at(sector, player->where) + 0.1)
	{
		//Mix_PlayChannel(CHANNEL_JUMP, doom->sound[WAV_JUMP], 0);
		player->velocity.z += (0.5 + doom->player.jump_height);
	}
	player->velocity.x = move.x * 3.5;
	player->velocity.y = move.y * 3.5;
	if (player->flight)
		player->velocity.z = move.z * 3.5;
}

/*
 *	Handels all the player movement.
 */
void	movement(t_doom *doom)
{
	t_v3		move;
	float		speed;
	t_motion	motion;

	if (doom->keys[KEY_LCTRL])
		doom->player.eyelvl = PLAYER_HEIGHT - 4;
	else if (doom->player.eyelvl == PLAYER_HEIGHT - 4
		&& !crouch_collision(doom, &doom->player))
		doom->player.eyelvl = PLAYER_HEIGHT - 1;
	update_camera(doom);
	get_base_speed(doom, &speed);
	ft_bzero(&move, sizeof(t_v3));
	get_movement(doom, doom->player, speed, &move);
	get_velocity(doom, move);
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
