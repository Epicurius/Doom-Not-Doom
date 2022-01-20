/*
 * https://github.com/Epicurius/Doom-Not-Doom
 * 
 * Created: 2021/12/28 15:07:29 nneronin
 * Updated: 2022/01/20 14:15:54 Niklas Neronin
 */

#include "doom.h"

static void	parse_wtx_texture(t_doom *doom, unsigned char *wtx_bool, int id)
{
	if (id < 0 || id == MAP_TEXTURE_AMOUNT - 1)
		return ;
	if (!wtx_bool[id])
	{
		wtx_bool[id] = TRUE;
		ft_strcpy(&doom->root[doom->rlen + BXPM_LEN], g_map_textures[id]);
		read_bxpm(&doom->mtx[id], doom->root);
	}
}

static void	parse_stx_texture(t_doom *doom, unsigned char *stx_bool, int id)
{
	int	i;

	id = (abs(id) - 1) * 6;
	if (!stx_bool[id])
	{
		stx_bool[id] = TRUE;
		i = id;
		while (i < id + 6)
		{
			ft_strcpy(&doom->root[doom->rlen + BXPM_LEN], g_skybox_textures[i]);
			read_bxpm(&doom->stx[i], doom->root);
			i++;
		}
	}
}

void	parse_surface_textures(t_doom *doom, int i, int j)
{
	unsigned char	wtx_bool[MAP_TEXTURE_AMOUNT];
	unsigned char	stx_bool[SKYBOX_TEXTURE_AMOUNT];

	memset(&wtx_bool, 0, MAP_TEXTURE_AMOUNT);
	memset(&stx_bool, 0, SKYBOX_TEXTURE_AMOUNT);
	parse_wtx_texture(doom, wtx_bool, 0);
	while (++i < doom->nb.walls)
	{
		if (doom->walls[i].wtx < 0)
			parse_stx_texture(doom, stx_bool, doom->walls[i].wtx);
		else
			parse_wtx_texture(doom, wtx_bool, doom->walls[i].wtx);
		parse_wtx_texture(doom, wtx_bool, doom->walls[i].ptx);
		j = -1;
		while (++j < doom->walls[i].wsprite.total)
			parse_wtx_texture(doom, wtx_bool, doom->walls[i].wsprite.num[j].tx);
	}
	i = -1;
	while (++i < doom->nb.sectors)
	{
		parse_wtx_texture(doom, wtx_bool, doom->sectors[i].ceiling.tx);
		parse_wtx_texture(doom, wtx_bool, doom->sectors[i].floor.tx);
	}
}
