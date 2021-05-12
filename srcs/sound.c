/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 13:54:10 by nneronin          #+#    #+#             */
/*   Updated: 2021/05/12 13:09:33 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	intro(void	*arg)
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

void	init_sound(t_doom *doom)
{
	Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 2048);
	Mix_AllocateChannels(10);
	doom->sound[MAIN_THEME] = Mix_LoadWAV(GAME_PATH"resources/WAV/at_dooms_gate.wav");
	doom->sound[SHOTGUN] = Mix_LoadWAV(GAME_PATH"resources/WAV/shotgun.wav");
	doom->sound[SS_SAVED] = Mix_LoadWAV(GAME_PATH"resources/WAV/ss_saved.wav");
	doom->sound[INTRO] = Mix_LoadWAV(GAME_PATH"resources/WAV/Intro.wav");
	doom->sound[FOOT_STEPS] = Mix_LoadWAV(GAME_PATH"resources/WAV/footstep.wav");
	doom->sound[JUMP] = Mix_LoadWAV(GAME_PATH"resources/WAV/jump.wav");
	doom->sound[GUN] = Mix_LoadWAV(GAME_PATH"resources/WAV/gun.wav");

	/* Intro */
	//doom->d.sound1 = doom->sound[INTRO];
	//doom->d.sound2 = doom->sound[MAIN_THEME];
	//doom->d.done = &doom->intro;
	//pthread_create(&doom->t, NULL, intro, &doom->d);
	
	Mix_PlayChannel(MUSIC, doom->sound[MAIN_THEME], -1);
	Mix_Volume(MUSIC, 5);
	doom->intro[1] = 1;
}
