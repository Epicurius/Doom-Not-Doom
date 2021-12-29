/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 13:54:10 by nneronin          #+#    #+#             */
/*   Updated: 2021/12/29 15:36:49 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
 *	Adjust volume ingame.
 */
void	set_volume(int i)
{
	static unsigned char	curr = DEFAULT_VOLUME;

	if (curr < 128 && i)
		Mix_Volume(-1, ++curr);
	else if (curr > 0 && curr <= 128 && !i)
		Mix_Volume(-1, --curr);
}

static void	init_volume(t_doom *doom)
{
	Mix_VolumeChunk(doom->sound[WAV_MAIN_THEME], VOLUME_MAIN_THEME);
	Mix_VolumeChunk(doom->sound[WAV_SHOTGUN], VOLUME_SHOTGUN);
	Mix_VolumeChunk(doom->sound[WAV_SCREEN_SHOT], VOLUME_SCREEN_SHOT);
	Mix_VolumeChunk(doom->sound[WAV_INTRO], VOLUME_INTRO);
	Mix_VolumeChunk(doom->sound[WAV_FOOT_STEPS], VOLUME_FOOT_STEPS);
	Mix_VolumeChunk(doom->sound[WAV_JUMP], VOLUME_JUMP);
	Mix_VolumeChunk(doom->sound[WAV_GUN], VOLUME_GUN);
	Mix_VolumeChunk(doom->sound[WAV_ELEVATOR_MUSIC], VOLUME_ELEVATOR_MUSIC);
	Mix_VolumeChunk(doom->sound[WAV_DOSH], VOLUME_DOSH);
	Mix_VolumeChunk(doom->sound[WAV_EMPTY_CLIP], VOLUME_EMPTY_CLIP);
	Mix_VolumeChunk(doom->sound[WAV_BIP], VOLUME_BIP);
	Mix_VolumeChunk(doom->sound[WAV_ORB], VOLUME_ORB);
	Mix_VolumeChunk(doom->sound[WAV_NEW_ROUND], VOLUME_NEW_ROUND);
	Mix_VolumeChunk(doom->sound[WAV_ROUND_END], VOLUME_ROUND_END);
	Mix_VolumeChunk(doom->sound[WAV_PLAYER_HIT], VOLUME_PLAYER_HIT);
	Mix_VolumeChunk(doom->sound[WAV_MONSTER_HIT], VOLUME_MONSTER_HIT);
	Mix_VolumeChunk(doom->sound[WAV_PLAYER_DEATH], VOLUME_PLAYER_DEATH);
	Mix_VolumeChunk(doom->sound[WAV_ENTITY_DEATH], VOLUME_ENTITY_DEATH);
	set_volume(0);
}

/*
 *	Init all the sounds and any event audio.
 */
void	init_sound(t_doom *doom)
{
	int	i;

	i = -1;
	while (++i < doom->nb.events)
	{
		if (doom->events[i].type == AUDIO)
		{
			doom->events[i].audio = Mix_LoadWAV(doom->events[i].path);
			if (!doom->events[i].audio)
				ft_printf("Audio event %s not found\n", doom->events[i].path);
			free(doom->events[i].path);
		}
	}
	tpool_wait(&doom->tpool);
	i = -1;
	while (++i < WAV_AMOUNT)
		if (doom->sound[i] == NULL)
			error_msg("Reading[%d]: %s", g_sounds[i].id, g_sounds[i].path);
	init_volume(doom);
	if (doom->game.mode == ENDLESS && !doom->settings.debug)
		Mix_PlayChannel(CHANNEL_TTS, doom->sound[WAV_INTRO], 0);
	else
		Mix_PlayChannel(CHANNEL_MUSIC, doom->sound[WAV_MAIN_THEME], 0);
}
