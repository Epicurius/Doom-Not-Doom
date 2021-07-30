/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 10:52:28 by nneronin          #+#    #+#             */
/*   Updated: 2021/07/30 15:23:21 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	get_base_speed(t_doom *doom, float *speed)
{
	if (doom->keys[KEY_LSHIFT])
		*speed = doom->player.sprint_speed;
	else
		*speed = doom->player.walk_speed;
	*speed *= doom->time.delta;
}

static inline void	foot_steps(t_doom *doom, t_player player)
{
	if ((doom->keys[KEY_W] || doom->keys[KEY_S] || doom->keys[KEY_A] || doom->keys[KEY_D])
		&& player.where.z <= get_floor_at_pos(&doom->sectors[player.sector],
			player.where))
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

static void	get_velocity(t_doom *doom, t_v3 move)
{
	t_player	*player;
	t_sector	*sector;

	player = &doom->player;
	sector = &doom->sectors[player->sector];
	if (doom->keys[KEY_SPACE]
		&& player->where.z <= get_floor_at_pos(sector, player->where) + 0.1)
	{
		Mix_PlayChannel(CHANNEL_JUMP, doom->sound[WAV_JUMP], 0);
		player->velocity.z += (0.5 + doom->player.jump_height);
	}
	player->velocity.x = (player->velocity.x + move.x) * ACCELERATION;
	player->velocity.y = (player->velocity.y + move.y) * ACCELERATION;
	if (player->flight)
		player->velocity.z = (player->velocity.z + move.z) * ACCELERATION;
}

void	movement(t_doom *doom)
{
	int			x;
	int			y;
	t_v3		move;
	float		speed;
	t_motion	motion;

	if (doom->player.where.z + doom->player.eyelvl + 2 < doom->sectors[doom->player.sector].ceiling.y)
		doom->player.eyelvl = PLAYER_HEIGHT - 1;
	if (doom->keys[KEY_LCTRL])
		doom->player.eyelvl = PLAYER_HEIGHT - 4;
	SDL_GetRelativeMouseState(&x, &y);
	update_camera(doom, x, y);
	get_base_speed(doom, &speed);
	ft_bzero(&move, sizeof(t_v3));
	get_movement(doom, doom->player, speed, &move);
	get_velocity(doom, move);
	if (entity_collision(doom, &doom->player.where, &doom->player.velocity))
		return ;
	motion.height = doom->player.eyelvl + 1;
	motion.curr_sect = doom->player.sector;
	motion.flight = doom->player.flight;
	doom->player.sector = collision_detection(doom, motion,
			&doom->player.where, &doom->player.velocity);
	if (doom->player.sector == -1)
		doom->player.health = 0;
}
