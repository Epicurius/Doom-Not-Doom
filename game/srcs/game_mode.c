/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Niklas Neronin <niklas.neronin@gmail.com>
 */

#include "doom.h"

/*
 *	Removes any MedKits left over from previous round.
 */
static void	remove_med_kits(t_doom *doom)
{
	t_list		*curr;

	curr = doom->entity;
	while (curr != NULL)
	{
		if (((t_entity *)curr->content)->type == MED_KIT)
		{
			curr = ft_dellstnode(&doom->entity, curr);
			doom->nb.entities -= 1;
		}
		else
			curr = curr->next;
	}
}

/*
 *	Checks and handels round end or start.
 */
static int	endless_round(t_doom *doom)
{
	if (doom->game.spawns == 0)
	{
		doom->game.round++;
		doom->game.cool_down = 10;
		doom->game.spawn_rate -= doom->game.round * 2;
		doom->player.health = 1100 - doom->settings.difficulty * 100;
		doom->player.store_access = TRUE;
		Mix_HaltChannel(CHANNEL_MUSIC);
		Mix_PlayChannel(CHANNEL_ROUND, doom->sound[WAV_ROUND_END], 0);
		return (1);
	}
	else if (doom->time.curr - doom->game.time > doom->game.spawn_rate)
	{
		rift_spawn(doom);
		doom->game.time = doom->time.curr;
	}
	return (0);
}

/*
 *	Handels the endless game mode.
 *	Spawning enemies, giving store access to the player,
 *	handling rounds and respawning rifts.
 *	
 */
static void	game_mode_endless(t_doom *doom)
{
	int	i;

	i = -1;
	if (!Mix_Playing(CHANNEL_TTS) && doom->game.cool_down > 0)
	{
		doom->game.cool_down -= 1 * doom->time.delta;
		if (doom->game.cool_down <= 0)
		{
			Mix_PlayChannel(CHANNEL_ROUND, doom->sound[WAV_NEW_ROUND], 0);
			doom->player.store_access = FALSE;
			while (++i < doom->nb.events)
				if (doom->events[i].type == STORE && doom->events[i].wsprite)
					doom->events[i].wsprite->src = rect_xy2(662, 0, 1324, 550);
			remove_med_kits(doom);
			respawn_rifts(doom);
			Mix_PlayChannel(CHANNEL_MUSIC, doom->sound[WAV_MAIN_THEME], -1);
		}
	}
	else if (!Mix_Playing(CHANNEL_TTS) && endless_round(doom))
	{
		while (++i < doom->nb.events)
			if (doom->events[i].type == STORE && doom->events[i].wsprite)
				doom->events[i].wsprite->src = rect_xy2(0, 0, 662, 550);
	}
}

/*
 *	Handels the story game mode.
 *	Spawning enemies from rifts if any are present.
 */
static void	game_mode_story(t_doom *doom)
{
	if (doom->time.curr - doom->game.time > doom->game.spawn_rate)
	{
		rift_spawn(doom);
		doom->game.time = doom->time.curr;
	}
}

/*
 *	Small function, made for handling future game modes.
 */
void	game_mode(t_doom *doom)
{
	if (doom->game.mode == ENDLESS)
		game_mode_endless(doom);
	else
		game_mode_story(doom);
}
