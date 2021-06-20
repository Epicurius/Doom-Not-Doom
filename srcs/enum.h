/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enum.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 14:13:33 by nneronin          #+#    #+#             */
/*   Updated: 2021/06/20 13:55:39 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENUM_H
# define ENUM_H

typedef enum e_enum_weapons
{
	WEAPON_SHOTGUN,
	WEAPON_GUN,
	WEAPON_MINIGUN,
	WEAPON_KAR
}				t_enum_weapons;

typedef enum e_enum_sounds
{
	WAV_MAIN_THEME,
	WAV_SHOTGUN,
	WAV_SCREEN_SHOT,
	WAV_INTRO,
	WAV_FOOT_STEPS,
	WAV_JUMP,
	WAV_GUN
}				t_enum_sounds;

typedef enum e_enum_sound_channel
{
	CHANNEL_MUSIC,
	CHANNEL_WEAPON,
	CHANNEL_STEPS,
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

#endif
