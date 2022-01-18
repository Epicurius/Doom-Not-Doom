/*
 * https://github.com/Epicurius/Doom-Not-Doom
 * 
 * Created: 2021/05/08 10:51:35 nneronin
 * Updated: 2022/01/18 17:34:34 Niklas Neronin
 */

#include "doom.h"

void	init_player(t_doom *doom)
{
	doom->player.where.z = ft_fmax(doom->player.where.z,
			floor_at(&doom->sectors[doom->player.sector], doom->player.where));
	doom->player.max_hp = 1100 - doom->settings.difficulty * 100;
	doom->player.health = doom->player.max_hp;
	doom->player.armour = 1000 - doom->settings.difficulty * 100;
	doom->player.eyelvl = EYE_LVL;
	doom->player.flight = doom->settings.debug;
	doom->player.debug = doom->settings.debug;
	doom->player.equipped = 1;
	doom->player.walk_speed = WALK_SPEED;
	doom->player.sprint_speed = SPRINT_SPEED;
	doom->player.jump_height = JUMP_HEIGHT;
}
