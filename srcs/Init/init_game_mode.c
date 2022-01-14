/*
 * https://github.com/Epicurius/Doom-Not-Doom
 * 
 * Created: 2021/06/20 11:32:29 nneronin
 * Updated: 2021/12/15 12:01:20 nneronin
 */

#include "doom.h"

static void	init_endless(t_doom *doom)
{
	int		i;
	t_list	*curr;

	ft_bzero(&doom->game, sizeof(t_game));
	doom->game.mode = ENDLESS;
	doom->game.spawn_rate = 5000 - doom->settings.difficulty * 750;
	curr = doom->entity;
	while (curr)
	{
		if (((t_entity *)curr->content)->type == ALFRED
			|| ((t_entity *)curr->content)->type == SPOOKY
			|| ((t_entity *)curr->content)->type == GHOST
			|| ((t_entity *)curr->content)->type == RIFT)
			curr = ft_dellstnode(&doom->entity, curr);
		else
			curr = curr->next;
	}
	doom->game.cool_down = 1;
	doom->player.store_access = FALSE;
	i = -1;
	while (++i < doom->nb.events)
		if (doom->events[i].type == STORE && doom->events[i].wsprite)
			doom->events[i].wsprite->src = rect_xy2(662, 0, 1324, 550);
}

static void	init_story(t_doom *doom)
{
	ft_bzero(&doom->game, sizeof(t_game));
	doom->game.mode = STORY;
	doom->game.spawn_rate = 5000 - doom->settings.difficulty * 750;
	doom->player.store_access = TRUE;
}

void	init_game_mode(t_doom *doom)
{
	doom->game.time = doom->time.curr;
	if (doom->game.mode == ENDLESS)
		init_endless(doom);
	else if (doom->game.mode == STORY)
		init_story(doom);
}
