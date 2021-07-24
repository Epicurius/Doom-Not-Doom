/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enum.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 14:13:33 by nneronin          #+#    #+#             */
/*   Updated: 2021/07/24 15:00:16 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENUM_H
# define ENUM_H

typedef enum e_enum_weapons
{
	WEAPON_SHOTGUN,
	WEAPON_GUN,
	WEAPON_KAR,
	WEAPON_PUMP,
	WEAPON_MINIGUN
}				t_enum_weapons;

typedef enum e_enum_sounds
{
	WAV_MAIN_THEME,
	WAV_SHOTGUN,
	WAV_SCREEN_SHOT,
	WAV_INTRO,
	WAV_FOOT_STEPS,
	WAV_JUMP,
	WAV_GUN,
	WAV_ELEVATOR_MUSIC,
	WAV_DOSH
}				t_enum_sounds;

# define CHANNEL_AMOUNT 7

typedef enum e_enum_sound_channel
{
	CHANNEL_MUSIC,
	CHANNEL_WEAPON,
	CHANNEL_STEPS,
	CHANNEL_JUMP,
	CHANNEL_TTS,
	CHANNEL_ALFRED,
	CHANNEL_SPOOKY,
	CHANNEL_EXPLOSION
}				t_enum_sound_channel;

typedef enum e_enum_sprites
{
	ALFRED,
	SPOOKY,
	RIFT,
	BARREL,
	LAMP,
	TORCH,
	MEAT_HOOK
}				t_enum_sprites;

typedef enum e_enum_entity_state
{
	IDLE,
	ATTACK,
	MOVE,
	DEATH
}			t_enum_entity_state;

typedef enum e_enum_skybox
{
	TOP,
	BOT,
	SIDES,
	TOP_HALF,
	BOT_HALF
}			t_enum_skybox;

typedef enum e_player_action
{
	NONE,
	SHOOTING,
	CLICKING,
	SECTOR
}			t_player_action;

typedef enum e_event_type
{
	CEILING,
	FLOOR,
	STORE
}			t_event_type;

typedef enum e_wsprite_action
{
	STATIC,
	LOOP,
	ACTION
}			t_wsprite_action;

typedef enum e_game_mode
{
	STORY,
	ENDLESS
}			t_game_mode;

#endif
