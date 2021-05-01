
#include "doom.h"

void	init_player(t_doom *doom)
{
	doom->player.sector = find_sector(doom, doom->player.where);
	doom->player.hp = 1000;
	doom->player.flying = 0;
}
