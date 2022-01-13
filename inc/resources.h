/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resources.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/11 10:31:43 by nneronin          #+#    #+#             */
/*   Updated: 2022/01/13 16:25:25 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESOURCES_H
# define RESOURCES_H

//# include "path.h"
# include "enum.h"

/* 16 Bytes */
typedef struct s_id_and_path
{
	int				id;
	char			*path;
}				t_id_and_path;

static const t_id_and_path	g_sounds[WAV_AMOUNT] =
{
	{WAV_ELEVATOR_MUSIC, "resources/WAV/BuyMenu.wav"},
	{WAV_MAIN_THEME, "resources/WAV/AtDoomsGate.wav"},
	{WAV_INTRO, "resources/WAV/Intro.wav"},
	{WAV_SHOTGUN, "resources/WAV/Shotgun.wav"},
	{WAV_SCREEN_SHOT, "resources/WAV/ScreenShot.wav"},
	{WAV_FOOT_STEPS, "resources/WAV/FootSteps.wav"},
	{WAV_JUMP, "resources/WAV/Jump.wav"},
	{WAV_GUN, "resources/WAV/Pistol.wav"},
	{WAV_DOSH, "resources/WAV/Dosh.wav"},
	{WAV_EMPTY_CLIP, "resources/WAV/EmptyClip.wav"},
	{WAV_BIP, "resources/WAV/Bip.wav"},
	{WAV_ORB, "resources/WAV/Projectile.wav"},
	{WAV_ROUND_END, "resources/WAV/EndRound.wav"},
	{WAV_NEW_ROUND, "resources/WAV/NewRound.wav"},
	{WAV_MONSTER_HIT, "resources/WAV/EntityHit.wav"},
	{WAV_PLAYER_HIT, "resources/WAV/PlayerHit.wav"},
	{WAV_ENTITY_DEATH, "resources/WAV/EntityDeath.wav"},
	{WAV_PLAYER_DEATH, "resources/WAV/PlayerDeath.wav"}
};

# define MAP_TEXTURE_AMOUNT	34
static const t_id_and_path	g_map_textures[MAP_TEXTURE_AMOUNT] =
{
	{0, "resources/BXPM/BulletHole.bxpm"},
	{1, "resources/BXPM/SciFi-8.bxpm"},
	{2, "resources/BXPM/FloorTiles.bxpm"},
	{3, "resources/BXPM/SteelBars.bxpm"},
	{4, "resources/BXPM/SteelDoor.bxpm"},
	{5, "resources/BXPM/SciFi-0.bxpm"},
	{6, "resources/BXPM/Lava.bxpm"},
	{7, "resources/BXPM/SciFi-1.bxpm"},
	{8, "resources/BXPM/SciFi-2.bxpm"},
	{9, "resources/BXPM/SciFi-3.bxpm"},
	{10, "resources/BXPM/SciFi-4.bxpm"},
	{11, "resources/BXPM/SciFi-5.bxpm"},
	{12, "resources/BXPM/SciFi-6.bxpm"},
	{13, "resources/BXPM/SciFi-7.bxpm"},
	{14, "resources/BXPM/FiberWall.bxpm"},
	{15, "resources/BXPM/SciFi-9.bxpm"},
	{16, "resources/BXPM/SciFi-13.bxpm"},
	{17, "resources/BXPM/SciFi-11.bxpm"},
	{18, "resources/BXPM/SciFi-12.bxpm"},
	{19, "resources/BXPM/SciFi-10.bxpm"},
	{20, "resources/BXPM/SteelTile.bxpm"},
	{21, "resources/BXPM/HandPrint.bxpm"},
	{22, "resources/BXPM/Radar.bxpm"},
	{23, "resources/BXPM/WarPoster.bxpm"},
	{24, "resources/BXPM/Wires.bxpm"},
	{25, "resources/BXPM/AnimatedButton.bxpm"},
	{26, "resources/BXPM/AnimatedClaw.bxpm"},
	{27, "resources/BXPM/AnimatedCog.bxpm"},
	{28, "resources/BXPM/AnimatedTerminal.bxpm"},
	{29, "resources/BXPM/AnimetedVent.bxpm"},
	{30, "resources/BXPM/DoomPoster.bxpm"},
	{31, "resources/BXPM/TargetDummy.bxpm"},
	{32, "resources/BXPM/Crate.bxpm"},
	{33, "resources/BXPM/Clock.bxpm"}
};

