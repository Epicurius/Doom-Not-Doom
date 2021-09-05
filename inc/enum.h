/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enum.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 14:13:33 by nneronin          #+#    #+#             */
/*   Updated: 2021/09/05 06:57:58 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENUM_H
# define ENUM_H

enum e_weapons
{
	WEAPON_SHOTGUN,
	WEAPON_GUN,
	WEAPON_KAR,
	WEAPON_PUMP,
	WEAPON_MINIGUN,
	WEAPON_AMOUNT
};

enum e_sounds
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

enum e_sound_channel
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

enum e_sprites
{
	ALFRED,
	SPOOKY,
	GHOST,
	RIFT,
	BARREL,
	LAMP,
	TORCH,
	MEAT_HOOK,
	CEILING_LAMP,
	GARGOYLE,
	MED_KIT,
	ENTITY_AMOUNT
};

enum e_entity_state
{
	IDLE,
	ATTACK,
	MOVE,
	DEATH,
	TERMINATE
};

enum e_skybox
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
	HAZARD,
	AUDIO,
	SPAWN,
	LIGHT
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

enum e_entity_type
{
	INANIMATE,
	MELEE,
	RANGE,
	KAMIKAZE
};

#endif
