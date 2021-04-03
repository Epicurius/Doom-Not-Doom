
#include "doom.h"

void	vertical_collision(t_doom *doom, t_player *player)
{
	double	new_z;
	t_sector sector;

	sector = doom->sectors[player->sector];
	new_z = player->where.z + player->velocity.z;
	// So to not keep on falling through floor.
	if (player->velocity.z < 0 && new_z < sector.floor.y)
	{	
		player->where.z = sector.floor.y;
		player->velocity.z = 0;
	}
	// If player has reached the cealing.
	else if (player->velocity.z > 0 && new_z + PLAYER_HEIGHT > sector.ceiling.y)
		player->velocity.z = 0;
	// Let the player keep on rising/falling.
	else
		player->where.z += player->velocity.z;
}
