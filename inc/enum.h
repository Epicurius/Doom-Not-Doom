/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enum.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 14:13:33 by nneronin          #+#    #+#             */
/*   Updated: 2021/08/03 10:01:38 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENUM_H
# define ENUM_H

enum e_enum_weapons
{
	WEAPON_SHOTGUN,
	WEAPON_GUN,
	WEAPON_KAR,
	WEAPON_PUMP,
	WEAPON_MINIGUN,
	WEAPON_AMOUNT
};

enum e_enum_sounds
{
	WAV_MAIN_THEME,
	WAV_SHOTGUN,
	WAV_SCREEN_SHOT,
	WAV_INTRO,
	WAV_FOOT_STEPS,
	WAV_JUMP,
	WAV_GUN,
	WAV_ELEVATOR_MUSIC,
	WAV_DOSH,
	WAV_EMPTY_CLIP,
	WAV_BIP,
	WAV_ORB,
	WAV_NEW_ROUND,
	WAV_ROUND_END,
	WAV_PLAYER_HIT,
	WAV_MONSTER_HIT,
	WAV_PLAYER_DEATH,
	WAV_ENTITY_DEATH,
	WAV_AMOUNT
};

enum e_enum_sound_channel
{
	CHANNEL_MUSIC,
	CHANNEL_WEAPON,
	CHANNEL_STEPS,
	CHANNEL_JUMP,
	CHANNEL_TTS,
	CHANNEL_ENEMY,
	CHANNEL_EXPLOSION,
	CHANNEL_AMOUNT
};

enum e_enum_sprites
{
	ALFRED,
	SPOOKY,
	GHOST,
	RIFT,
	BARREL,
	LAMP,
	TORCH,
	MEAT_HOOK,
	ENTITY_AMOUNT
};

enum e_enum_entity_state
{
	IDLE,
	ATTACK,
	MOVE,
	DEATH,
	TERMINATE
};

enum e_enum_skybox
{
	TOP,
	BOT,
	SIDES,
	TOP_HALF,
	BOT_HALF
};

enum e_player_action
{
	NONE,
	SHOOTING,
	CLICKING,
	SECTOR
};

enum e_event_type
{
	CEILING,
	FLOOR,
	STORE,
	HAZARD
};

enum e_wsprite_action
{
	STATIC,
	LOOP,
	ACTION
};

enum e_game_mode
{
	STORY,
	ENDLESS
};

enum e_key_code
{
	KEY_A = 4,
	KEY_B = 5,
	KEY_C = 6,
	KEY_D = 7,
	KEY_E = 8,
	KEY_F = 9,
	KEY_G = 10,
	KEY_H = 11,
	KEY_I = 12,
	KEY_J = 13,
	KEY_K = 14,
	KEY_L = 15,
	KEY_M = 16,
	KEY_N = 17,
	KEY_O = 18,
	KEY_P = 19,
	KEY_Q = 20,
	KEY_R = 21,
	KEY_S = 22,
	KEY_T = 23,
	KEY_U = 24,
	KEY_V = 25,
	KEY_W = 26,
	KEY_X = 27,
	KEY_Y = 28,
	KEY_Z = 29,
	KEY_1 = 30,
	KEY_2 = 31,
	KEY_3 = 32,
	KEY_4 = 33,
	KEY_5 = 34,
	KEY_6 = 35,
	KEY_7 = 36,
	KEY_8 = 37,
	KEY_9 = 38,
	KEY_0 = 39,
	KEY_RETURN = 40,
	KEY_ESCAPE = 41,
	KEY_BACKSPACE = 42,
	KEY_TAB = 43,
	KEY_SPACE = 44,
	KEY_MINUS = 45,
	KEY_EQUAL = 46,
	KEY_LEFT_BRACKET = 47,
	KEY_RIGHT_BRACKET = 48,
	KEY_BACK_SLAC = 49,
	KEY_HASH = 50,
	KEY_CAPSLOCK = 57,
	KEY_F1 = 58,
	KEY_F2 = 59,
	KEY_F3 = 60,
	KEY_F4 = 61,
	KEY_F5 = 62,
	KEY_F6 = 63,
	KEY_F7 = 64,
	KEY_F8 = 65,
	KEY_F9 = 66,
	KEY_F10 = 67,
	KEY_F11 = 68,
	KEY_F12 = 69,
	KEY_DELETE = 76,
	KEY_RIGHT = 79,
	KEY_LEFT = 80,
	KEY_DOWN = 81,
	KEY_UP = 82,
	KEY_LCTRL = 224,
	KEY_LSHIFT = 225,
	KEY_LALT = 226,
	KEY_RCTRL = 228,
	KEY_RSHIFT = 229,
	KEY_RALT = 230,
	MOUSE_LEFT = 512,
	MOUSE_RIGHT = 513,
};

#endif