# define SKYBOX_TEXTURE_AMOUNT	18
static const t_id_and_path	g_skybox_textures[SKYBOX_TEXTURE_AMOUNT] =
{
	{0, "resources/BXPM/Space-3.bxpm"},
	{1, "resources/BXPM/Space-0.bxpm"},
	{2, "resources/BXPM/Space-1.bxpm"},
	{3, "resources/BXPM/Space-2.bxpm"},
	{4, "resources/BXPM/Space-4.bxpm"},
	{5, "resources/BXPM/Space-5.bxpm"},
	{6, "resources/BXPM/Land-4.bxpm"},
	{7, "resources/BXPM/Land-1.bxpm"},
	{8, "resources/BXPM/Land-2.bxpm"},
	{9, "resources/BXPM/Land-3.bxpm"},
	{10, "resources/BXPM/Land-0.bxpm"},
	{11, "resources/BXPM/Land-5.bxpm"},
	{12, "resources/BXPM/Duke-3.bxpm"},
	{13, "resources/BXPM/Duke-1.bxpm"},
	{14, "resources/BXPM/Duke-2.bxpm"},
	{15, "resources/BXPM/Duke-1.bxpm"},
	{16, "resources/BXPM/Duke-5.bxpm"},
	{17, "resources/BXPM/Duke-0.bxpm"}
};

# define ICON_TEXTURE_AMOUNT	5
static const t_id_and_path	g_icon_textures[ICON_TEXTURE_AMOUNT] =
{
	{0, "resources/BXPM/health_heart.bxpm"},
	{1, "resources/BXPM/armour_shield.bxpm"},
	{2, "resources/BXPM/ammo_patrons.bxpm"},
	{3, "resources/BXPM/mag_ammo.bxpm"},
	{4, "resources/BXPM/cash_dosh.bxpm"}
};

# define ENTITY_TEXTURE_AMOUNT	5
static const t_id_and_path	g_entity_textures[ENTITY_TEXTURE_AMOUNT] =
{
	{0, "resources/BXPM/EntityAlfred.bxpm"},
	{1, "resources/BXPM/EntitySpooky.bxpm"},
	{2, "resources/BXPM/EntityRift.bxpm"},
	{3, "resources/BXPM/EntityObjects.bxpm"},
	{4, "resources/BXPM/EntityGhost.bxpm"}
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
	{0, "resources/BXPM/shotgun-0.bxpm"},
	{1, "resources/BXPM/shotgun-1.bxpm"},
	{2, "resources/BXPM/shotgun-2.bxpm"},
	{3, "resources/BXPM/shotgun-3.bxpm"},
	{4, "resources/BXPM/shotgun-4.bxpm"},
	{5, "resources/BXPM/shotgun-5.bxpm"},
	{6, "resources/BXPM/shotgun-6.bxpm"},
	{7, "resources/BXPM/shotgun-7.bxpm"},
	{8, "resources/BXPM/shotgun-8.bxpm"},
	{9, "resources/BXPM/shotgun-9.bxpm"},
	{10, "resources/BXPM/shotgun-10.bxpm"},
	{11, "resources/BXPM/shotgun-11.bxpm"},
	{12, "resources/BXPM/shotgun-12.bxpm"},
	{13, "resources/BXPM/shotgun-13.bxpm"}
};

# define GLOCK_TEXTURE_AMOUNT	6
static const t_id_and_path	g_glock_textures[GLOCK_TEXTURE_AMOUNT] =
{
	{0, "resources/BXPM/glock-0.bxpm"},
	{1, "resources/BXPM/glock-1.bxpm"},
	{2, "resources/BXPM/glock-2.bxpm"},
	{3, "resources/BXPM/glock-3.bxpm"},
	{4, "resources/BXPM/glock-4.bxpm"},
	{5, "resources/BXPM/glock-5.bxpm"}
};

# define MINIGUN_TEXTURE_AMOUNT	6
static const t_id_and_path	g_minigun_textures[MINIGUN_TEXTURE_AMOUNT] =
{
	{0, "resources/BXPM/minigun-0.bxpm"},
	{1, "resources/BXPM/minigun-1.bxpm"},
	{2, "resources/BXPM/minigun-2.bxpm"},
	{3, "resources/BXPM/minigun-3.bxpm"},
	{4, "resources/BXPM/minigun-4.bxpm"},
	{5, "resources/BXPM/minigun-5.bxpm"}
};

