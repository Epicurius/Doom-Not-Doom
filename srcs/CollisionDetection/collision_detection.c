/*
 * https://github.com/Epicurius/Doom-Not-Doom
 * 
 * Created: 2021/04/24 15:32:29 nneronin
 * Updated: 2021/12/18 15:59:59 nneronin
 */

#include "doom.h"

/*
 *	Find the correct sector from the sectbool list of sectors
 *	that player hitbox has moved through.
 *	If none of the match, check all sectors.
 *	If that fails return -1, to kill the entity.
 */
int	find_from_sectbool(t_doom *doom, t_motion *motion)
{
	int		i;
	t_v3	where;

	i = -1;
	where = add_v3(motion->where, motion->velocity);
	while (++i < doom->nb.sectors)
	{
		if (doom->sectbool[i] && in_sector_area(&doom->sectors[i], where))
			return (i);
	}
	return (find_sector_no_z(doom->sectors, doom->nb.sectors, where));
}

static void	check_vertical_position(t_sector *sector, t_motion *motion,
	t_v3 *where, t_v3 *velocity)
{
	float	top;
	float	bot;

	bot = floor_at(sector, *where);
	top = ceiling_at(sector, *where);
	if (where->z < bot)
	{
		where->z = bot;
		velocity->z = 0;
	}
	if (where->z + motion->height > top)
	{
		where->z = top - motion->height;
		velocity->z = 0;
	}	
}

/*
 *	Check map collision.
 *	Vertical -> Horizontal -> move entity z to be in sector.
 */
int	collision_detection(t_doom *doom, t_motion motion,
		t_v3 *where, t_v3 *velocity)
{
	float	gforce;

	motion.step = 2;
	motion.where = *where;
	motion.velocity = *velocity;
	if (vertical_collision(doom, &motion, &gforce))
		return (-1);
	if (velocity->x || velocity->y)
	{
		motion.dest = add_v3(motion.where, motion.velocity);
		reset_sectbool(doom, motion.sector);
		if (horizontal_collision(doom, &motion))
			return (-1);
	}
	*velocity = motion.velocity;
	*where = add_v3(*where, *velocity);
	velocity->z = gforce;
	check_vertical_position(&doom->sectors[motion.sector],
		&motion, where, velocity);
	return (motion.sector);
}
