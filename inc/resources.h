/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resources.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/11 10:31:43 by nneronin          #+#    #+#             */
/*   Updated: 2021/09/23 11:33:50 by nneronin         ###   ########.fr       */
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

static const t_id_and_path	g_sounds[WAV_AMOUNT] =
{
	{WAV_MAIN_THEME, WAV_PATH"at_dooms_gate.wav"},
	{WAV_SHOTGUN, WAV_PATH"shotgun.wav"},
	{WAV_SCREEN_SHOT, WAV_PATH"tts_saved.wav"},
	{WAV_INTRO, WAV_PATH"intro.wav"},
	{WAV_FOOT_STEPS, WAV_PATH"footsteps.wav"},
	{WAV_JUMP, WAV_PATH"jump.wav"},
	{WAV_GUN, WAV_PATH"gun.wav"},
	{WAV_ELEVATOR_MUSIC, WAV_PATH"elevator_music.wav"},
	{WAV_DOSH, WAV_PATH"dosh.wav"},
	{WAV_EMPTY_CLIP, WAV_PATH"empty_clip.wav"},
	{WAV_BIP, WAV_PATH"bip.wav"},
	{WAV_ORB, WAV_PATH"orb.wav"},
	{WAV_ROUND_END, WAV_PATH"round_end.wav"},
	{WAV_NEW_ROUND, WAV_PATH"new_round.wav"},
	{WAV_MONSTER_HIT, WAV_PATH"EntityHit.wav"},
	{WAV_PLAYER_HIT, WAV_PATH"PlayerHit.wav"},
	{WAV_ENTITY_DEATH, WAV_PATH"EntityDeath.wav"},
	{WAV_PLAYER_DEATH, WAV_PATH"PlayerDeath.wav"}
};

# define MAP_TEXTURE_AMOUNT	21
static const t_id_and_path	g_map_textures[MAP_TEXTURE_AMOUNT] =
{	
	{0, BXPM_PATH"bullet_hole.bxpm"},
	{1, BXPM_PATH"vent.bxpm"},
	{2, BXPM_PATH"tile_floor.bxpm"},
	{3, BXPM_PATH"bars.bxpm"},
	{4, BXPM_PATH"wall_button.bxpm"},
	{5, BXPM_PATH"cog.bxpm"},
	{6, BXPM_PATH"lava.bxpm"},
	{7, BXPM_PATH"metal_wall.bxpm"},
	{8, BXPM_PATH"terminal.bxpm"},
	{9, BXPM_PATH"console.bxpm"},
	{10, BXPM_PATH"green_wall.bxpm"},
	{11, BXPM_PATH"radar.bxpm"},
	{12, BXPM_PATH"compwall.bxpm"},
	{13, BXPM_PATH"door.bxpm"},
	{14, BXPM_PATH"fiber_wall.bxpm"},
	{15, BXPM_PATH"rock.bxpm"},
	{16, BXPM_PATH"steel_tile1.bxpm"},
	{17, BXPM_PATH"steel_tile2.bxpm"},
	{18, BXPM_PATH"steel_tlight.bxpm"},
	{19, BXPM_PATH"wires.bxpm"},
	{20, BXPM_PATH"clock.bxpm"}
};

# define SKYBOX_TEXTURE_AMOUNT	18
static const t_id_and_path	g_skybox_textures[SKYBOX_TEXTURE_AMOUNT] =
{
	{0, BXPM_PATH"space-3.bxpm"},
	{1, BXPM_PATH"space-0.bxpm"},
	{2, BXPM_PATH"space-1.bxpm"},
	{3, BXPM_PATH"space-2.bxpm"},
	{4, BXPM_PATH"space-4.bxpm"},
	{5, BXPM_PATH"space-5.bxpm"},
	{6, BXPM_PATH"land-4.bxpm"},
	{7, BXPM_PATH"land-1.bxpm"},
	{8, BXPM_PATH"land-2.bxpm"},
	{9, BXPM_PATH"land-3.bxpm"},
	{10, BXPM_PATH"land-0.bxpm"},
	{11, BXPM_PATH"land-5.bxpm"},
	{12, BXPM_PATH"cosmos-4.bxpm"},
	{13, BXPM_PATH"cosmos-1.bxpm"},
	{14, BXPM_PATH"cosmos-2.bxpm"},
	{15, BXPM_PATH"cosmos-3.bxpm"},
	{16, BXPM_PATH"cosmos-0.bxpm"},
	{17, BXPM_PATH"cosmos-5.bxpm"}
};

# define ICON_TEXTURE_AMOUNT	5
static const t_id_and_path	g_icon_textures[ICON_TEXTURE_AMOUNT] =
{
	{0, BXPM_PATH"health_heart.bxpm"},
	{1, BXPM_PATH"armour_shield.bxpm"},
	{2, BXPM_PATH"ammo_patrons.bxpm"},
	{3, BXPM_PATH"mag_ammo.bxpm"},
	{4, BXPM_PATH"cash_dosh.bxpm"}
};

