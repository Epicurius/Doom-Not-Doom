/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 10:52:28 by nneronin          #+#    #+#             */
/*   Updated: 2021/07/29 11:49:40 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	print_v3(char *str, t_v3 v)
{
	if (str)
		ft_printf("%s\t", str);
	ft_printf("[%.2f\t%.2f\t%.2f]\n", v.x, v.y, v.z);
}

static void	get_base_speed(t_doom *doom, float *speed)
{
	if (doom->key.lshift)
		*speed = doom->player.sprint_speed;
	else
		*speed = doom->player.walk_speed;
	*speed *= doom->time.delta;
}

static inline void	foot_steps(t_doom *doom, t_player player)
{
	if ((doom->key.w || doom->key.s || doom->key.a || doom->key.d)
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
	if (doom->key.w)
	{
		move->x += player.anglecos * speed;
		move->y += player.anglesin * speed;
		if (player.flying)
			move->z += -player.pitch * speed;
	}
	if (doom->key.s)
	{
		move->x += player.anglecos * -speed;
		move->y += player.anglesin * -speed;
		if (player.flying)
			move->z += player.pitch * speed;
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
	foot_steps(doom, player);
}

static void	get_velocity(t_doom *doom, t_v3 move)
{
	t_player	*player;
	t_sector	*sector;

	player = &doom->player;
	sector = &doom->sectors[player->sector];
	if (doom->key.space
		&& player->where.z <= get_floor_at_pos(sector, player->where) + 0.1)
	{
		Mix_PlayChannel(CHANNEL_JUMP, doom->sound[WAV_JUMP], 0);
		player->velocity.z += (0.5 + doom->player.jump_height);
	}
	player->velocity.x = (player->velocity.x + move.x) * ACCELERATION;
	player->velocity.y = (player->velocity.y + move.y) * ACCELERATION;
	//if (!player->flying)
	//{
	//	if (doom->player.where.z > get_floor_at_pos(sector, player->where))
	//		player->velocity.z -= sector->gravity;
	//}
	//else
	//	player->velocity.z = (player->velocity.z + move.z) * ACCELERATION;
	if (player->flying)
		player->velocity.z = (player->velocity.z + move.z) * ACCELERATION;
}

t_motion	new_motion(int sector, double size_2d, double eyesight, t_v3 where)
{
	t_motion motion;

	motion.sector = sector;
	motion.size_2d = size_2d;
	motion.eyesight = eyesight;
	motion.height = motion.eyesight + 1;
	motion.where = where;
	motion.suffocate = 0;
	return (motion);
}

void	movement(t_doom *doom)
{
	int		x;
	int		y;
	t_v3	move;
	float	speed;

	if (doom->player.where.z + doom->player.eye_lvl + 2
		< doom->sectors[doom->player.sector].ceiling.y)
		doom->player.eye_lvl = EYE_LVL;
	if (doom->key.lctr)
		doom->player.eye_lvl = 4;
	SDL_GetRelativeMouseState(&x, &y);
	update_camera(doom, x, y);
	get_base_speed(doom, &speed);
	ft_bzero(&move, sizeof(t_v3));
	get_movement(doom, doom->player, speed, &move);
	get_velocity(doom, move);

	t_motion motion = new_motion(doom->player.sector, 0.75, doom->player.eye_lvl, doom->player.where);
	motion.flight = doom->player.flying;
	motion.lowest_ceiling = find_lowest_ceiling(doom, motion);
	doom->player.velocity = bb_collision_detection(doom, doom->player.velocity, motion);
	doom->player.where = add_v3(doom->player.where, doom->player.velocity);


	//ft_printf("Sect: %d\t", doom->player.sector);
	//print_v3("pos:", doom->player.where);
	if (doom->player.where.z < get_floor_at_pos(&doom->sectors[motion.sector], doom->player.where))
	{
		//printf("Player under sector\n");
		doom->player.velocity.z = 0;
		doom->player.where.z = get_floor_at_pos(&doom->sectors[motion.sector], doom->player.where);////////
	}
	//ft_printf("%f %d\n",doom->player.where.z, doom->player.sector);
	//doom->player.sector = find_sector(doom->sectors, doom->nb.sectors, doom->player.where);
	//ft_printf("%f %f %f\n", move.x, move.y, move.z);
	//ft_printf("PLAYER SECTOR: %d\n", doom->player.sector);
	//player_collision(doom);
}
