/*
 * https://github.com/Epicurius/Doom-Not-Doom
 * 
 * Created: 2020/10/08 16:08:23 nneronin
 * Updated: 2021/09/23 11:16:08 nneronin
 */

#include "doom.h"

/*
 *	Calculate floor and ceiling dimensions.
 */
static void	curr_floor_and_ceiling(t_doom *doom, t_wall *w)
{
	t_fc		v1;
	t_fc		v2;
	float		eye_z;

	eye_z = doom->player.where.z + doom->player.eyelvl;
	v1.bot = doom->sectors[w->sect].floor.height - eye_z;
	v2.bot = doom->sectors[w->sect].floor.height - eye_z;
	v1.top = doom->sectors[w->sect].ceiling.height - eye_z;
	v2.top = doom->sectors[w->sect].ceiling.height - eye_z;
	w->stat_y1.bot = doom->c.y + (v1.bot + w->pitch_z1) * w->fov_z1;
	w->stat_y1.top = doom->c.y + (v1.top + w->pitch_z1) * w->fov_z1;
	w->stat_y2.bot = doom->c.y + (v2.bot + w->pitch_z2) * w->fov_z2;
	w->stat_y2.top = doom->c.y + (v2.top + w->pitch_z2) * w->fov_z2;
	w->stat_range.bot = w->stat_y2.bot - w->stat_y1.bot;
	w->stat_range.top = w->stat_y2.top - w->stat_y1.top;
}

/*
 *	Calculate sloping floor and ceiling dimensions.
 */
static void	curr_floor_and_ceil_incl(t_doom *doom, t_wall *w, t_v3 p1, t_v3 p2)
{
	t_fc		v1;
	t_fc		v2;
	float		eye_z;

	eye_z = doom->player.where.z + doom->player.eyelvl;
	v1.bot = floor_at(&doom->sectors[w->sect], p1) - eye_z;
	v1.top = ceiling_at(&doom->sectors[w->sect], p1) - eye_z;
	v2.bot = floor_at(&doom->sectors[w->sect], p2) - eye_z;
	v2.top = ceiling_at(&doom->sectors[w->sect], p2) - eye_z;
	w->incl_y1.bot = doom->c.y + (v1.bot + w->pitch_z1) * w->fov_z1;
	w->incl_y1.top = doom->c.y + (v1.top + w->pitch_z1) * w->fov_z1;
	w->incl_y2.bot = doom->c.y + (v2.bot + w->pitch_z2) * w->fov_z2;
	w->incl_y2.top = doom->c.y + (v2.top + w->pitch_z2) * w->fov_z2;
	w->incl_range.bot = w->incl_y2.bot - w->incl_y1.bot;
	w->incl_range.top = w->incl_y2.top - w->incl_y1.top;
}

/*
 *	Calculate neighbour floor and ceiling dimensions.
 *	Screen y for floor and ceiling vertex, z of floor and ceiling with slope.
 */
static void	neighbour_floor_and_ceil(t_doom *doom, t_wall *w, t_v3 p1, t_v3 p2)
{
	t_fc		v1;
	t_fc		v2;
	float		eye_z;

	eye_z = doom->player.where.z + doom->player.eyelvl;
	v1.bot = floor_at(&doom->sectors[w->n], p1) - eye_z;
	v1.top = ceiling_at(&doom->sectors[w->n], p1) - eye_z;
	v2.bot = floor_at(&doom->sectors[w->n], p2) - eye_z;
	v2.top = ceiling_at(&doom->sectors[w->n], p2) - eye_z;
	w->incl_ny1.bot = doom->c.y + (v1.bot + w->pitch_z1) * w->fov_z1;
	w->incl_ny1.top = doom->c.y + (v1.top + w->pitch_z1) * w->fov_z1;
	w->incl_ny2.bot = doom->c.y + (v2.bot + w->pitch_z2) * w->fov_z2;
	w->incl_ny2.top = doom->c.y + (v2.top + w->pitch_z2) * w->fov_z2;
	w->incl_nrange.bot = w->incl_ny2.bot - w->incl_ny1.bot;
	w->incl_nrange.top = w->incl_ny2.top - w->incl_ny1.top;
}

/*
 *	Preforms perspective transformation
 */
void	project_wall(t_doom *doom, t_wall *wall)
{
	t_v3		p1;
	t_v3		p2;

	wall->fov_z1 = doom->cam.scale / -wall->cv1.z;
	wall->fov_z2 = doom->cam.scale / -wall->cv2.z;
	wall->pitch_z1 = doom->player.pitch * wall->cv1.z;
	wall->pitch_z2 = doom->player.pitch * wall->cv2.z;
	wall->x1 = wall->sv1.x * doom->cam.scale / -wall->sv1.z + doom->c.x;
	wall->x2 = wall->sv2.x * doom->cam.scale / -wall->sv2.z + doom->c.x;
	wall->cx1 = wall->cv1.x * wall->fov_z1 + doom->c.x;
	wall->cx2 = wall->cv2.x * wall->fov_z2 + doom->c.x;
	wall->xrange = wall->x2 - wall->x1;
	wall->zrange = wall->sv1.z - wall->sv2.z;
	wall->zcomb = wall->sv2.z * wall->sv1.z;
	wall->x1z2 = wall->v1.x * wall->sv2.z;
	wall->y1z2 = wall->v1.y * wall->sv2.z;
	wall->xzrange = wall->v2.x * wall->sv1.z - wall->x1z2;
	wall->yzrange = wall->v2.y * wall->sv1.z - wall->y1z2;
	curr_floor_and_ceiling(doom, wall);
	screen_to_map_vertex(doom->player, &wall->cv1, &p1);
	screen_to_map_vertex(doom->player, &wall->cv2, &p2);
	curr_floor_and_ceil_incl(doom, wall, p1, p2);
	if (wall->n != -1)
		neighbour_floor_and_ceil(doom, wall, p1, p2);
}
