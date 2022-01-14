/*
 * https://github.com/Epicurius/Doom-Not-Doom
 * 
 * Created: 2021/05/05 10:27:28 nneronin
 * Updated: 2022/01/07 16:16:05 nneronin
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
		LG_ERROR("Malloc img pos\n");
	if (!malloc_state_frames_and_angles(entity, IDLE))
		LG_ERROR("Malloc img pos IDLE\n");
	if (!malloc_state_frames_and_angles(entity, MOVE))
		LG_ERROR("Malloc img pos MOVE\n");
	if (!malloc_state_frames_and_angles(entity, ATTACK))
		LG_ERROR("Malloc img pos ATTACK\n");
	if (!malloc_state_frames_and_angles(entity, DEATH))
		LG_ERROR("Malloc img pos DEATH\n");
}
