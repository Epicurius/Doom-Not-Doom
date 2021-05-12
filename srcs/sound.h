/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 14:13:33 by nneronin          #+#    #+#             */
/*   Updated: 2021/05/12 13:12:29 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOUND_H
# define SOUND_H

typedef enum	e_sounds
{
	MAIN_THEME,
	SHOTGUN,
	SS_SAVED,
	INTRO,
	FOOT_STEPS,
	JUMP,
	GUN
}				e_sounds;

typedef enum	e_sound_channel
{
	MUSIC,
	WEAPON,
	STEPS,
	TTS
}				e_sound_channel;

#endif
