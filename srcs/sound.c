/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 13:54:10 by nneronin          #+#    #+#             */
/*   Updated: 2021/07/14 09:53:19 by nneronin         ###   ########.fr       */
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

static void	parse_wav(int amount, Mix_Chunk **dest, t_id_and_path *src)
{
	int	i;

	i = -1;
	while (++i < amount)
	{
		if (ft_strequ(src[i].path, "NULL"))
			continue ;
		dest[src[i].id] = Mix_LoadWAV(src[i].path);
		if (dest == NULL)
			error_msg("Reading[%d]: %s", src[i].id, src[i].path);
	}
}

void	init_sound(t_doom *doom)
{
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
		error_msg("Mix_OpenAudio: %s\n", Mix_GetError());
	Mix_AllocateChannels(7);
	parse_wav(WAV_AMOUNT, doom->sound, g_sounds);
	Mix_PlayChannel(CHANNEL_TTS, doom->sound[WAV_INTRO], 0);
	Mix_Volume(-1, 0);
}
