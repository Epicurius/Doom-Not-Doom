/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enum.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 14:13:33 by nneronin          #+#    #+#             */
/*   Updated: 2021/05/26 17:10:03 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENUM_H
# define ENUM_H

typedef enum	e_weapons
{
	WEAPON_SHOTGUN,
	WEAPON_GUN,
	WEAPON_MINIGUN,
	WEAPON_KAR
}				e_weapons;

typedef enum	e_sounds
{
	WAV_MAIN_THEME,
	WAV_SHOTGUN,
	WAV_SCREEN_SHOT,
	WAV_INTRO,
	WAV_FOOT_STEPS,
	WAV_JUMP,
	WAV_GUN
}				e_sounds;

typedef enum	e_sound_channel
{
	CHANNEL_MUSIC,
	CHANNEL_WEAPON,
	CHANNEL_STEPS,
	CHANNEL_TTS
}				e_sound_channel;

typedef enum	e_sprites
{
	ALFRED,
	SPOOKY,
	RIFT,
	BARREL,
	LAMP,
	TORCH,
	MEAT_HOOK
}				e_sprites;

#endif
