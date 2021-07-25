/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 14:05:32 by nneronin          #+#    #+#             */
/*   Updated: 2021/07/25 09:47:10 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int	multy_thread_bxpm(void *arg)
{
	int	res;

	res = read_bxpm(((t_thread_bxpm *)arg)->bxpm, ((t_thread_bxpm *)arg)->path);
	free(((t_thread_bxpm *)arg)->path);
	if (res)
		return (1);
	ft_printf("Could not read %s\n", ((t_thread_bxpm *)arg)->path);
	return (0);
}

static void	get(t_doom *doom, int amount, t_bxpm *dest, const t_id_and_path *src)
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
		tpool_add(&doom->tpool, multy_thread_bxpm, &threads[src[i].id]);
	}
	tpool_wait(&doom->tpool);
	free(threads);
}

void	init_textures(t_doom *doom)
{
	get(doom, MAP_TEXTURE_AMOUNT - 1, doom->mtx, g_map_textures);
	get(doom, SKYBOX_TEXTURE_AMOUNT, doom->stx, g_skybox_textures);
	get(doom, ENTITY_TEXTURE_AMOUNT, doom->etx, g_entity_textures);
	get(doom, ICON_TEXTURE_AMOUNT, doom->itx, g_icon_textures);
	get(doom, SHOTGUN_TEXTURE_AMOUNT, doom->weapon[0].bxpm, g_shotgun_textures);
	get(doom, GLOCK_TEXTURE_AMOUNT, doom->weapon[1].bxpm, g_glock_textures);
	get(doom, MINIGUN_TEXTURE_AMOUNT, doom->weapon[2].bxpm, g_minigun_textures);
	get(doom, KAR_TEXTURE_AMOUNT, doom->weapon[3].bxpm, g_kar_textures);
	get(doom, PUMP_TEXTURE_AMOUNT, doom->weapon[4].bxpm, g_pump_textures);
	init_clock(doom, &doom->mtx[MAP_TEXTURE_AMOUNT - 1]);
	color_palets(doom);
}
