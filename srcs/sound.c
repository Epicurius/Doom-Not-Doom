/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 13:54:10 by nneronin          #+#    #+#             */
/*   Updated: 2021/05/26 16:48:30 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	load_wav(t_doom *doom)
{
	doom->sound[WAV_MAIN_THEME] = Mix_LoadWAV(GAME_PATH"resources/WAV/at_dooms_gate.wav");
	doom->sound[WAV_SHOTGUN] = Mix_LoadWAV(GAME_PATH"resources/WAV/shotgun.wav");
	doom->sound[WAV_SCREEN_SHOT] = Mix_LoadWAV(GAME_PATH"resources/WAV/ss_saved.wav");
	doom->sound[WAV_INTRO] = Mix_LoadWAV(GAME_PATH"resources/WAV/Intro.wav");
	doom->sound[WAV_FOOT_STEPS] = Mix_LoadWAV(GAME_PATH"resources/WAV/footstep.wav");
	doom->sound[WAV_JUMP] = Mix_LoadWAV(GAME_PATH"resources/WAV/jump.wav");
	doom->sound[WAV_GUN] = Mix_LoadWAV(GAME_PATH"resources/WAV/gun.wav");

	if (!doom->sound[WAV_MAIN_THEME] || !doom->sound[WAV_SHOTGUN] || !doom->sound[WAV_SCREEN_SHOT]
			|| !doom->sound[WAV_INTRO] || !doom->sound[WAV_FOOT_STEPS] || !doom->sound[WAV_JUMP]
			|| !doom->sound[WAV_GUN])
		error_msg("Mix_LoadWAV: %s\n", Mix_GetError());
}

void	intro(void	*arg)
{
	t_dialog	*d;

	d = arg;
	//Mix_PlayChannel(1, d->sound1, 0);
    while (Mix_Playing(1) != 0)
		SDL_Delay(200);
	//Mix_PlayChannel(1, d->sound2, -1);
	SDL_Delay(1300);
	d->done[0] = 1;
}

void	init_sound(t_doom *doom)
{
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
		error_msg("Mix_OpenAudio: %s\n", Mix_GetError());
	Mix_AllocateChannels(7);
	load_wav(doom);

	/* Intro */
	//doom->d.sound1 = doom->sound[INTRO];
	//doom->d.sound2 = doom->sound[MAIN_THEME];
	//doom->d.done = &doom->intro;
	//pthread_create(&doom->t, NULL, intro, &doom->d);
	
	//Mix_PlayChannel(CHANNEL_MUSIC, doom->sound[WAV_MAIN_THEME], -1);
	Mix_Volume(CHANNEL_MUSIC, 5);
	doom->intro[1] = 1;
}
