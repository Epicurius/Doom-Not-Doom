/*
 * https://github.com/Epicurius/Doom-Not-Doom
 * 
 * Created: 2021/05/11 10:12:36 nneronin
 * Updated: 2022/01/18 13:11:25 Niklas Neronin
 */

#include "doom.h"

/*
 *	Check sector for each entity.
 */
static int	check_entities(t_doom *doom)
{
	t_list		*curr;

	curr = doom->entity;
	while (curr)
	{
		if (!in_sector(&doom->sectors[((t_entity *)curr->content)->sector],
				((t_entity *)curr->content)->where))
		{
			LG_WARN("Entity %d is outside map boundaries!.",
				((t_entity *)curr->content)->type);
			return (0);
		}
		curr = curr->next;
	}
	return (1);
}

/*
 *	Check player sector.
 */
static int	check_player(t_doom *doom)
{
	if (!in_sector(&doom->sectors[doom->player.sector], doom->player.where))
	{
		LG_WARN("Player is outside map boundaries!.");
		return (0);
	}
	return (1);
}

/*
 *	Change sector slope start index from wall index to sextor wall index.
 */
static int	fix_slope_wall_index(t_sector *sector, int *wall_slope)
{
	int	i;

	i = -1;
	if (*wall_slope < 0)
		return (*wall_slope = 0);
	while (++i < sector->npoints)
		if (sector->wall[i]->id == *wall_slope)
			return (*wall_slope = i);
	return (*wall_slope = 0);
}

/*
 *	For each sector:
 *	Calculate sector center.
 *	Fix wall orientation to be clockwise.
 *	Fix wall order, if not possible error.
 *	If sector convex, else error.
 */
static int	check_map(t_doom *doom)
{
	int	i;

	i = -1;
	while (++i < doom->nb.sectors)
	{
		sector_center(&doom->sectors[i]);
		fix_wall_orientation(&doom->sectors[i]);
		if (!fix_wall_order(&doom->sectors[i]))
			return (0);
		if (!is_convex(&doom->sectors[i]))
			return (0);
		fix_slope_wall_index(&doom->sectors[i],
			&doom->sectors[i].floor_incl_start);
		fix_slope_wall_index(&doom->sectors[i],
			&doom->sectors[i].ceiling_incl_start);
		doom->sectors[i].center.z = floor_at(&doom->sectors[i],
				doom->sectors[i].center);
	}
	return (1);
}

/*
 *	Main validation function.
 *	Checks if map is valid else free.
 */
int	validate_map(t_doom *doom)
{
	fix_sector_index(doom);
	if (check_map(doom) && check_player(doom) && check_entities(doom))
		return (1);
	free_doom(doom);
	return (0);
}
