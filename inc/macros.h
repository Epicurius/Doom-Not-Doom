/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 12:30:18 by nneronin          #+#    #+#             */
/*   Updated: 2021/09/18 16:31:39 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_H
# define MACROS_H

/*
** Screen info
*/
# define MAX_PROCESSORS					64
# define MOUSE_LEFT						512
# define MOUSE_RIGHT					513

/*
**	Vision
*/
# define FOV							90
# define NEAR_Z							0.1
# define FAR_Z							1000.0
# define PLAYER_HEIGHT 					7
# define PLAYER_RADIUS					0.7
# define EYE_LVL						6
# define RENDER_DISTANCE				200.0
# define ZB								100

/*
** Entities
*/
# define ACTIVE_AREA					50
# define FRAMES							0
# define ANGLES							1
# define PLAYER_PROJECTILE_MAX_RANGE	100
# define ENTITY_PROJECTILE_MAX_RANGE	100
# define PROJECTILE_SPEED				50.0

/*
** Weapon
*/
# define START_WEAPON					WEAPON_GUN
# define MAX_BULLET_HOLES				20

/*
**	Movement
*/
# define WALK_SPEED						20.0
# define SPRINT_SPEED					40.0
# define JUMP_HEIGHT					15
# define MOUSE_X						0.003
# define MOUSE_Y						0.003
# define ACCELERATION					0.7
# define DIAMETER						0.7

/*
** Texture
*/
# define ZBUFFER_COLOR					1
# define TEXTURE_DISABLED				0
# define CLOCK_BG_COLOR					0xFF000000
# define CLOCK_FG_COLOR					0xFFFFFFFF
# define WALL_SPRITE_SPEED				100

/*
** Minimap
*/
# define MM_SCALE						0.8
# define MM_SECTORS_SCALE				1
# define MM_BEZEL_SIZE					5
# define MM_BEZEL_COLOR					0x222222
# define MM_VIEW_COLOR					0xFFD700
# define MM_ALPHA						100

#endif
