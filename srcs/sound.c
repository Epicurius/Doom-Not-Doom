/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 13:54:10 by nneronin          #+#    #+#             */
/*   Updated: 2021/09/17 18:41:10 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
 *	Mute or unmute sounds.
 */
void	mute(int i)
{
	(void)i;
	if (Mix_Volume(-1, -1) <= 0)
		Mix_Volume(-1, 64);
	else
		Mix_Volume(-1, 0);
}

/*
 *	Parse .wav files and save them too doom->sounds.
 */
static void	parse_wav(int amount, Mix_Chunk **dest, const t_id_and_path *src)
{
	int	i;

	i = -1;
	while (++i < amount)
	{
		if (ft_strequ(src[i].path, "NULL"))
			continue ;
		dest[src[i].id] = Mix_LoadWAV(src[i].path);
		if (dest[src[i].id] == NULL)
			error_msg("Reading[%d]: %s", src[i].id, src[i].path);
	}
}

/*
 *	Init all the sounds and any event audio.
 */
void	init_sound(t_doom *doom)
{
	int	i;

	i = -1;
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
		error_msg("Mix_OpenAudio: %s\n", Mix_GetError());
	Mix_AllocateChannels(32);
	parse_wav(WAV_AMOUNT, doom->sound, g_sounds);
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
	Mix_Volume(-1, 0);
}
