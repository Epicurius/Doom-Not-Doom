
#include "doom.h"

void	vertical_collision(t_doom *doom, t_player *player)
{
	double	cam_z;
	double	new_z;
	t_sector sector;

	sector = doom->sectors[player->sector];
	if (!player->flying)
		player->velocity.z -= sector.gravity;
	new_z = player->where.z + player->velocity.z;
	cam_z = player->ducking ? DUCK_HEIGHT : EYE_HEIGHT;
	// So to not keep on falling through floor.
	if (player->velocity.z < 0 && new_z < sector.floor.y + cam_z)
	{
		player->where.z = sector.floor.y + cam_z;
		player->velocity.z = 0;
		player->ground = 1;
	}
	// If player has reached the cealing.
	else if (player->velocity.z > 0 && new_z > sector.ceiling.y)
		player->velocity.z = 0;
	// Let the player keep on falling.
	else if (!player->ground || player->flying)
		player->where.z += player->velocity.z;
}
