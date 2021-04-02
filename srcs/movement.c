
#include "doom.h"

void	get_base_speed(t_doom *doom, float *speed)
{
	Uint32 time;

	time = SDL_GetTicks() - doom->fps.curr;
	//if (PLAYER.ducking)
	//	*speed = CROUCH_SPEED;
	if (doom->key.l_shift)
		*speed = SPRINT_SPEED;
	else
		*speed = WALK_SPEED;
	*speed *= time;
}


void	get_movement(t_doom *doom, float speed, t_xyz *move)
{
	*move = xyz(0, 0, 0);
	if (doom->key.w)
	{
		move->x += PLAYER.anglecos * speed;
		move->y += PLAYER.anglesin * speed;
		move->z += PLAYER.flying ? -PLAYER.pitch * speed : 0;
	}
	if (doom->key.s)
	{
		move->x += PLAYER.anglecos * -speed;
		move->y += PLAYER.anglesin * -speed;
		move->z += PLAYER.flying ? PLAYER.pitch * speed : 0;
	}
	if (doom->key.a)
	{
		move->x += PLAYER.anglesin * speed;
		move->y += PLAYER.anglecos * -speed;
	}
	if (doom->key.d)
	{
		move->x += PLAYER.anglesin * -speed;
		move->y += PLAYER.anglecos * speed;
	}
}

void	get_velocity(t_doom *doom, t_xyz move)
{
	t_player *player;

	player = &doom->player;
	if (doom->key.space && player->where.z == doom->sectors[player->sector].floor.y)
		player->velocity.z += 0.5;
	player->velocity.x = (player->velocity.x + move.x) * ACCELERATION;
	player->velocity.y = (player->velocity.y + move.y) * ACCELERATION;
	if (!player->flying)
		return ;
	player->velocity.z = (player->velocity.z + move.z) * ACCELERATION;
}

void	movement(t_doom *doom)
{
	int x;
	int y;
	t_xyz move;
	float speed;

	SDL_GetRelativeMouseState(&x, &y);
	update_camera(doom, x, y);
	get_base_speed(doom, &speed);
	get_movement(doom, speed, &move);
	get_velocity(doom, move);
	//doom->player.dest = sum_xyz(doom->player.where, doom->player.velocity);
}
