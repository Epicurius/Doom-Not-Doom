
#include "doom.h"

int	init_player(t_doom *doom)
{
	t_player *player;

	player = &doom->player;
	player->sector = find_sector(doom, doom->player.where);
	if (player->sector == -1)
		return (0);
	
	player->hp		= 1000;
	player->flying		= 0;
	//player->ground		= 0;
	//player->stat1.width		= PLAYER_RADIUS;
	//player->stat1.height		= PLAYER_HEIGHT;
	//player->stat1.eye_lvl		= EYE_LVL;
	//player->stat1.walk_speed	= WALK_SPEED;
	//player->stat1.sprint_speed	= SPRINT_SPEED;
	//player->stat1.step_height	= STEP_HEIGHT;
		
	//player->where.z		+= EYE_LVL;
	return (1);
}
