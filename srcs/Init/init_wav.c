/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_wav.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 14:39:43 by nneronin          #+#    #+#             */
/*   Updated: 2022/01/07 16:16:05 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static int	multithread_sound_0(void *arg)
{
	((Mix_Chunk **)arg)[g_sounds[0].id] = Mix_LoadWAV(g_sounds[0].path);
	return (1);
}

static int	multithread_sound_1(void *arg)
{
	((Mix_Chunk **)arg)[g_sounds[1].id] = Mix_LoadWAV(g_sounds[1].path);
	return (1);
}

static int	multithread_sound_2(void *arg)
{
	((Mix_Chunk **)arg)[g_sounds[2].id] = Mix_LoadWAV(g_sounds[2].path);
	return (1);
}

static int	multithread_sounds(void *arg)
{
	int	i;

	i = 2;
	while (++i < WAV_AMOUNT)
		((Mix_Chunk **)arg)[g_sounds[i].id] = Mix_LoadWAV(g_sounds[i].path);
	return (1);
}

/*
 *	Parse .wav files int threads and save them too doom->sounds.
 */
void	init_wav(t_doom *doom)
{
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
		LG_ERROR("Mix_OpenAudio: %s\n", Mix_GetError());
	Mix_AllocateChannels(32);
	tpool_add(&doom->tpool, multithread_sound_0, &doom->sound);
	tpool_add(&doom->tpool, multithread_sound_1, &doom->sound);
	tpool_add(&doom->tpool, multithread_sound_2, &doom->sound);
	tpool_add(&doom->tpool, multithread_sounds, &doom->sound);
}
