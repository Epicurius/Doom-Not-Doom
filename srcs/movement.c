
#include "doom.h"

void	get_velocity(t_doom *doom, float *speed)
{
	Uint32 time;

	time = SDL_GetTicks() - doom->fps.curr;
	if (PLAYER.ducking)
		*speed = CROUCH_SPEED;
	else if (doom->key.l_shift)
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

void	movement(t_doom *doom)
{
	int x;
	int y;
	t_xyz move;
	float speed;

	SDL_GetRelativeMouseState(&x, &y);
	update_camera(doom, x, y);
	//doom->player.ducking = (doom->key.l_ctrl && doom->player.ground);
	get_velocity(doom, &speed);
	get_movement(doom, speed, &move);
	PLAYER.velocity.x = (PLAYER.velocity.x + move.x) * ACCELERATION;
	PLAYER.velocity.y = (PLAYER.velocity.y + move.y) * ACCELERATION;
	if (PLAYER.flying)
		PLAYER.velocity.z = (PLAYER.velocity.z + move.z) * ACCELERATION;
	if (doom->key.space && doom->player.ground && !doom->player.ducking)
	{
		doom->player.velocity.z += 0.5;
		doom->player.ground = 0;
	}
}
