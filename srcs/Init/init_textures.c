/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 14:05:32 by nneronin          #+#    #+#             */
/*   Updated: 2021/12/28 16:37:01 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int	multithread_idk1(void *arg)
{
	parse_surface_textures((t_doom *)arg, -1, -1);	
	return (1);
}

int	multithread_idk2(void *arg)
{
	t_doom *doom = arg;
	
	int i = -1;
	while (++i < ENTITY_TEXTURE_AMOUNT)
		read_bxpm(&doom->etx[g_entity_textures[i].id], g_entity_textures[i].path);
	i = -1;
	while (++i < ICON_TEXTURE_AMOUNT)
		read_bxpm(&doom->itx[g_icon_textures[i].id], g_icon_textures[i].path);
	i = -1;
	while (++i < SHOTGUN_TEXTURE_AMOUNT)
		read_bxpm_scaled(&doom->weapon[WEAPON_SHOTGUN].bxpm[i], g_shotgun_textures[i].path, doom->c.x / 800.0);
	i = -1;
	while (++i < GLOCK_TEXTURE_AMOUNT)
		read_bxpm_scaled(&doom->weapon[WEAPON_GUN].bxpm[i], g_glock_textures[i].path, doom->c.x / 900.0);
	i = -1;
	while (++i < KAR_TEXTURE_AMOUNT)
		read_bxpm_scaled(&doom->weapon[WEAPON_KAR].bxpm[i], g_kar_textures[i].path, doom->c.x / 340.0);
	i = -1;
	while (++i < LAUNCHER_TEXTURE_AMOUNT)
		read_bxpm_scaled(&doom->weapon[WEAPON_LAUNCHER].bxpm[i], g_launcher_textures[i].path, doom->c.x / 800.0);
	i = -1;
	while (++i < MINIGUN_TEXTURE_AMOUNT)
		read_bxpm_scaled(&doom->weapon[WEAPON_MINIGUN].bxpm[i], g_minigun_textures[i].path, doom->c.x / 400.0);	
	return (1);
}

void	init_textures(t_doom *doom)
{
	int	i;
	
	parse_surface_textures(doom, -1, -1);	
	i = -1;
	while (++i < ENTITY_TEXTURE_AMOUNT)
		read_bxpm(&doom->etx[g_entity_textures[i].id], g_entity_textures[i].path);
	i = -1;
	while (++i < ICON_TEXTURE_AMOUNT)
		read_bxpm(&doom->itx[g_icon_textures[i].id], g_icon_textures[i].path);
	i = -1;
	while (++i < SHOTGUN_TEXTURE_AMOUNT)
		read_bxpm_scaled(&doom->weapon[WEAPON_SHOTGUN].bxpm[i], g_shotgun_textures[i].path, doom->c.x / 800.0);
	i = -1;
	while (++i < GLOCK_TEXTURE_AMOUNT)
		read_bxpm_scaled(&doom->weapon[WEAPON_GUN].bxpm[i], g_glock_textures[i].path, doom->c.x / 900.0);
	i = -1;
	while (++i < KAR_TEXTURE_AMOUNT)
		read_bxpm_scaled(&doom->weapon[WEAPON_KAR].bxpm[i], g_kar_textures[i].path, doom->c.x / 340.0);
	i = -1;
	while (++i < LAUNCHER_TEXTURE_AMOUNT)
		read_bxpm_scaled(&doom->weapon[WEAPON_LAUNCHER].bxpm[i], g_launcher_textures[i].path, doom->c.x / 800.0);
	i = -1;
	while (++i < MINIGUN_TEXTURE_AMOUNT)
		read_bxpm_scaled(&doom->weapon[WEAPON_MINIGUN].bxpm[i], g_minigun_textures[i].path, doom->c.x / 400.0);
	//tpool_add(&doom->tpool, multithread_idk1, doom);
	//tpool_add(&doom->tpool, multithread_idk2, doom);
	init_clock(doom, &doom->mtx[MAP_TEXTURE_AMOUNT - 1]);
	sector_shading(doom, -1, -1);
	//tpool_wait(&doom->tpool);
}