# define ENTITY_TEXTURE_AMOUNT	5
static const t_id_and_path	g_entity_textures[ENTITY_TEXTURE_AMOUNT] =
{
	{0, BXPM_PATH"alfred.bxpm"},
	{1, BXPM_PATH"spooky.bxpm"},
	{2, BXPM_PATH"rift.bxpm"},
	{3, BXPM_PATH"objects.bxpm"},
	{4, BXPM_PATH"ghost.bxpm"}
};

static const char			*g_weapon_data[WEAPON_AMOUNT] =
{
	"SHOTGUN",
	"GLOCK",
	"KAR98",
	"LAUNCHER",
	"MINIGUN"
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

# define LAUNCHER_TEXTURE_AMOUNT	14
static const t_id_and_path	g_launcher_textures[LAUNCHER_TEXTURE_AMOUNT] =
{
	{0, BXPM_PATH"launcher-0.bxpm"},
	{1, BXPM_PATH"launcher-1.bxpm"},
	{2, BXPM_PATH"launcher-2.bxpm"},
	{3, BXPM_PATH"launcher-3.bxpm"},
	{4, BXPM_PATH"launcher-4.bxpm"},
	{5, BXPM_PATH"launcher-5.bxpm"},
	{6, BXPM_PATH"launcher-6.bxpm"},
	{7, BXPM_PATH"launcher-7.bxpm"},
	{8, BXPM_PATH"launcher-8.bxpm"},
	{9, BXPM_PATH"launcher-9.bxpm"},
	{10, BXPM_PATH"launcher-10.bxpm"},
	{11, BXPM_PATH"launcher-11.bxpm"},
	{12, BXPM_PATH"launcher-12.bxpm"},
	{13, BXPM_PATH"launcher-13.bxpm"}
};

typedef struct s_entity_data
{
	float			scale;
	float			speed;
	int				health;
	int				height;
	int				pickup;
	int				hitbox_radius;
	int				flight;
	int				damage;
	int				type;
	int				move;
	int				view_distance;
	int				detection_radius;
	int				attack_range;
	int				frame_rate[4];
	int				tc[4];
	char			*path;
	char			*name;
}					t_entity_data;

static const t_entity_data	g_entity_data[ENTITY_AMOUNT] =
{
	{
		.name = "Alfred",
		.pickup = FALSE,
		.type = KAMIKAZE,
		.move = TRUE,
		.flight = TRUE,
		.scale = 15,
		.speed = 20,
		.health = 1,
		.damage = 100,
		.height = 2,
		.attack_range = 7,
		.hitbox_radius = 5,
		.view_distance = 200,
		.detection_radius = 40,
		.frame_rate[IDLE] = 20,
		.frame_rate[MOVE] = 40,
		.frame_rate[ATTACK] = 60,
		.frame_rate[DEATH] = 60,
		.path = BXPM_PATH"alfred.bxpm",
		.tc = {0, 0, 43, 47}
	},
	{
		.name = "Spooky",
		.pickup = FALSE,
		.health = 1,
		.damage = 30,
		.type = RANGE,
		.scale = 25,
		.height = 7,
		.hitbox_radius = 5,
		.speed = 10,
		.move = TRUE,
		.view_distance = 200,
		.detection_radius = 40,
		.attack_range = 50,
		.flight = FALSE,
		.frame_rate[IDLE] = 20,
		.frame_rate[MOVE] = 60,
		.frame_rate[ATTACK] = 180,
		.frame_rate[DEATH] = 120,
		.path = BXPM_PATH"spooky.bxpm",
		.tc = {25, 193, 114, 184}
	},
	{
		.name = "Ghost",
		.pickup = FALSE,
		.health = 1,
		.damage = 1,
		.type = MELEE,
		.scale = 18,
		.height = 7,
		.hitbox_radius = 5,
		.speed = 20,
		.move = TRUE,
		.view_distance = 200,
		.detection_radius = 40,
		.attack_range = 20,
		.flight = FALSE,
		.frame_rate[IDLE] = 20,
		.frame_rate[MOVE] = 60,
		.frame_rate[ATTACK] = 70,
		.frame_rate[DEATH] = 40,
		.path = BXPM_PATH"ghost.bxpm",
		.tc = {10, 0, 132, 150}
	},
	{
		.name = "Rift",
		.pickup = FALSE,
		.health = 1,
		.damage = 200,
		.type = INANIMATE,
		.scale = 30,
		.height = 9,
		.hitbox_radius = 5,
		.speed = 0,
		.move = FALSE,
		.view_distance = 0,
		.detection_radius = 0,
		.attack_range = 0,
		.flight = FALSE,
		.frame_rate[IDLE] = 20,
		.frame_rate[MOVE] = 80,
		.frame_rate[ATTACK] = 0,
		.frame_rate[DEATH] = 0,
		.path = BXPM_PATH"rift.bxpm",
		.tc = {0, 0, 174, 315}
	},
	{
		.name = "Barrel",
		.pickup = FALSE,
		.health = 20,
		.damage = 0,
		.type = INANIMATE,
		.scale = 9,
		.height = 0,
		.hitbox_radius = 5,
		.speed = 0,
		.move = FALSE,
		.view_distance = 0,
		.detection_radius = 0,
		.attack_range = 0,
		.flight = FALSE,
		.frame_rate[IDLE] = 60,
		.frame_rate[MOVE] = 0,
		.frame_rate[ATTACK] = 0,
		.frame_rate[DEATH] = 40,
		.path = BXPM_PATH"objects.bxpm",
		.tc = {174, 182, 35, 51}
	},
	{
		.name = "Lamp",
		.pickup = FALSE,
		.health = MAX_INT,
		.damage = 0,
		.type = INANIMATE,
		.scale = 10,
		.height = 0,
		.hitbox_radius = 5,
		.speed = 0,
		.move = FALSE,
		.view_distance = 0,
		.detection_radius = 0,
		.attack_range = 0,
		.flight = FALSE,
		.frame_rate[IDLE] = 30,
		.frame_rate[MOVE] = 0,
		.frame_rate[ATTACK] = 0,
		.frame_rate[DEATH] = 0,
		.path = BXPM_PATH"objects.bxpm",
		.tc = {174, 7, 23, 84}
	},
	{
		.name = "Torch",
		.pickup = FALSE,
		.health = MAX_INT,
		.damage = 0,
		.type = INANIMATE,
		.scale = 10,
		.height = 0,
		.hitbox_radius = 5,
		.speed = 0,
		.move = FALSE,
		.view_distance = 0,
		.detection_radius = 0,
		.attack_range = 0,
		.flight = FALSE,
		.frame_rate[IDLE] = 90,
		.frame_rate[MOVE] = 0,
		.frame_rate[ATTACK] = 0,
		.frame_rate[DEATH] = 0,
		.path = BXPM_PATH"objects.bxpm",
		.tc = {371, 209, 10, 47}
	},
	{
		.name = "MeatHook",
		.pickup = FALSE,
		.health = MAX_INT,
		.damage = 0,
		.type = INANIMATE,
		.scale = 10,
		.height = 0,
		.hitbox_radius = 5,
		.speed = 0,
		.move = FALSE,
		.view_distance = 0,
		.detection_radius = 0,
		.attack_range = 0,
		.flight = FALSE,
		.frame_rate[IDLE] = 10,
		.frame_rate[MOVE] = 0,
		.frame_rate[ATTACK] = 0,
		.frame_rate[DEATH] = 0,
		.path = BXPM_PATH"objects.bxpm",
		.tc = {543, 5, 36, 91}
	},
	{
		.name = "CeilingLamp",
		.pickup = FALSE,
		.type = INANIMATE,
		.move = FALSE,
		.flight = FALSE,
		.health = MAX_INT,
		.scale = 10,
		.speed = 0,
		.damage = 0,
		.height = 2,
		.attack_range = 0,
		.hitbox_radius = 2,
		.view_distance = 0,
		.detection_radius = 0,
		.frame_rate[IDLE] = 10,
		.frame_rate[MOVE] = 0,
		.frame_rate[ATTACK] = 0,
		.frame_rate[DEATH] = 0,
		.path = BXPM_PATH"objects.bxpm",
		.tc = {88, 70, 24, 56}
	},
	{
		.name = "Gargoyle",
		.pickup = FALSE,
		.type = INANIMATE,
		.move = FALSE,
		.flight = FALSE,
		.health = MAX_INT,
		.scale = 10,
		.speed = 0,
		.damage = 0,
		.height = 2,
		.attack_range = 0,
		.hitbox_radius = 2,
		.view_distance = 0,
		.detection_radius = 0,
		.frame_rate[IDLE] = 10,
		.frame_rate[MOVE] = 0,
		.frame_rate[ATTACK] = 0,
		.frame_rate[DEATH] = 0,
		.path = BXPM_PATH"objects.bxpm",
		.tc = {229, 97, 58, 75}
	},
	{
		.name = "MedKit",
		.pickup = TRUE,
		.type = INANIMATE,
		.move = FALSE,
		.flight = FALSE,
		.health = 100,
		.scale = 10,
		.speed = 0,
		.damage = 0,
		.height = 2,
		.attack_range = 0,
		.hitbox_radius = 2,
		.view_distance = 0,
		.detection_radius = 0,
		.frame_rate[IDLE] = 10,
		.frame_rate[MOVE] = 0,
		.frame_rate[ATTACK] = 0,
		.frame_rate[DEATH] = 0,
		.path = BXPM_PATH"objects.bxpm",
		.tc = {178, 242, 28, 18}
	}
};

#endif
