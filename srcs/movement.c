/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 10:52:28 by nneronin          #+#    #+#             */
/*   Updated: 2021/08/31 10:37:12 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
 *	Get the player speed, depending on if walking, sprinting and current FPS.
 */
static void	get_base_speed(t_doom *doom, float *speed)
{
	if (doom->keys[SDL_SCANCODE_LSHIFT])
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
	if ((doom->keys[SDL_SCANCODE_W] || doom->keys[SDL_SCANCODE_S]
			|| doom->keys[SDL_SCANCODE_A] || doom->keys[SDL_SCANCODE_D])
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
	if (doom->keys[SDL_SCANCODE_W])
	{
		move->x += player.anglecos * speed;
		move->y += player.anglesin * speed;
		if (player.flight)
			move->z += -player.pitch * doom->player.sprint_speed;
	}
	if (doom->keys[SDL_SCANCODE_S])
	{
		move->x += player.anglecos * -speed;
		move->y += player.anglesin * -speed;
		if (player.flight)
			move->z += player.pitch * doom->player.sprint_speed;
	}
	if (doom->keys[SDL_SCANCODE_A])
	{
		move->x += player.anglesin * speed;
		move->y += player.anglecos * -speed;
	}
	if (doom->keys[SDL_SCANCODE_D])
	{
		move->x += player.anglesin * -speed;
		move->y += player.anglecos * speed;
	}
	foot_steps(doom, player);
}

/*
 *	Calculates the velocity depending on player movement and jump.
 */
static void	get_velocity(t_doom *doom, t_v3 move)
{
	t_player	*player;
	t_sector	*sector;

	player = &doom->player;
	sector = &doom->sectors[player->sector];
	if (doom->keys[SDL_SCANCODE_SPACE] && player->where.z
		<= floor_at(sector, player->where) + 0.1)
	{
		Mix_PlayChannel(CHANNEL_JUMP, doom->sound[WAV_JUMP], 0);
		player->velocity.z += 25.5;//doom->player.jump_height;
	}
	player->velocity.x = move.x;
	player->velocity.y = move.y;
	if (player->flight)
		player->velocity.z = move.z;
}

/*
 *	Handels all the player movement.
 */
void	movement(t_doom *doom)
{
	t_v3		move;
	float		speed;
	t_motion	motion;

	if (doom->keys[SDL_SCANCODE_LCTRL])
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
