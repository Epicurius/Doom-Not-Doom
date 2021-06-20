/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 13:54:10 by nneronin          #+#    #+#             */
/*   Updated: 2021/06/20 13:31:49 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	mute(int i)
{
	if (i)
		Mix_Volume(-1, 64);
	else
		Mix_Volume(-1, 0);
}

void	load_wav(t_doom *doom)
{
	doom->sound[WAV_MAIN_THEME] = Mix_LoadWAV(WAV_PATH"at_dooms_gate.wav");
	doom->sound[WAV_SHOTGUN] = Mix_LoadWAV(WAV_PATH"shotgun.wav");
	doom->sound[WAV_SCREEN_SHOT] = Mix_LoadWAV(WAV_PATH"ss_saved.wav");
	doom->sound[WAV_INTRO] = Mix_LoadWAV(WAV_PATH"Intro.wav");
	doom->sound[WAV_FOOT_STEPS] = Mix_LoadWAV(WAV_PATH"footstep.wav");
	doom->sound[WAV_JUMP] = Mix_LoadWAV(WAV_PATH"jump.wav");
	doom->sound[WAV_GUN] = Mix_LoadWAV(WAV_PATH"gun.wav");
	if (!doom->sound[WAV_MAIN_THEME] || !doom->sound[WAV_SHOTGUN]
		|| !doom->sound[WAV_SCREEN_SHOT] || !doom->sound[WAV_INTRO]
		|| !doom->sound[WAV_FOOT_STEPS] || !doom->sound[WAV_JUMP]
		|| !doom->sound[WAV_GUN])
		error_msg("Mix_LoadWAV: %s\n", Mix_GetError());
}
/*
void	intro(void *arg)
{
	t_dialog	*d;

	d = arg;
	Mix_PlayChannel(1, d->sound1, 0);
	while (Mix_Playing(1) != 0)
		SDL_Delay(200);
	Mix_PlayChannel(1, d->sound2, -1);
	SDL_Delay(1300);
	d->done[0] = 1;
}
*/
void	init_sound(t_doom *doom)
{
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
		error_msg("Mix_OpenAudio: %s\n", Mix_GetError());
	Mix_AllocateChannels(7);
	load_wav(doom);
	//Mix_Volume(-1, 0);
	Mix_PlayChannel(CHANNEL_TTS, doom->sound[WAV_INTRO], 0);
}
