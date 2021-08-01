/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 12:30:18 by nneronin          #+#    #+#             */
/*   Updated: 2021/08/01 16:18:24 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_H
# define MACROS_H

/*
** Screen info
*/
# define MAX_PROCESSORS					64

/*
**	Vision
*/
# define PLAYER_HEIGHT 					7
# define EYE_LVL						6
# define OVER_HEAD_SPACE				1
# define DUCK_HEIGHT					2.5
# define STEP_HEIGHT					2
# define CAMERA_RATIO					1.77777777778
# define FOV							90
# define PLAYER_YAW						45
# define PLAYER_PITCH					10
# define PLAYER_RADIUS					0.7
# define NEAR_Z							0.1
# define FAR_Z							1000
# define RENDER_DISTANCE				200.0
# define ZB								100

/*
** Entities
*/
# define MAX_ENTITIES_RENDERED			20
# define FRAMES							0
# define ANGLES							1
# define STYLE_MELEE					0
# define STYLE_RANGE					1
# define PLAYER_PROJECTILE_MAX_RANGE	100
# define ENTITY_PROJECTILE_MAX_RANGE	100
# define PROJECTILE_SPEED				80.0

/*
** Bullet Holes
*/
# define MAX_BULLET_HOLES				20

/*
**	Movement
*/
# define WALK_SPEED						10.0f
# define SPRINT_SPEED					20.0f
# define JUMP_HEIGHT					0.01f
# define CROUCH_SPEED					0.006f
# define MOUSE_X						0.003f
# define MOUSE_Y						0.003f
# define ACCELERATION					0.7

/*
** Map Rendering
*/
# define MAXQUEUE						32

/*
** Texture
*/
# define ZBUFFER_COLOR					1
# define TEXTURE_DISABLED				0
# define OPAQUE							30
# define NB_SKYBOX_TEXTURES				6
# define NB_WALL_TEXTURES				5
# define NB_CEILING_TEXTURES			1
# define NB_FLOOR_TEXTURES				1
# define CLOCK_BG_COLOR					0xFF000000
# define CLOCK_FG_COLOR					0xFFFFFFFF

/*
** Minimap
*/
# define MM_SCALE						0.8
# define MM_SECTORS_SCALE				2
# define MM_BEZEL_SIZE					5
# define MM_BEZEL_COLOR					0x222222
# define MM_VIEW_COLOR					0xFFD700
# define MM_ALPHA						100

#endif