# define KAR_TEXTURE_AMOUNT	38
static const t_id_and_path	g_kar_textures[KAR_TEXTURE_AMOUNT] =
{
	{0, "resources/BXPM/kar-0.bxpm"},
	{1, "resources/BXPM/kar-1.bxpm"},
	{2, "resources/BXPM/kar-2.bxpm"},
	{3, "resources/BXPM/kar-3.bxpm"},
	{4, "resources/BXPM/kar-4.bxpm"},
	{5, "resources/BXPM/kar-5.bxpm"},
	{6, "resources/BXPM/kar-6.bxpm"},
	{7, "resources/BXPM/kar-7.bxpm"},
	{8, "resources/BXPM/kar-8.bxpm"},
	{9, "resources/BXPM/kar-9.bxpm"},
	{10, "resources/BXPM/kar-10.bxpm"},
	{11, "resources/BXPM/kar-11.bxpm"},
	{12, "resources/BXPM/kar-12.bxpm"},
	{13, "resources/BXPM/kar-13.bxpm"},
	{14, "resources/BXPM/kar-14.bxpm"},
	{15, "resources/BXPM/kar-15.bxpm"},
	{16, "resources/BXPM/kar-16.bxpm"},
	{17, "resources/BXPM/kar-17.bxpm"},
	{18, "resources/BXPM/kar-18.bxpm"},
	{19, "resources/BXPM/kar-19.bxpm"},
	{20, "resources/BXPM/kar-20.bxpm"},
	{21, "resources/BXPM/kar-21.bxpm"},
	{22, "resources/BXPM/kar-22.bxpm"},
	{23, "resources/BXPM/kar-23.bxpm"},
	{24, "resources/BXPM/kar-24.bxpm"},
	{25, "resources/BXPM/kar-25.bxpm"},
	{26, "resources/BXPM/kar-26.bxpm"},
	{27, "resources/BXPM/kar-27.bxpm"},
	{28, "resources/BXPM/kar-28.bxpm"},
	{29, "resources/BXPM/kar-29.bxpm"},
	{30, "resources/BXPM/kar-30.bxpm"},
	{31, "resources/BXPM/kar-31.bxpm"},
	{32, "resources/BXPM/kar-32.bxpm"},
	{33, "resources/BXPM/kar-33.bxpm"},
	{34, "resources/BXPM/kar-34.bxpm"},
	{35, "resources/BXPM/kar-35.bxpm"},
	{36, "resources/BXPM/kar-36.bxpm"},
	{37, "resources/BXPM/kar-37.bxpm"}
};

# define LAUNCHER_TEXTURE_AMOUNT	14
static const t_id_and_path	g_launcher_textures[LAUNCHER_TEXTURE_AMOUNT] =
{
	{0, "resources/BXPM/launcher-0.bxpm"},
	{1, "resources/BXPM/launcher-1.bxpm"},
	{2, "resources/BXPM/launcher-2.bxpm"},
	{3, "resources/BXPM/launcher-3.bxpm"},
	{4, "resources/BXPM/launcher-4.bxpm"},
	{5, "resources/BXPM/launcher-5.bxpm"},
	{6, "resources/BXPM/launcher-6.bxpm"},
	{7, "resources/BXPM/launcher-7.bxpm"},
	{8, "resources/BXPM/launcher-8.bxpm"},
	{9, "resources/BXPM/launcher-9.bxpm"},
	{10, "resources/BXPM/launcher-10.bxpm"},
	{11, "resources/BXPM/launcher-11.bxpm"},
	{12, "resources/BXPM/launcher-12.bxpm"},
	{13, "resources/BXPM/launcher-13.bxpm"}
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
		.path = "resources/BXPM/EntityAlfred.bxpm",
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
		.detection_radius = 70,
		.attack_range = 70,
		.flight = FALSE,
		.frame_rate[IDLE] = 20,
		.frame_rate[MOVE] = 60,
		.frame_rate[ATTACK] = 180,
		.frame_rate[DEATH] = 120,
		.path = "resources/BXPM/EntitySpooky.bxpm",
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
		.path = "resources/BXPM/EntityGhost.bxpm",
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
		.path = "resources/BXPM/EntityRift.bxpm",
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
		.path = "resources/BXPM/EntityObjects.bxpm",
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
		.path = "resources/BXPM/EntityObjects.bxpm",
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
		.path = "resources/BXPM/EntityObjects.bxpm",
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
		.path = "resources/BXPM/EntityObjects.bxpm",
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
		.path = "resources/BXPM/EntityObjects.bxpm",
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
		.path = "resources/BXPM/EntityObjects.bxpm",
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
		.path = "resources/BXPM/EntityObjects.bxpm",
		.tc = {178, 242, 28, 18}
	}
};

static const char			*g_event_type[EVENT_TYPE_AMOUNT] =
{
	"None",
	"Ceiling",
	"Floor",
	"Store",
	"Hazard",
	"Audio",
	"Spawn",
	"Light",
	"Win"
};

static const char			*g_sprite_type[SPRITE_TYPE_AMOUNT] =
{
	"STATIC",
	"LOOP",
	"ACTION"
};

static const char			*g_event_action[EVENT_ACTION_AMOUNT] =
{
	"NONE",
	"SHOOT",
	"CLICK",
	"SECTOR"
};

#endif
