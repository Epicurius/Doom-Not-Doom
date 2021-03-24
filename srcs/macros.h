/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 12:30:18 by nneronin          #+#    #+#             */
/*   Updated: 2020/11/26 13:59:37 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_H
# define MACROS_H

typedef struct	s_int_xyz
{
	int	x;
	int	y;
	int	z;
}		t_int_xyz;

typedef struct	s_double_xyz
{
	double	x;
	double	y;
	double	z;
}		t_double_xyz;


/*
** Jony
*/
//# define JONY

/*
** Screen info
*/
# define W						1280
# define H						720
# define MAX_PROCESSORS					8

/*
**	Vision
*/
#define EYE_HEIGHT 					6
#define DUCK_HEIGHT					2.5
#define OVER_HEAD_SPACE					1
#define STEP_HEIGHT					2
//720x480 id 3:2 aspect
#define CAMERA_RATIO					(16.0/9.0)
#define FOV						90
#define PLAYER_YAW					45
#define PLAYER_PITCH					10
#define PLAYER_RADIUS					1.0
#define NEAR_Z						0.1
#define FAR_Z						1000
#define RENDER_DISTANCE					200

/*
** Entities
*/
# define MAX_ENTITIES_RENDERED				20
# define IDLE						0
# define FOLLOW						1
# define ATTACK						2
# define STYLE_MELEE					0
# define STYLE_RANGE					1

/*
** FPS
*/
# define FPS_FONT					"./bmp/Minecraft.ttf"
# define FPS_FONT_SIZE					20
# define FPS_COLOR					0xff00ffff

/*
** Bullet Holes
*/
#define ENABLE_BH					1
#define MAX_BH						10

/*
** Values !!DONT TOUCH!!
*/
#define CONVERT_RADIANS					0.0174532925199432955
#define CONVERT_DEGREES					57.2957795130823228647

/*
**	Movement
*/
#define WALK_SPEED					0.01f
#define SPRINT_SPEED					0.02f
#define CROUCH_SPEED					0.006f
#define	GRAVITY						0.05f
#define MOUSE_X						0.005f
#define MOUSE_Y						0.005f
#define	ACCELERATION					0.7

/*
** Map Rendering
*/
# define MAXQUEUE					32

/*
**	Shortcuts
*/
# define PLAYER						doom->player
# define FPS						doom->fps

/*
** Texture
*/
//Opaque scale for bliting
# define OPAQUE						30
# define NB_SKYBOX_TEXTURES				6
# define NB_WALL_TEXTURES				5
# define NB_CEILING_TEXTURES				1
# define NB_FLOOR_TEXTURES				1

/*
** Minimap
*/
# define MM_SCALE					0.8
# define MM_SECTORS_SCALE				2
# define MM_BEZEL_SIZE					5
# define MM_BEZEL_COLOR					0x222222
# define MM_VIEW_COLOR					0xFFD700
# define MM_ALPHA					100

/*
** Skybox
*/
# define TOP						1
# define BOT						2
# define SIDES						3
# define TOP_HALF					4
# define BOT_HALF					5

#endif
