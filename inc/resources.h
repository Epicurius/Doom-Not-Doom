/*
 * https://github.com/Epicurius/Doom-Not-Doom
 * 
 * Created: 2021/07/11 10:31:43 nneronin
 * Updated: 2022/01/20 14:21:13 Niklas Neronin
 */

#ifndef RESOURCES_H
# define RESOURCES_H

# define BXPM_PATH	"resources/BXPM/"
# define BXPM_LEN	15
# define WAV_PATH	"resources/WAV/"
# define WAV_LEN	14

# include "enum.h"

/*	All bxpm and wav paths 2170 bytes total. */

static const char	*g_sounds[WAV_AMOUNT] =
{
	"AtDoomsGate.wav",
	"BuyMenu.wav",
	"Intro.wav",
	"ScreenShot.wav",
	"FootSteps.wav",
	"Jump.wav",
	"Dosh.wav",
	"Bip.wav",
	"EmptyClip.wav",
	"Pistol.wav",
	"Shotgun.wav",
	"Projectile.wav",
	"NewRound.wav",
	"EndRound.wav",
	"PlayerHit.wav",
	"EntityHit.wav",
	"PlayerDeath.wav",
	"EntityDeath.wav"
};

# define MAP_TEXTURE_AMOUNT	34
static const char	*g_map_textures[MAP_TEXTURE_AMOUNT] =
{
	"BulletHole.bxpm",
	"SciFi-8.bxpm",
	"FloorTiles.bxpm",
	"SteelBars.bxpm",
	"SteelDoor.bxpm",
	"SciFi-0.bxpm",
	"Lava.bxpm",
	"SciFi-1.bxpm",
	"SciFi-2.bxpm",
	"SciFi-3.bxpm",
	"SciFi-4.bxpm",
	"SciFi-5.bxpm",
	"SciFi-6.bxpm",
	"SciFi-7.bxpm",
	"FiberWall.bxpm",
	"SciFi-9.bxpm",
	"SciFi-13.bxpm",
	"SciFi-11.bxpm",
	"SciFi-12.bxpm",
	"SciFi-10.bxpm",
	"SteelTile.bxpm",
	"HandPrint.bxpm",
	"Radar.bxpm",
	"WarPoster.bxpm",
	"Wires.bxpm",
	"AnimatedButton.bxpm",
	"AnimatedClaw.bxpm",
	"AnimatedCog.bxpm",
	"AnimatedTerminal.bxpm",
	"AnimetedVent.bxpm",
	"DoomPoster.bxpm",
	"TargetDummy.bxpm",
	"Crate.bxpm",
	"Clock.bxpm"
};

# define SKYBOX_TEXTURE_AMOUNT	18
static const char	*g_skybox_textures[SKYBOX_TEXTURE_AMOUNT] =
{
	"Space-3.bxpm",
	"Space-0.bxpm",
	"Space-1.bxpm",
	"Space-2.bxpm",
	"Space-4.bxpm",
	"Space-5.bxpm",
	"Land-4.bxpm",
	"Land-1.bxpm",
	"Land-2.bxpm",
	"Land-3.bxpm",
	"Land-0.bxpm",
	"Land-5.bxpm",
	"Duke-3.bxpm",
	"Duke-1.bxpm",
	"Duke-2.bxpm",
	"Duke-1.bxpm",
	"Duke-5.bxpm",
	"Duke-0.bxpm"
};

# define ICON_TEXTURE_AMOUNT	5
static const char	*g_icon_textures[ICON_TEXTURE_AMOUNT] =
{
	"health_heart.bxpm",
	"armour_shield.bxpm",
	"ammo_patrons.bxpm",
	"mag_ammo.bxpm",
	"cash_dosh.bxpm"
};

# define ENTITY_TEXTURE_AMOUNT	5
static const char	*g_entity_textures[ENTITY_TEXTURE_AMOUNT] =
{
	"EntityAlfred.bxpm",
	"EntitySpooky.bxpm",
	"EntityRift.bxpm",
	"EntityObjects.bxpm",
	"EntityGhost.bxpm"
};

