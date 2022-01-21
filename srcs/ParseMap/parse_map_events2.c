/*
 * https://github.com/Epicurius/Doom-Not-Doom
 * 
 * Created: 2021/07/05 09:00:24 nneronin
 * Updated: 2022/01/21 14:03:03 Niklas Neronin
 */

#include "doom.h"

/*
 *	Parse Floor or Ceiling event args.
 */
void	floor_ceiling_event(t_event *event, int nb, char **arr)
{
	if (nb < 7)
		LG_ERROR("Invalid argument for event %s.", arr[0]);
	event->event_sector = ft_atoi(arr[4]);
	event->dir = -1;
	if (event->type == CEILING)
		event->dir = 1;
	event->min = ft_atof(arr[5]);
	event->max = ft_atof(arr[6]);
	event->dir = ft_atof(arr[7]);
	if (event->dir != 1 && event->dir != -1)
		LG_ERROR("Event dir must be -1 or 1 not %d.", event->dir);
	event->speed = 10;
}

/*
 *	Parse Spawn event args.
 *	event->yaw = ft_atoi(arr[8]) * CONVERT_TO_RADIANS;
 */
void	spawn_event(t_doom *doom, t_event *event, int nb, char **arr)
{
	if (nb < 8)
		LG_ERROR("Invalid argument for event %s.", arr[0]);
	if (event->type == NONE)
		LG_ERROR("Event 'Spawn' can`t have action NONE");
	event->entity = ft_atoi(arr[4]);
	event->pos = mult_v3(new_v3(ft_atof(arr[5]),
				ft_atof(arr[6]), ft_atof(arr[7])), doom->map_scale);
}

/*
 *	Parse Audio event args.
 */
void	audio_event(t_event *event, int nb, char **arr)
{
	if (nb < 4)
		LG_ERROR("Invalid argument for event %s.", arr[0]);
	if (event->action == NONE)
		LG_ERROR("Event 'Audio' can`t have action NONE");
	event->path = ft_strdup(arr[4]);
}

/*
 *	Parse Hazard event args.
 */
void	hazard_event(t_event *event, int nb, char **arr)
{
	if (nb < 7)
		LG_ERROR("Invalid argument for event %s.", arr[0]);
	if (event->action != SECTOR)
		LG_ERROR("Event 'Hazard' can only have SECTOR as an action.");
	event->event_sector = ft_atoi(arr[4]);
	event->speed = ft_atoi(arr[7]);
}

/*
 *	Parse Light event args.
 */
void	light_event(t_event *event, int nb, char **arr)
{
	if (nb < 5)
		LG_ERROR("Invalid argument for event %s.", arr[0]);
	event->event_sector = ft_atoi(arr[4]);
	event->light = ft_clamp(ft_atoi(arr[5]) + 100, 0, 199);
}
