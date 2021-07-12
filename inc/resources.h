/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resources.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/11 10:31:43 by nneronin          #+#    #+#             */
/*   Updated: 2021/07/12 13:00:39 by jsalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESOURCES_H
# define RESOURCES_H

# include "path.h"
# include "enum.h"

typedef struct s_id_and_path
{
	int			id;
	char		*path;
}				t_id_and_path;

# define WAV_AMOUNT	7
static const t_id_and_path	g_sounds[WAV_AMOUNT] =
{
	{WAV_MAIN_THEME, WAV_PATH"at_dooms_gate.wav"},
	{WAV_SHOTGUN, WAV_PATH"shotgun.wav"},
	{WAV_SCREEN_SHOT, WAV_PATH"tts_saved.wav"},
	{WAV_INTRO, WAV_PATH"intro.wav"},
	{WAV_FOOT_STEPS, WAV_PATH"footsteps.wav"},
	{WAV_JUMP, WAV_PATH"jump.wav"},
	{WAV_GUN, WAV_PATH"gun.wav"}
};

# define MAP_TEXTURE_AMOUNT	15
static const t_id_and_path	g_map_textures[MAP_TEXTURE_AMOUNT] =
{
	{0, BXPM_PATH"bh.bxpm"},
	{1, BXPM_PATH"vent.bxpm"},
	{2, BXPM_PATH"tile_floor.bxpm"},
	{3, BXPM_PATH"bars.bxpm"},
	{4, "NULL"},
	{5, BXPM_PATH"DoomScore.bxpm"},
	{6, BXPM_PATH"lava.bxpm"},
	{7, BXPM_PATH"metal_wall.bxpm"},
	{8, BXPM_PATH"door.bxpm"},
	{9, BXPM_PATH"console.bxpm"},
	{10, BXPM_PATH"green_wall.bxpm"},
	{11, BXPM_PATH"radar.bxpm"},
	{12, BXPM_PATH"steel.bxpm"},
	{13, BXPM_PATH"wall_panel.bxpm"},
	{14, BXPM_PATH"metal_tile2.bxpm"}
};

# define SKYBOX_TEXTURE_AMOUNT	12
static const t_id_and_path	g_skybox_textures[SKYBOX_TEXTURE_AMOUNT] =
{
	{0, BXPM_PATH"space3.bxpm"},
	{1, BXPM_PATH"space0.bxpm"},
	{2, BXPM_PATH"space1.bxpm"},
	{3, BXPM_PATH"space2.bxpm"},
	{4, BXPM_PATH"space4.bxpm"},
	{5, BXPM_PATH"space5.bxpm"},
	{6, BXPM_PATH"land4.bxpm"},
	{7, BXPM_PATH"land1.bxpm"},
	{8, BXPM_PATH"land2.bxpm"},
	{9, BXPM_PATH"land3.bxpm"},
	{10, BXPM_PATH"land0.bxpm"},
	{11, BXPM_PATH"land5.bxpm"}
};

# define ICON_TEXTURE_AMOUNT	5
static const t_id_and_path	g_icon_textures[ICON_TEXTURE_AMOUNT] =
{
	{0, ICON_PATH"health_heart.bxpm"},
	{1, ICON_PATH"armour_shield.bxpm"},
	{2, ICON_PATH"ammo_patrons.bxpm"},
	{3, ICON_PATH"mag_ammo.bxpm"},
	{4, ICON_PATH"cash_dosh.bxpm"}
};

# define ENTITY_TEXTURE_AMOUNT	4
static const t_id_and_path	g_entity_textures[ENTITY_TEXTURE_AMOUNT] =
{
	{0, BXPM_PATH"alfred.bxpm"},
	{1, BXPM_PATH"spooky.bxpm"},
	{2, BXPM_PATH"rift.bxpm"},
	{3, BXPM_PATH"objects.bxpm"}
};

# define SHOTGUN_TEXTURE_AMOUNT	14
static const t_id_and_path	g_shotgun_textures[SHOTGUN_TEXTURE_AMOUNT] =
{
	{0, BXPM_PATH"shotgun-0.bxpm"},
	{1, BXPM_PATH"shotgun-1.bxpm"},
	{2, BXPM_PATH"shotgun-2.bxpm"},
	{3, BXPM_PATH"shotgun-3.bxpm"},
	{4, BXPM_PATH"shotgun-4.bxpm"},
	{5, BXPM_PATH"shotgun-5.bxpm"},
	{6, BXPM_PATH"shotgun-6.bxpm"},
	{7, BXPM_PATH"shotgun-7.bxpm"},
	{8, BXPM_PATH"shotgun-8.bxpm"},
	{9, BXPM_PATH"shotgun-9.bxpm"},
	{10, BXPM_PATH"shotgun-10.bxpm"},
	{11, BXPM_PATH"shotgun-11.bxpm"},
	{12, BXPM_PATH"shotgun-12.bxpm"},
	{13, BXPM_PATH"shotgun-13.bxpm"}
};

# define GLOCK_TEXTURE_AMOUNT	6
static const t_id_and_path	g_glock_textures[GLOCK_TEXTURE_AMOUNT] =
{
	{0, BXPM_PATH"glock-0.bxpm"},
	{1, BXPM_PATH"glock-1.bxpm"},
	{2, BXPM_PATH"glock-2.bxpm"},
	{3, BXPM_PATH"glock-3.bxpm"},
	{4, BXPM_PATH"glock-4.bxpm"},
	{5, BXPM_PATH"glock-5.bxpm"}
};

# define MINIGUN_TEXTURE_AMOUNT	6
static const t_id_and_path	g_minigun_textures[MINIGUN_TEXTURE_AMOUNT] =
{
	{0, BXPM_PATH"minigun-0.bxpm"},
	{1, BXPM_PATH"minigun-1.bxpm"},
	{2, BXPM_PATH"minigun-2.bxpm"},
	{3, BXPM_PATH"minigun-3.bxpm"},
	{4, BXPM_PATH"minigun-4.bxpm"},
	{5, BXPM_PATH"minigun-5.bxpm"}
};

# define KAR_TEXTURE_AMOUNT	38
static const t_id_and_path	g_kar_textures[KAR_TEXTURE_AMOUNT] =
{
	{0, BXPM_PATH"kar-0.bxpm"},
	{1, BXPM_PATH"kar-1.bxpm"},
	{2, BXPM_PATH"kar-2.bxpm"},
	{3, BXPM_PATH"kar-3.bxpm"},
	{4, BXPM_PATH"kar-4.bxpm"},
	{5, BXPM_PATH"kar-5.bxpm"},
	{6, BXPM_PATH"kar-6.bxpm"},
	{7, BXPM_PATH"kar-7.bxpm"},
	{8, BXPM_PATH"kar-8.bxpm"},
	{9, BXPM_PATH"kar-9.bxpm"},
	{10, BXPM_PATH"kar-10.bxpm"},
	{11, BXPM_PATH"kar-11.bxpm"},
	{12, BXPM_PATH"kar-12.bxpm"},
	{13, BXPM_PATH"kar-13.bxpm"},
	{14, BXPM_PATH"kar-14.bxpm"},
	{15, BXPM_PATH"kar-15.bxpm"},
	{16, BXPM_PATH"kar-16.bxpm"},
	{17, BXPM_PATH"kar-17.bxpm"},
	{18, BXPM_PATH"kar-18.bxpm"},
	{19, BXPM_PATH"kar-19.bxpm"},
	{20, BXPM_PATH"kar-20.bxpm"},
	{21, BXPM_PATH"kar-21.bxpm"},
	{22, BXPM_PATH"kar-22.bxpm"},
	{23, BXPM_PATH"kar-23.bxpm"},
	{24, BXPM_PATH"kar-24.bxpm"},
	{25, BXPM_PATH"kar-25.bxpm"},
	{26, BXPM_PATH"kar-26.bxpm"},
	{27, BXPM_PATH"kar-27.bxpm"},
	{28, BXPM_PATH"kar-28.bxpm"},
	{29, BXPM_PATH"kar-29.bxpm"},
	{30, BXPM_PATH"kar-30.bxpm"},
	{31, BXPM_PATH"kar-31.bxpm"},
	{32, BXPM_PATH"kar-32.bxpm"},
	{33, BXPM_PATH"kar-33.bxpm"},
	{34, BXPM_PATH"kar-34.bxpm"},
	{35, BXPM_PATH"kar-35.bxpm"},
	{36, BXPM_PATH"kar-36.bxpm"},
	{37, BXPM_PATH"kar-37.bxpm"}
};

# define PUMP_TEXTURE_AMOUNT	9
static const t_id_and_path	g_pump_textures[PUMP_TEXTURE_AMOUNT] =
{
	{0, BXPM_PATH"pump-0.bxpm"},
	{1, BXPM_PATH"pump-1.bxpm"},
	{2, BXPM_PATH"pump-2.bxpm"},
	{3, BXPM_PATH"pump-3.bxpm"},
	{4, BXPM_PATH"pump-4.bxpm"},
	{5, BXPM_PATH"pump-5.bxpm"},
	{6, BXPM_PATH"pump-6.bxpm"},
	{7, BXPM_PATH"pump-7.bxpm"},
	{8, BXPM_PATH"pump-8.bxpm"}
};

typedef struct s_entity_data
{
	char			*name;
	int				health;
	int				height;
	int				hitbox_radius;
	double			speed;
	int				flying;
	int				damage;
	int				animate;
	int				hostile;
	int				attack_style;
	double			scale;
	int				move;
	int				view_distance;
	int				detection_radius;
	int				attack_range;
	int				frame_rate[4];
	char			*path;
	int				tc[4];
}					t_entity_data;

# define ENTITY_AMOUNT	7
static const t_entity_data	g_entity_data[ENTITY_AMOUNT] = 
{
	{//	Alferd
		.name = "Alfred",
		.health = 1,
		.damage = 100,
		.animate = 1,
		.hostile = 1,
		.attack_style = 2,
		.scale = 4,
		.height = 2,
		.hitbox_radius = 2,
		.speed = 20,
		.move = 1,
		.view_distance = 200,
		.detection_radius = 40,
		.attack_range = 7,
		.flying = 1,
		.frame_rate[IDLE] = 2000,
		.frame_rate[MOVE] = 4000,
		.frame_rate[ATTACK] = 6000,
		.frame_rate[DEATH] = 6000,
		.path = BXPM_PATH"alfred.bxpm",
		.tc = {0, 0, 43, 47}
	},
	{//	Spooky
		.name = "Spooky",
		.health = 1,
		.damage = 30,
		.animate = 1,
		.hostile = 1,
		.attack_style = 1,
		.scale = 2,
		.height = 7,
		.hitbox_radius = 2,
		.speed = 10,
		.move = 1,
		.view_distance = 100,
		.detection_radius = 40,
		.attack_range = 50,
		.flying = 0,
		.frame_rate[IDLE] = 2000,
		.frame_rate[MOVE] = 6000,
		.frame_rate[ATTACK] = 18000,
		.frame_rate[DEATH] = 12000,
		.path = BXPM_PATH"spooky.bxpm",
		.tc = {25, 193, 139 - 25, 377 - 193}
	},
	{//	Rift
		.name = "Rift",
		.health = 1,
		.damage = 200,
		.animate = 0,
		.hostile = 0,
		.attack_style = 2,
		.scale = 2,
		.height = 9,
		.hitbox_radius = 0,
		.speed = 0,
		.move = 0,
		.view_distance = 0,
		.detection_radius = 0,
		.attack_range = 0,
		.flying = 0,
		.frame_rate[IDLE] = 2000,
		.frame_rate[MOVE] = 8000,
		.frame_rate[ATTACK] = 0,
		.frame_rate[DEATH] = 0,
		.path = BXPM_PATH"rift.bxpm",
		.tc = {0, 0, 174, 315}
	},
	{//	Barrel
		.name = "Barrel",
		.health = 20,
		.damage = 0,
		.animate = 0,
		.hostile = 0,
		.attack_style = 0,
		.scale = 5,
		.height = 0,
		.hitbox_radius = 0,
		.speed = 0,
		.move = 0,
		.view_distance = 0,
		.detection_radius = 0,
		.attack_range = 0,
		.flying = 0,
		.frame_rate[IDLE] = 6000,
		.frame_rate[MOVE] = 0,
		.frame_rate[ATTACK] = 0,
		.frame_rate[DEATH] = 0,
		.path = BXPM_PATH"objects.bxpm",
		.tc = {174, 182, 209 - 174, 233 - 182}
	},
	{//	Lamp
		.name = "Lamp",
		.health = 11120,
		.damage = 0,
		.animate = 0,
		.hostile = 0,
		.attack_style = 0,
		.scale = 5,
		.height = 0,
		.hitbox_radius = 0,
		.speed = 0,
		.move = 0,
		.view_distance = 0,
		.detection_radius = 0,
		.attack_range = 0,
		.flying = 0,
		.frame_rate[IDLE] = 3000,
		.frame_rate[MOVE] = 0,
		.frame_rate[ATTACK] = 0,
		.frame_rate[DEATH] = 0,
		.path = BXPM_PATH"objects.bxpm",
		.tc = {174, 7, 197 - 174, 91 - 7}
	},
	{//	Torch
		.name = "Torch",
		.health = 11120,
		.damage = 0,
		.animate = 0,
		.hostile = 0,
		.attack_style = 0,
		.scale = 5,
		.height = 0,
		.hitbox_radius = 0,
		.speed = 0,
		.move = 0,
		.view_distance = 0,
		.detection_radius = 0,
		.attack_range = 0,
		.flying = 0,
		.frame_rate[IDLE] = 9000,
		.frame_rate[MOVE] = 0,
		.frame_rate[ATTACK] = 0,
		.frame_rate[DEATH] = 0,
		.path = BXPM_PATH"objects.bxpm",
		.tc = {371, 209, 381 - 371, 256 - 209}
	},
	{//	Meat_Hook
		.name = "Meat Hook",
		.health = 11120,
		.damage = 0,
		.animate = 0,
		.hostile = 0,
		.attack_style = 0,
		.scale = 10,
		.height = 0,
		.hitbox_radius = 0,
		.speed = 0,
		.move = 0,
		.view_distance = 0,
		.detection_radius = 0,
		.attack_range = 0,
		.flying = 0,
		.frame_rate[IDLE] = 1000,
		.frame_rate[MOVE] = 0,
		.frame_rate[ATTACK] = 0,
		.frame_rate[DEATH] = 0,
		.path = BXPM_PATH"objects.bxpm",
		.tc = {543, 5, 579 - 543, 104 - 5}
	}
};

#endif
