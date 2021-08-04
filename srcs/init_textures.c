/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 14:05:32 by nneronin          #+#    #+#             */
/*   Updated: 2021/08/04 13:55:07 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	parse_bxpm(t_doom *doom, int amount, t_bxpm *dest,
	const t_id_and_path *src)
{
	int				i;
	t_thread_bxpm	*threads;

	threads = malloc(sizeof(t_thread_bxpm) * amount);
	if (!threads)
		error_msg("Parse bxpm threads malloc\n");
	i = -1;
	while (++i < amount)
	{
		threads[src[i].id].path = ft_strdup(src[i].path);
		threads[src[i].id].bxpm = &dest[src[i].id];
		tpool_add(&doom->tpool, multithread_read_bxpm, &threads[src[i].id]);
	}
	tpool_wait(&doom->tpool);
	free(threads);
}

static void	parse_wtx_texture(t_doom *doom, t_thread_bxpm *threads, int id)
{
	if (!threads[id].active && g_map_textures[id].id != MAP_TEXTURE_AMOUNT - 1)
	{
		threads[id].active = 1;
		threads[id].path = ft_strdup(g_map_textures[id].path);
		threads[id].bxpm = &doom->mtx[id];
		tpool_add(&doom->tpool, multithread_read_bxpm, &threads[id]);
	}
}

static void	parse_stx_texture(t_doom *doom, t_thread_bxpm *threads, int id)
{
	int	i;

	id = abs(id) - 1;
	if (!threads[id].active)
	{
		threads[id].active = 1;
		i = id;
		while (i < id + 6)
		{
			threads[i].path = ft_strdup(g_skybox_textures[i].path);
			threads[i].bxpm = &doom->stx[i];
			tpool_add(&doom->tpool, multithread_read_bxpm, &threads[i]);
			i++;
		}
	}
}

static void	parse_map_textures(t_doom *doom, int i, int j)
{
	t_thread_bxpm	wtx_threads[MAP_TEXTURE_AMOUNT];
	t_thread_bxpm	stx_threads[SKYBOX_TEXTURE_AMOUNT];

	ft_bzero(&wtx_threads, sizeof(t_thread_bxpm) * MAP_TEXTURE_AMOUNT);
	ft_bzero(&stx_threads, sizeof(t_thread_bxpm) * SKYBOX_TEXTURE_AMOUNT);
	i = -1;
	while (++i < doom->nb.walls)
	{
		if (doom->walls[i].wtx < 0)
			parse_stx_texture(doom, stx_threads, doom->walls[i].wtx);
		else
			parse_wtx_texture(doom, wtx_threads, doom->walls[i].wtx);
		parse_wtx_texture(doom, wtx_threads, doom->walls[i].ptx);
		j = -1;
		while (++j < doom->walls[i].wsprite.total)
			parse_wtx_texture(doom, wtx_threads,
				doom->walls[i].wsprite.num[j].tx);
	}
	i = -1;
	while (++i < doom->nb.sectors)
	{
		parse_wtx_texture(doom, wtx_threads, doom->sectors[i].ceiling.tx);
		parse_wtx_texture(doom, wtx_threads, doom->sectors[i].floor.tx);
	}
	tpool_wait(&doom->tpool);
}

//parse_bxpm(doom, MAP_TEXTURE_AMOUNT - 1,
//	doom->mtx, g_map_textures);
//parse_bxpm(doom, SKYBOX_TEXTURE_AMOUNT,
//	doom->stx, g_skybox_textures);
void	init_textures(t_doom *doom)
{
	parse_map_textures(doom, -1, -1);
	parse_bxpm(doom, ENTITY_TEXTURE_AMOUNT,
		doom->etx, g_entity_textures);
	parse_bxpm(doom, ICON_TEXTURE_AMOUNT,
		doom->itx, g_icon_textures);
	parse_bxpm(doom, SHOTGUN_TEXTURE_AMOUNT,
		doom->weapon[0].bxpm, g_shotgun_textures);
	parse_bxpm(doom, GLOCK_TEXTURE_AMOUNT,
		doom->weapon[1].bxpm, g_glock_textures);
	parse_bxpm(doom, MINIGUN_TEXTURE_AMOUNT,
		doom->weapon[2].bxpm, g_minigun_textures);
	parse_bxpm(doom, KAR_TEXTURE_AMOUNT,
		doom->weapon[3].bxpm, g_kar_textures);
	parse_bxpm(doom, LAUNCHER_TEXTURE_AMOUNT,
		doom->weapon[4].bxpm, g_launcher_textures);
	init_clock(doom, &doom->mtx[MAP_TEXTURE_AMOUNT - 1]);
	color_palets(doom);
}
