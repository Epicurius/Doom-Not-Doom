/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_aiming.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 15:55:17 by nneronin          #+#    #+#             */
/*   Updated: 2020/11/10 16:54:22 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	wasd(t_doom *doom, t_xyz *move)
{
	float speed;

	speed = doom->key.l_shift == 1 ? SPRINT_SPEED : WALK_SPEED; 
	if (doom->key.w)
	{
		move->x += PLAYER.anglecos * speed;
		move->y += PLAYER.anglesin * speed;
	}
	if (doom->key.s)
	{
		move->x -= PLAYER.anglecos * speed;
		move->y -= PLAYER.anglesin * speed;
	}
	if (doom->key.a)
	{
		move->x += PLAYER.anglesin * speed;
		move->y -= PLAYER.anglecos * speed;
	}
	if (doom->key.d)
	{
		move->x -= PLAYER.anglesin * speed;
		move->y += PLAYER.anglecos * speed;
	}
}

void	mouse_and_keys(t_doom *doom)
{
	int x;
	int y;
	t_xyz move;

	if (doom->key.space && PLAYER.ground)
	{
		PLAYER.velocity.z += 0.5; //mirror gravity
		PLAYER.falling = 1;
		doom->key.space = 0;
	}
	PLAYER.ducking = 0;
	if (doom->key.l_ctrl)
	{
		PLAYER.ducking = 1;
		PLAYER.falling = 1;
	}
	SDL_GetRelativeMouseState(&x, &y);
	PLAYER.angle += x * MOUSE_X;
	doom->yaw = clamp(doom->yaw + y * MOUSE_Y, -5, 5);
	PLAYER.yaw = doom->yaw - PLAYER.velocity.z * 0.5f;
	//move_player(doom, 0, 0);
	move = (t_xyz){0.f, 0.f};
	wasd(doom, &move);
	PLAYER.velocity.x = PLAYER.velocity.x * (1 - ACCELERATION) + move.x * ACCELERATION;
	PLAYER.velocity.y = PLAYER.velocity.y * (1 - ACCELERATION) + move.y * ACCELERATION;
	PLAYER.moving = 1;
}
