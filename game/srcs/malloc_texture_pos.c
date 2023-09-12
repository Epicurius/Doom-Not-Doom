/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Niklas Neronin <niklas.neronin@gmail.com>
 */

#include "doom.h"

/*
 *	Handles the mallocing of the entity state frame position array. (t_rect)
 *	According to the amount of frame for each action aswell as angles.
 */
static int	malloc_state_frames_and_angles(t_frames *entity, int state)
{
	int	i;

	i = -1;
	if (entity->nb[state][FRAMES] <= 0)
		return (1);
	entity->pos[state] = protalloc(sizeof(t_rect *)
			* entity->nb[state][FRAMES]);
	if (!entity->pos[state])
		return (0);
	while (++i < entity->nb[state][FRAMES])
	{
		entity->pos[state][i] = protalloc(sizeof(t_rect)
				* entity->nb[state][ANGLES]);
		if (!entity->pos[state][i])
			return (0);
	}
	return (1);
}

/*
 *	Handles the mallocing of the entity state array. (t_rect)
 *	IDLE, MOVE, ATTACK, DEATH.
 */
void	malloc_texture_pos(t_frames *entity)
{
	entity->pos = (t_rect ***)protalloc(sizeof(t_rect **) * 4);
	if (!entity->pos)
		LG_ERROR("Malloc img pos.");
	if (!malloc_state_frames_and_angles(entity, IDLE))
		LG_ERROR("Malloc img pos IDLE.");
	if (!malloc_state_frames_and_angles(entity, MOVE))
		LG_ERROR("Malloc img pos MOVE.");
	if (!malloc_state_frames_and_angles(entity, ATTACK))
		LG_ERROR("Malloc img pos ATTACK.");
	if (!malloc_state_frames_and_angles(entity, DEATH))
		LG_ERROR("Malloc img pos DEATH.");
}
