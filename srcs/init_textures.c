/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 14:05:32 by nneronin          #+#    #+#             */
/*   Updated: 2021/07/16 14:30:57 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

//int		multy_thread_bxpm(void  *arg)
//{
//	if (read_bxpm(((t_thread_bxpm *)arg)->bxpm, ((t_thread_bxpm *)arg)->path));
//		return (1);
//	ft_printf("Could not read %s\n", ((t_thread_bxpm *)arg)->path);
//	return (0);
//}
//
//static void	parse(t_doom *doom, int amount, t_bxpm *dest, t_id_and_path *src)
//{
//	int				i;
//	t_thread_bxpm	*threads;
//
//	threads = malloc(sizeof(t_thread_bxpm) * amount);
//	if (!threads)
//		error_msg("parse bxpm threads malloc\n");
//	i = -1;
//	while (++i < amount)
//	{
//		if (ft_strequ(src[i].path, "NULL"))
//			continue ;
//		threads[src[i].id].path = ft_strdup(src[i].path);
//		threads[src[i].id].bxpm = &dest[src[i].id];
//		tpool_add(&doom->tpool, multy_thread_bxpm, &threads[src[i].id]);
//	}
//	tpool_wait(&doom->tpool);
//	free(threads);
//}
//
static void	parse(int amount, t_bxpm *dest, t_id_and_path *src)
{
	int	i;

	i = -1;
	while (++i < amount)
	{
		if (ft_strequ(src[i].path, "NULL"))
			continue ;
		if (!read_bxpm(&dest[src[i].id], src[i].path))
			error_msg("Reading[%d]: %s", src[i].id, src[i].path);
	}
}

void	init_textures(t_doom *doom)
{
	parse(MAP_TEXTURE_AMOUNT, doom->mtx, g_map_textures);
	parse(SKYBOX_TEXTURE_AMOUNT, doom->stx, g_skybox_textures);
	parse(ENTITY_TEXTURE_AMOUNT, doom->etx, g_entity_textures);
	parse(ICON_TEXTURE_AMOUNT, doom->itx, g_icon_textures);
	parse(SHOTGUN_TEXTURE_AMOUNT, doom->weapon[0].bxpm, g_shotgun_textures);
	parse(GLOCK_TEXTURE_AMOUNT, doom->weapon[1].bxpm, g_glock_textures);
	parse(MINIGUN_TEXTURE_AMOUNT, doom->weapon[2].bxpm, g_minigun_textures);
	parse(KAR_TEXTURE_AMOUNT, doom->weapon[3].bxpm, g_kar_textures);
	parse(PUMP_TEXTURE_AMOUNT, doom->weapon[4].bxpm, g_pump_textures);
	init_clock(doom, &doom->mtx[4]);
	color_palets(doom);
}
