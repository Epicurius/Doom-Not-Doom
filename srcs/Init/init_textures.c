/*
 * https://github.com/Epicurius/Doom-Not-Doom
 * 
 * Created: 2021/05/01 14:05:32 nneronin
 * Updated: 2022/01/20 14:23:29 Niklas Neronin
 */

#include "doom.h"

static inline void	parse_textures_scaled(t_doom *doom, t_bxpm *bxpm,
	const char **g, int amount, float scale)
{
	int	i;

	i = -1;
	while (++i < amount)
	{
		ft_strcpy(&doom->root[doom->rlen + BXPM_LEN], g[i]);
		if (!read_bxpm_scaled(&bxpm[i], doom->root, scale))
			LG_ERROR("read_bxpm_scaled %s.", doom->root);
	}
}

static inline void	parse_textures(t_doom *doom, t_bxpm *bxpm,
	const char **g, int amount)
{
	int	i;

	i = -1;
	while (++i < amount)
	{
		ft_strcpy(&doom->root[doom->rlen + BXPM_LEN], g[i]);
		if (!read_bxpm(&bxpm[i], doom->root))
			LG_ERROR("read_bxpm %s.", doom->root);
	}
}

void	init_textures(t_doom *doom)
{
	ft_strcpy(&doom->root[doom->rlen], BXPM_PATH);
	parse_surface_textures(doom, -1, -1);
	parse_textures(doom, doom->etx, g_entity_textures,
		ENTITY_TEXTURE_AMOUNT);
	parse_textures_scaled(doom, doom->itx, g_icon_textures,
		ICON_TEXTURE_AMOUNT, doom->c.x * 0.002);
	parse_textures_scaled(doom, doom->weapon[WEAPON_SHOTGUN].bxpm,
		g_shotgun_textures, SHOTGUN_TEXTURE_AMOUNT, doom->c.x * 0.00125);
	parse_textures_scaled(doom, doom->weapon[WEAPON_GUN].bxpm,
		g_glock_textures, GLOCK_TEXTURE_AMOUNT, doom->c.x * 0.001);
	parse_textures_scaled(doom, doom->weapon[WEAPON_KAR].bxpm,
		g_kar_textures, KAR_TEXTURE_AMOUNT, doom->c.x * 0.003);
	parse_textures_scaled(doom, doom->weapon[WEAPON_LAUNCHER].bxpm,
		g_launcher_textures, LAUNCHER_TEXTURE_AMOUNT, doom->c.x * 0.00125);
	parse_textures_scaled(doom, doom->weapon[WEAPON_MINIGUN].bxpm,
		g_minigun_textures, MINIGUN_TEXTURE_AMOUNT, doom->c.x * 0.0025);
	init_clock(doom, &doom->mtx[MAP_TEXTURE_AMOUNT - 1]);
	sector_shading(doom, -1, -1);
}
