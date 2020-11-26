/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_detection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 12:10:37 by nneronin          #+#    #+#             */
/*   Updated: 2020/11/26 15:38:13 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/* Vertical collision detection */
void	vertical_collision(t_doom *doom)
{
        float new_z;
        float eye_height;

        PLAYER.ground = !PLAYER.falling;
        if (PLAYER.falling)
        {
	   		eye_height = PLAYER.ducking ? DUCK_HEIGHT : EYE_HEIGHT;
            PLAYER.velocity.z -= doom->sectors[PLAYER.sector].gravity;
            new_z = PLAYER.where.z + PLAYER.velocity.z;
            if (PLAYER.velocity.z < 0 && new_z < doom->sectors[PLAYER.sector].floor + eye_height) // down
            {
                PLAYER.where.z = doom->sectors[PLAYER.sector].floor + eye_height;
                PLAYER.velocity.z = 0;
                PLAYER.falling = 0;
                PLAYER.ground  = 1;
            }
            else if (PLAYER.velocity.z > 0 && new_z > doom->sectors[PLAYER.sector].ceil) //up
            {
                PLAYER.velocity.z = 0;
                PLAYER.falling = 1;
            }
            if (PLAYER.falling)
            {
                PLAYER.where.z += PLAYER.velocity.z;
                PLAYER.moving = 1;
            }
        }
}

//Horizontal collision detection
void	horizontal_collision(t_doom *doom)
{
	int			s;
	t_xyz		p;
	t_xyz		d;
	t_xyz*		vert;
	t_sector*	sect;
	float		hole_low;
	float		hole_high;

	float eye_height = PLAYER.ducking ? DUCK_HEIGHT : EYE_HEIGHT;
	if (PLAYER.moving)
	{
		s = -1;
		p = (t_xyz){.x = PLAYER.where.x, .y = PLAYER.where.y, .z = 0};
		d = (t_xyz){.x = PLAYER.velocity.x, .y = PLAYER.velocity.y, .z = 0};
		p.x += PLAYER.velocity.x > 0 ? 0.5 : -0.5;	//
		p.y += PLAYER.velocity.y > 0 ? 0.5 : -0.5;	//Temp fix, so not to clip in wall dont let player reach wall
		sect = &doom->sectors[PLAYER.sector];
		vert = sect->vertex;
		while (++s < sect->npoints)
		{
			if (intersect_box(p, d, vert[s], vert[s + 1]) && point_side(p, d, vert[s], vert[s + 1]) < 0)
			{
				//Check where the hole is.
				if (sect->neighbors[s] >= 0)
				{
					hole_low  = max(sect->floor, doom->sectors[sect->neighbors[s]].floor);
					hole_high = min(sect->ceil,  doom->sectors[sect->neighbors[s]].ceil );
				}
				if (sect->neighbors[s] == -1 || hole_high < PLAYER.where.z + OVER_HEAD_SPACE ||
						hole_low  > PLAYER.where.z - eye_height + STEP_HEIGHT)
				{
					float xd = sect->vertex[s+1].x - sect->vertex[s+0].x;
					float yd = sect->vertex[s+1].y - sect->vertex[s+0].y;
					d.x = xd * (d.x * xd + d.y * yd) / (xd * xd + yd * yd);
					d.y = yd * (d.x * xd + d.y * yd) / (xd * xd + yd * yd);
					PLAYER.moving = 0;
					//d = (t_xyz){.x = 0.f, .y = 0.f};

				}

			}
		}
		//printf("%f %f\n", d.x, d.y)
		move_player(doom, d.x, d.y);
		PLAYER.falling = 1;
	}
}
