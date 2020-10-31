/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 12:30:18 by nneronin          #+#    #+#             */
/*   Updated: 2020/10/31 13:32:36 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_H
# define MACROS_H

/*
** Screen info
*/
# define W				1900
# define H				900

/*
**	Vision
*/
#define EYE_HEIGHT 		6
#define DUCK_HEIGHT		2.5
#define OVER_HEAD_SPACE	1
#define STEP_HEIGHT		2
#define HORI_FOV		(1.0 * 0.50f * W)
#define VERT_FOV		(1.0 * 0.25f * W)

/*
**	Movement
*/
#define WALK_SPEED		0.2f
#define SPRINT_SPEED	0.5f
#define	GRAVITY			0.05f

/*
** Map Rendering
*/
# define NEARZ			0.0001000
# define FARZ			5.0000000
# define NEARSIDE		0.0000100
# define FARSIDE		20.000000
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
#define IMG_RES			doom->txtx->w

#define WALL_TEXTURE_H	doom->txtx->w

#endif
