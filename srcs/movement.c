/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 10:52:28 by nneronin          #+#    #+#             */
/*   Updated: 2021/06/16 16:21:05 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	get_base_speed(t_doom *doom, float *speed)
{
	if (doom->key.shift_l)
		*speed = doom->player.sprint_speed;
	else
		*speed = doom->player.walk_speed;
	*speed *= doom->time.delta;
}


void	get_movement(t_doom *doom, t_player player, float speed, t_v3 *move)
{
	*move = xyz(0, 0, 0);
	if (doom->key.w)
	{
		move->x += player.anglecos * speed;
		move->y += player.anglesin * speed;
		move->z += player.flying ? -player.pitch * speed : 0;
	}
	if (doom->key.s)
	{
		move->x += player.anglecos * -speed;
		move->y += player.anglesin * -speed;
		move->z += player.flying ? player.pitch * speed : 0;
	}
	if (doom->key.a)
	{
		move->x += player.anglesin * speed;
		move->y += player.anglecos * -speed;
	}
	if (doom->key.d)
	{
		move->x += player.anglesin * -speed;
		move->y += player.anglecos * speed;
	}
	if ((doom->key.w || doom->key.s || doom->key.a || doom->key.d)
			&& player.where.z == doom->sectors[player.sector].floor.y)
	{
		//if (!Mix_Playing(CHANNEL_STEPS))
			//Mix_PlayChannel(CHANNEL_STEPS, doom->sound[WAV_FOOT_STEPS], -1);
	}
	else if (Mix_Playing(CHANNEL_STEPS))
	{
		Mix_FadeOutChannel(CHANNEL_STEPS, 600);
		//Mix_HaltChannel(2);
	}
}

void	get_velocity(t_doom *doom, t_v3 move)
{
	t_player *player;
	t_sector *sector;

	player = &doom->player;
	sector = &doom->sectors[player->sector];
	if (doom->key.space && player->where.z == get_floor_at_pos(sector, player->where))
	{
		//Mix_PlayChannel(CHANNEL_STEPS, doom->sound[WAV_JUMP], 0);
		player->velocity.z += (0.5 + doom->player.jump_height);
	}
	player->velocity.x = (player->velocity.x + move.x) * ACCELERATION;
	player->velocity.y = (player->velocity.y + move.y) * ACCELERATION;
	if (!player->flying)
	{
		if (doom->player.where.z > get_floor_at_pos(sector, player->where))
			player->velocity.z -= sector->gravity;
	}
	else
		player->velocity.z = (player->velocity.z + move.z) * ACCELERATION;
}

void	movement(t_doom *doom)
{
	int x;
	int y;
	t_v3 move;
	float speed;

	if (doom->player.where.z + doom->player.eye_lvl + 2 < doom->sectors[doom->player.sector].ceiling.y)
		doom->player.eye_lvl = EYE_LVL;
	if (doom->key.ctr_l)
		doom->player.eye_lvl = 4;
	SDL_GetRelativeMouseState(&x, &y);
	update_camera(doom, x, y);
	get_base_speed(doom, &speed);
	get_movement(doom, doom->player, speed, &move);
	get_velocity(doom, move);
}
