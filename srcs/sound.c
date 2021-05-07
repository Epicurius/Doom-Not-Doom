/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 13:54:10 by nneronin          #+#    #+#             */
/*   Updated: 2021/05/07 14:16:26 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	init_sound(t_doom *doom)
{
	Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 2048);
	doom->sound[MAIN_THEME] = Mix_LoadWAV(GAME_PATH"resources/WAV/at_dooms_gate.wav");
	doom->sound[SHOTGUN] = Mix_LoadWAV(GAME_PATH"resources/WAV/shotgun_shot.wav");
	Mix_PlayChannel(-1, doom->sound[MAIN_THEME], -1);
}
