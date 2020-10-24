/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 12:30:18 by nneronin          #+#    #+#             */
/*   Updated: 2020/10/24 13:44:08 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_H
# define MACROS_H

/*
** Screen info
*/
# define W				1280
# define H				720

/*
**	Vision
*/
#define EYE_HEIGHT 		6
#define DUCK_HEIGHT		2.5
#define OVER_HEAD_SPACE	1
#define STEP_HEIGHT		2
#define HORI_FOV		(1.0 * 0.73f * H / W)
#define VERT_FOV		(1.0 * .2f)

/*
**	Movement
*/
#define WALK_SPEED		0.2f
#define SPRINT_SPEED	0.5f

/*
** Map Rendering
*/
# define NEARZ			1e-4f
# define FARZ			5
# define NEARSIDE		1e-5f
# define FARSIDE		20.f
# define MAXQUEUE		32

/*
**	Shortcuts
*/
# define PLAYER			doom->player
# define SECTORS		doom->sectors
# define HEIGHT_INFO	doom->height_info
# define SECTORNUM		doom->num_sectors
# define FPS			doom->fps

/*
** Texture
*/
#define IMG_RES			1024

#endif