# define SHOTGUN_TEXTURE_AMOUNT	14
static const char	*g_shotgun_textures[SHOTGUN_TEXTURE_AMOUNT] =
{
	"shotgun-0.bxpm",
	"shotgun-1.bxpm",
	"shotgun-2.bxpm",
	"shotgun-3.bxpm",
	"shotgun-4.bxpm",
	"shotgun-5.bxpm",
	"shotgun-6.bxpm",
	"shotgun-7.bxpm",
	"shotgun-8.bxpm",
	"shotgun-9.bxpm",
	"shotgun-10.bxpm",
	"shotgun-11.bxpm",
	"shotgun-12.bxpm",
	"shotgun-13.bxpm"
};

# define GLOCK_TEXTURE_AMOUNT	6
static const char	*g_glock_textures[GLOCK_TEXTURE_AMOUNT] =
{
	"glock-0.bxpm",
	"glock-1.bxpm",
	"glock-2.bxpm",
	"glock-3.bxpm",
	"glock-4.bxpm",
	"glock-5.bxpm"
};

# define MINIGUN_TEXTURE_AMOUNT	6
static const char	*g_minigun_textures[MINIGUN_TEXTURE_AMOUNT] =
{
	"minigun-0.bxpm",
	"minigun-1.bxpm",
	"minigun-2.bxpm",
	"minigun-3.bxpm",
	"minigun-4.bxpm",
	"minigun-5.bxpm"
};

# define KAR_TEXTURE_AMOUNT	38
static const char	*g_kar_textures[KAR_TEXTURE_AMOUNT] =
{
	"kar-0.bxpm",
	"kar-1.bxpm",
	"kar-2.bxpm",
	"kar-3.bxpm",
	"kar-4.bxpm",
	"kar-5.bxpm",
	"kar-6.bxpm",
	"kar-7.bxpm",
	"kar-8.bxpm",
	"kar-9.bxpm",
	"kar-10.bxpm",
	"kar-11.bxpm",
	"kar-12.bxpm",
	"kar-13.bxpm",
	"kar-14.bxpm",
	"kar-15.bxpm",
	"kar-16.bxpm",
	"kar-17.bxpm",
	"kar-18.bxpm",
	"kar-19.bxpm",
	"kar-20.bxpm",
	"kar-21.bxpm",
	"kar-22.bxpm",
	"kar-23.bxpm",
	"kar-24.bxpm",
	"kar-25.bxpm",
	"kar-26.bxpm",
	"kar-27.bxpm",
	"kar-28.bxpm",
	"kar-29.bxpm",
	"kar-30.bxpm",
	"kar-31.bxpm",
	"kar-32.bxpm",
	"kar-33.bxpm",
	"kar-34.bxpm",
	"kar-35.bxpm",
	"kar-36.bxpm",
	"kar-37.bxpm"
};

# define LAUNCHER_TEXTURE_AMOUNT	14
static const char	*g_launcher_textures[LAUNCHER_TEXTURE_AMOUNT] =
{
	"launcher-0.bxpm",
	"launcher-1.bxpm",
	"launcher-2.bxpm",
	"launcher-3.bxpm",
	"launcher-4.bxpm",
	"launcher-5.bxpm",
	"launcher-6.bxpm",
	"launcher-7.bxpm",
	"launcher-8.bxpm",
	"launcher-9.bxpm",
	"launcher-10.bxpm",
	"launcher-11.bxpm",
	"launcher-12.bxpm",
	"launcher-13.bxpm"
};

typedef struct s_entity_data
{
	char			*name;
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
	unsigned char	frame_rate[4];
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
		.frame_rate[DEATH] = 60
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
		.frame_rate[DEATH] = 120
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
		.frame_rate[DEATH] = 40
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
		.frame_rate[DEATH] = 0
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
		.frame_rate[DEATH] = 40
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
		.frame_rate[DEATH] = 0
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
		.frame_rate[DEATH] = 0
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
		.frame_rate[DEATH] = 0
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
		.frame_rate[DEATH] = 0
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
		.frame_rate[DEATH] = 0
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
		.frame_rate[DEATH] = 0
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
