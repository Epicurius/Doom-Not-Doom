
#include "doom.h"

//	Returns 1 if collision 0 if not
int	hitbox_collision(t_xyz dest, t_wall *wall)
{
	t_xyz point;

	//Dose player hitbox collide with vetex 1.
	if (point_distance_2d(wall->v1.x, wall->v1.y, dest.x, dest.y) <= PLAYER_RADIUS)
		return (1);
	//Dose player hitbox collide with vetex 2.
	if (point_distance_2d(wall->v2.x, wall->v2.y, dest.x, dest.y) <= PLAYER_RADIUS)
		return (2);
	point = closest_point_on_segment_2d(dest, wall->v1, wall->v2);
	//Dose player hitbox collide with vertex point closest to the wall.
	if (point_distance_2d(point.x, point.y, dest.x, dest.y) <= PLAYER_RADIUS)
		return (3);
	return (0);
}

int	fit_through_portal(t_doom *doom, t_sector *sector, t_wall *wall)
{
	double portal_top;
	double portal_bot;

	double eye_height = PLAYER.ducking ? DUCK_HEIGHT : EYE_HEIGHT;
	portal_bot = max(sector->floor.y, doom->sectors[wall->n].floor.y);
	portal_top = min(sector->ceiling.y, doom->sectors[wall->n].ceiling.y);
	if (portal_top > doom->player.where.z + OVER_HEAD_SPACE &&
		portal_bot <= doom->player.where.z - eye_height + STEP_HEIGHT)
		return (1);
	return (0);
}

void	horizontal_collision(t_doom *doom, t_player *player)
{
	int i;
	t_sector *sector;
	t_wall *wall;
	t_xyz	dest;

	i = -1;
	sector = &doom->sectors[player->sector];
	dest.x = player->where.x + player->velocity.x;
	dest.y = player->where.y + player->velocity.y;
	while (++i < sector->npoints)
	{
		wall = sector->wall[i];
		if (intersect_check(player->where, dest, wall->v1, wall->v2))
		{
			if (wall->n == -1)
				return ;
			if (!fit_through_portal(doom, sector, wall))
				return ;
			if (doom->sectors[wall->n].floor.y < sector->floor.y)
				player->ground = 0;
			player->sector = wall->n;
			break ;
		}
		else if ((wall->n == -1 || !fit_through_portal(doom, sector, wall))
			&& hitbox_collision(dest, wall))
			return ;
	}
	player->where.x += player->velocity.x;
	player->where.y += player->velocity.y;
}