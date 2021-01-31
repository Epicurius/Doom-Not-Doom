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

/*
** Screen info
*/
# define W				720
# define H				480
# define THREADS_NB		4

/*
**	Vision
*/
#define EYE_HEIGHT 		6
#define DUCK_HEIGHT		2.5
#define OVER_HEAD_SPACE	1
#define STEP_HEIGHT		2
#define HORI_FOV		(0.32f * W)
#define VERT_FOV		(0.18f * H)

//* W



/*
**	Movement
*/
#define WALK_SPEED		0.2f
#define SPRINT_SPEED	0.5f
#define CROUCH_SPEED	0.01f
#define	GRAVITY			0.05f
#define MOUSE_X			0.005f
#define MOUSE_Y			0.005f
#define	ACCELERATION	0.7

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
# define ENTITYNUM		doom->num_entity
# define FPS			doom->fps

/*
** Texture
*/

# define WTX_W	render->wtx->w
# define WTX_H	render->wtx->h
# define CTX_W	render->ctx->w
# define CTX_H	render->ctx->h
# define FTX_W	render->ftx->w
# define FTX_H	render->ftx->h
#define G				0xAAAAAA

/*
** Keys
*/
# define KEY_A(x)			(x << 1)
# define KEY_B(x)			(x << 2)
# define KEY_C(x)			(x << 3)
# define KEY_D(x)			(x << 4)
# define KEY_E(x)			(x << 5)
# define KEY_F(x)			(x << 6)
# define KEY_G(x)			(x << 7)
# define KEY_H(x)			(x << 8)
# define KEY_J(x)			(x << 9)
# define KEY_K(x)			(x << 10)
# define KEY_L(x)			(x << 11)
# define KEY_M(x)			(x << 12)
# define KEY_O(x)			(x << 13)
# define KEY_P(x)			(x << 14)
# define KEY_Q(x)			(x << 15)
# define KEY_R(x)			(x << 16)
# define KEY_S(x)			(x << 17)
# define KEY_T(x)			(x << 18)
# define KEY_U(x)			(x << 19)
# define KEY_V(x)			(x << 20)
# define KEY_W(x)			(x << 21)
# define KEY_X(x)			(x << 22)
# define KEY_Y(x)			(x << 23)
# define KEY_Z(x)			(x << 24)

# define KEY_1				(x << 1)
# define KEY_2				(x << 2)
# define KEY_3				(x << 3)
# define KEY_4				(x << 4)
# define KEY_5				(x << 5)
# define KEY_6				(x << 6)
# define KEY_7				(x << 7)
# define KEY_8				(x << 8)
# define KEY_9				(x << 9)
# define KEY_0				(x << 10)

# define TAB(x)				(x << 1)
# define SPACE(x)			(x << 2)
# define ENTER(x)			(x << 3)
# define DELET(x)			(x << 4)
# define LCTRL(x)			(x << 5)
# define RCTRL(x)			(x << 6)
# define LSHIFT(x)			(x << 7)
# define RSHIFT(x)			(x << 8)
# define ARROW_UP(x)		(x << 9)
# define ARROW_DOWN(x)		(x << 10)
# define ARROW_LEFT(x)		(x << 11)
# define ARROW_RIGHT(x)		(x << 12)

# define TEST(a,b,c)		(a b 1 << c)
# define AAAA				doom->player->where.x

#endif
