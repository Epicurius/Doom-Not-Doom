/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Niklas Neronin <niklas.neronin@gmail.com>
 */

#ifndef DOOM_H
# define DOOM_H

# define SDL_MAIN_HANDLED
# include "liblg.h"
# include "SDL2/SDL.h"
# include "SDL2/SDL_ttf.h"
# include "SDL2/SDL_mixer.h"
# include "libft.h"
# include "libpf.h"
# include "tpool.h"
# include "bxpm.h"
# include "macros.h"
# include "libm.h"
# include "enum.h"
# include "time.h"
# include "resources.h"
# include <math.h>
# include <fcntl.h>
# include <limits.h>

typedef struct s_settings
{
	t_point			size;
	t_v2			mouse;
	float			rres;
	int				difficulty;
	int				fov;
	int				debug;
	int				launcher;
}					t_settings;

typedef struct s_plane
{
	int				tx;
	float			height;
	float			ppos;
	float			scale;
}					t_plane;

typedef struct s_fc
{
	float			top;
	float			bot;
}					t_fc;

typedef struct s_vline
{
	int				y1;
	int				y2;
	float			alpha;
	float			clipped_alpha;
	float			divider;
	float			z;
	float			zrange;
	float			z_near_z;
	float			line_height;
	t_fc			start;
	t_fc			height;
	t_fc			max;
	t_fc			curr;
	t_fc			max_n;
	t_fc			curr_n;
	t_v2			texel;
	t_v2			texel_nearz;
	t_v2			texel_range;
	t_fc			stat_y;
}					t_vline;

typedef struct s_projectile
{
	t_v3			start;
	t_v3			where;
	t_v3			velocity;
	float			dist;
	int				sector;
	int				moving;
	int				target;
	int				range;
}					t_projectile;

typedef struct s_weapon_thread
{
	SDL_Surface		*dst;
	t_bxpm			*src;
	int				sx1;
	int				sy1;
	int				sx2;
	int				sy2;
	int				dx1;
	int				dy1;
	int				dx2;
	int				dy2;
}					t_weapon_thread;

typedef struct s_player
{
	t_v3			wishdir;
	t_v3			wishspeed;
	t_v3			where;
	t_v3			velocity;
	int				eyelvl;
	int				sector;
	double			yaw;
	double			pitch;
	double			anglesin;
	double			anglecos;
	float			horizon;
	int				health;
	int				max_hp;
	int				armour;
	int				flight;
	int				action;
	int				equipped;
	int				debug;
	int				store_access;
	int				hitmarker;
	int				damage;
	float			walk_speed;
	float			sprint_speed;
	float			jump_height;
}					t_player;

typedef struct s_wsprite
{
	t_v2			where;
	int				id;
	int				tx;
	int				frame;
	int				time;
	t_rect			src;
	float			scale_w;
	float			scale_h;
	t_v2			tscale;
	int				ready;
	int				trigger;
	int				state;
	int				action;
}					t_wsprite;

typedef struct s_bullet_hole
{
	t_wsprite		num[MAX_BULLET_HOLES];
	int				curr;
	int				total;
}					t_bullet_hole;

typedef struct s_wsprites
{
	t_wsprite		*num;
	int				curr;
	int				total;
}					t_wsprites;

typedef struct s_wall
{
	signed char		wtx;
	signed char		ptx;
	signed char		solid;
	signed char		visible;
	unsigned short	id;
	int				sect;
	int				n;
	t_v3			v1;
	t_v3			v2;
	t_v3			sv1;
	t_v3			sv2;
	t_v3			cv1;
	t_v3			cv2;
	t_v2			text_pix_nb;
	t_v2			clip_scale;
	float			scale_factor;
	float			width;
	float			height;
	float			fov_z1;
	float			fov_z2;
	float			pitch_z1;
	float			pitch_z2;
	float			x1;
	float			x2;
	float			cx1;
	float			cx2;
	t_fc			stat_y1;
	t_fc			stat_y2;
	t_fc			stat_range;
	t_fc			incl_y1;
	t_fc			incl_y2;
	t_fc			incl_range;
	t_fc			incl_ny1;
	t_fc			incl_ny2;
	t_fc			incl_nrange;
	float			xrange;
	float			zrange;
	float			zcomb;
	float			x1z2;
	float			y1z2;
	float			xzrange;
	float			yzrange;
	t_wsprites		wsprite;
	t_bullet_hole	bullet_hole;
}					t_wall;

typedef struct s_sector
{
	int				id;
	int				npoints;
	t_wall			**wall;
	t_plane			floor;
	t_plane			ceiling;
	int				light;
	float			gravity;
	t_v3			center;
	int				ceiling_incl_start;
	float			ceiling_incl_angle;
	int				floor_incl_start;
	float			floor_incl_angle;
	t_v2			top_normal;
	t_v2			bot_normal;
	int				trigger;
	char			visible;
}					t_sector;

typedef struct s_camera
{
	float			near_left;
	float			near_right;
	float			far_left;
	float			far_right;
	float			range;
	float			scale;
}					t_camera;

typedef struct s_entity_render
{
	t_point			start;
	t_point			end;
	t_point			clamp_start;
	t_point			clamp_end;
	float			xrange;
	float			yrange;
	float			z;
}					t_entity_render;

typedef struct s_entity
{
	t_v3			where;
	t_v3			velocity;
	t_v3			dest;
	int				sector;
	int				danger;
	int				state;
	int				frame;
	int				angle;
	int				hp;
	int				type;
	double			yaw;
	int				time;
	t_entity_render	render;
}					t_entity;

typedef struct s_entity_thread
{
	SDL_Surface		*surface;
	t_entity_render	render;
	t_bxpm			*bxpm;
	t_rect			pos;
	int				dmg;
	int				*hp;
	int				*hitmarker;
	int				shooting;
	int				type;
	t_v3			center;
}					t_entity_thread;

typedef struct s_render
{
	SDL_Surface		*surface;
	t_sector		*sectors;
	int				nb_sectors;
	t_wall			*skybox;
	t_bxpm			*mtx;
	t_bxpm			*stx;
	t_camera		*cam;
	t_player		*player;
	int				ytop;
	int				ybot;
	int				x;
	int				xend;
	t_wall			*wall;
	t_plane			*floor;
	t_plane			*ceiling;
	int				light;
	int				s;
	t_bullet_hole	*bullet_hole;
	t_v3			center;
	t_wsprites		*wsprite;
}					t_render;

typedef struct s_map
{
	t_point			pos;
	t_rect			size;
	int				zoom;
}					t_map;

typedef struct s_nb
{
	int				walls;
	int				sectors;
	int				vertices;
	int				processors;
	int				projectiles;
	int				threads;
	int				entities;
	int				rifts;
	int				kills;
	int				events;
}					t_nb;

typedef struct s_time
{
	int				fps;
	int				curr;
	int				prev;
	float			delta;
	SDL_Color		color;
	SDL_Surface		*surf;
	long int		start;
	struct tm		date;
	SDL_Color		clock_fg;
	SDL_Color		clock_bg;
}					t_time;

typedef struct s_frames
{
	t_bxpm			*bxpm;
	t_rect			***pos;
	int				nb[4][2];
}					t_frames;

typedef struct s_game
{
	int				mode;
	int				round;
	int				spawns;
	int				time;
	int				spawn_rate;
	float			cool_down;
}					t_game;

typedef struct s_weapon
{
	int				own;
	int				price;
	int				ammo_price;
	int				damage_price;
	int				firerate_price;
	int				max_ammo_price;
	int				damage;
	int				mag_size;
	int				cur_ammo;
	int				mag_ammo;
	int				max_ammo;
	int				ammo_increase;
	int				damage_increase;
	int				firerate_increase;
	int				max_ammo_increase;
	int				x_offset;
	int				frame_rate;
	int				sound;
	int				time;
	int				frame;
	int				fire_frames;
	int				reload_frames;
	t_bxpm			*bxpm;
}					t_weapon;

typedef struct s_inv
{
	int				*hp;
	int				*armour;
	int				dosh;
	int				max_armour;
	int				max_armour_price;
	int				speed_price;
	int				jump_price;
	int				armour_price;
	t_weapon		*weapon;
	float			*speed;
	float			*jump;
}					t_inv;

typedef struct s_fonts
{
	TTF_Font		*amaz;
	TTF_Font		*digital;
}					t_fonts;

typedef struct s_event
{
	t_wsprite		*wsprite;
	t_sector		*sector;
	int				event_sector;
	int				trigger_sector;
	int				trigger;
	int				type;
	int				action;
	float			min;
	float			max;
	float			speed;
	int				time;
	Mix_Chunk		*audio;
	int				dir;
	int				entity;
	t_v3			pos;
	int				yaw;
	int				light;
	char			*path;
}					t_event;

typedef struct s_motion
{
	int				flight;
	int				sector;
	float			height;
	float			step;
	t_v3			where;
	t_v3			velocity;
	t_v3			dest;
}					t_motion;

typedef struct s_doom
{
	t_settings		settings;
	char			root[PATH_MAX];
	int				rlen;
	SDL_Window		*win;
	SDL_Surface		*surface;
	SDL_Texture		*texture;
	SDL_Renderer	*renderer;
	float			*zbuffer;
	int				quit;
	char			*sectbool;
	float			map_scale;
	t_fonts			font;
	t_render		*render;
	t_v3			c;
	t_game			game;
	t_inv			inv;
	t_nb			nb;
	t_tpool			tpool;
	t_time			time;
	t_map			map;
	t_v3			*vert;
	t_wall			*walls;
	t_wall			skybox[4];
	t_sector		*sectors;
	t_list			*entity;
	t_list			*rifts;
	t_list			*orb;
	t_camera		cam;
	t_player		player;
	t_bxpm			mtx[MAP_TEXTURE_AMOUNT];
	t_bxpm			stx[SKYBOX_TEXTURE_AMOUNT];
	t_bxpm			itx[ICON_TEXTURE_AMOUNT];
	t_bxpm			etx[ENTITY_TEXTURE_AMOUNT];
	Mix_Chunk		*sound[WAV_AMOUNT];
	t_weapon		weapon[WEAPON_AMOUNT];
	t_frames		eframes[ENTITY_AMOUNT];
	t_event			*events;
	char			keys[517];
}					t_doom;

/* File: srcs/ai_attack.c */
void				ai_attack(t_doom *doom, t_entity *entity);
/* File: srcs/ai_movement.c */
int					ai_track_player(t_doom *doom, t_entity *entity);
int					ai_rand_move(t_doom *doom, t_entity *entity, int chance,
						int angle);
int					ai_rand_dodge(t_doom *doom, t_entity *entity, int chance,
						int angle);
void				ai_collision(t_doom *doom, t_entity *entity);
/* File: srcs/animate_wsprite.c */
int					animate_wsprite(t_doom *doom, t_wsprite *wsprite);
/* File: srcs/args.c */
void				args(int ac, char **av, t_settings *init);
/* File: srcs/blit_bxpm.c */
void				blit_bxpm2(t_weapon_thread *thread, SDL_Surface *surface,
						t_bxpm *bxpm);
void				blit_bxpm(SDL_Surface *surface, t_bxpm *bxpm, int sx,
						int sy);
/* File: srcs/camera.c */
void				init_camera(t_doom *doom);
void				update_camera(t_doom *doom);
/* File: srcs/clock.c */
void				get_elapsed_time_str(t_doom *doom, char *str);
void				init_clock(t_doom *doom, t_bxpm *bxpm);
int					clock_wsprite(t_doom *doom, t_wall *wall, int x);
/* File: srcs/color_and_brightness.c */
SDL_Color			hex_to_sdl_color(int hex);
Uint32				brightness(Uint32 src, int light);
int					blend_alpha(unsigned int src, unsigned int dest,
						uint8_t alpha);
void				sector_shading(t_doom *doom, int s, int w);
void				combine_argb(unsigned char *src, unsigned char *dest);
unsigned int		blend_colors(unsigned int src, unsigned int dest);
/* File: srcs/compute_vline.c */
void				compute_vline_data(t_render *render, t_wall *wall,
						t_vline *vline);
void				compute_vline_texels(t_render *render, t_wall *wall,
						t_vline *vline);
/* File: srcs/crosshair_position.c */
void				crosshair_position(t_render *render, t_vline *vline,
						float alpha, int coord);
/* File: srcs/doom.c */
/* File: srcs/find_sector.c */
int					in_sector(t_sector *sector, t_v3 pos);
int					find_sector(t_sector *sectors, int nb, t_v3 pos);
int					in_sector_area(t_sector *sector, t_v3 pos);
int					find_sector_no_z(t_sector *sectors, int nb, t_v3 pos);
/* File: srcs/fix_map.c */
void				fix_sector_index2(t_doom *doom,
						unsigned short *sector_index);
void				fix_sector_index(t_doom *doom);
/* File: srcs/fps.c */
void				update_fps(t_doom *doom);
void				init_fps(t_doom *doom);
/* File: srcs/game_mode.c */
void				game_mode(t_doom *doom);
/* File: srcs/get_entity_state.c */
int					ray_collision(t_doom *doom, t_v3 enemy, t_v3 player,
						int sector);
void				get_entity_state2(t_doom *doom, t_entity *entity);
void				get_entity_state(t_doom *doom, t_entity *entity);
/* File: srcs/help.c */
void				print_help_msg(void);
/* File: srcs/icon.c */
int					set_icon(SDL_Window *window, char *dir);
/* File: srcs/keys.c */
void				poll_event(t_doom *doom);
/* File: srcs/malloc_texture_pos.c */
void				malloc_texture_pos(t_frames *entity);
/* File: srcs/minimap.c */
void				map(t_doom *doom);
/* File: srcs/movement.c */
void				movement(t_doom *doom);
/* File: srcs/orientation.c */
int					orientation(t_v3 p1, t_v3 p2, double yaw, int nb_angles);
/* File: srcs/precompute_buy_menu.c */
void				precompute_buymenu(t_doom *doom);
/* File: srcs/precompute_entities.c */
void				precompute_entities(t_doom *doom);
/* File: srcs/precompute_projectiles.c */
void				precompute_projectiles(t_doom *doom);
/* File: srcs/precompute_skybox.c */
void				compute_skybox(t_doom *doom);
void				project_skybox(t_doom *doom, t_wall *wall);
void				precompute_skybox(t_doom *doom);
void				init_skybox(t_doom *doom);
/* File: srcs/precompute_walls.c */
void				clip_to_fustrum(t_camera cam, t_wall *wall);
int					clip_wall(t_camera cam, t_wall *wall);
void				precompute_texture(t_doom *doom, t_wall *wall);
void				precompute_floor_ceil(t_doom *doom, t_sector *sector);
void				precompute_walls(t_doom *doom);
/* File: srcs/precompute_weapon.c */
void				weapon_fire_animate(t_doom *doom, t_weapon *weapon);
void				weapon_reload_animate(t_doom *doom, t_weapon *weapon);
void				equip_weapon(t_doom *doom);
void				precompute_weapon(t_doom *doom);
/* File: srcs/project_entity.c */
void				project_entity(t_doom *doom, t_entity *e,
						t_entity_render *render);
/* File: srcs/project_wall.c */
void				project_wall(t_doom *doom, t_wall *wall);
/* File: srcs/protalloc.c */
void				*protalloc(size_t size);
void				reset_sectbool(t_doom *doom, int curr_sect);
/* File: srcs/purge_entities.c */
void				purge_entities(t_doom *doom);
/* File: srcs/put_pixels.c */
void				blit_pixel_brightness(t_render *render, int coord,
						t_v3 text, t_bxpm *bxpm);
void				blit_pixel_alpha(t_render *render, int coord, t_v3 text,
						t_bxpm *bxpm);
void				blit_pixel_opaque(t_render *render, int coord, t_v3 text,
						t_bxpm *bxpm);
void				blit_pixel_skybox(t_render *render, int coord, t_v3 text,
						int side);
/* File: srcs/sound.c */
void				set_volume(int i);
void				init_sound(t_doom *doom);
/* File: srcs/spawn_entity.c */
void				spawn_entity(t_doom *doom, int type, t_v3 pos, int yaw);
void				rift_spawn(t_doom *doom);
void				respawn_rifts(t_doom *doom);
/* File: srcs/timer.c */
void				doom_timer_start(void);
double				doom_timer_end(void);
/* File: srcs/update_screen.c */
void				update_screen(t_doom *doom);
/* File: srcs/wall_to_screen_xz.c */
void				map_to_screen_vertex(t_player player, t_v3 *map,
						t_v3 *screen);
void				screen_to_map_vertex(t_player player, t_v3 *screen,
						t_v3 *map);
/* File: srcs/CollisionDetection/collision_detection.c */
int					find_from_sectbool(t_doom *doom, t_motion *motion);
int					collision_detection(t_doom *doom, t_motion motion,
						t_v3 *where, t_v3 *velocity);
/* File: srcs/CollisionDetection/crouch_collision.c */
int					crouch_collision(t_doom *doom, t_player *player);
/* File: srcs/CollisionDetection/horizontal_collision.c */
int					check_portal(t_doom *doom, t_motion *motion, t_wall *wall,
						t_v3 point);
int					check_collsion(t_motion *motion, t_wall *wall,
						t_v3 *point);
int					check_solid_surfaces(t_doom *doom, t_motion *motion,
						int sect);
int					horizontal_collision(t_doom *doom, t_motion *motion);
/* File: srcs/CollisionDetection/object_collision.c */
int					entity_collision(t_doom *doom, t_v3 *where,
						t_v3 *velocity);
/* File: srcs/CollisionDetection/projectile_collision.c */
int					target_contact(t_doom *doom, t_projectile *orb, t_v3 start,
						t_v3 dest);
/* File: srcs/CollisionDetection/slide_collision.c */
int					check_solid_surfaces_no_slide(t_doom *doom,
						t_motion *motion, int sect);
int					slide_collision(t_doom *doom, t_motion *motion,
						t_wall *wall);
/* File: srcs/CollisionDetection/vertical_collision.c */
int					vertical_collision(t_doom *doom, t_motion *motion,
						float *temp);
/* File: srcs/Draw/draw2.c */
void				draw_map(t_doom *doom);
/* File: srcs/Draw/draw_bullet_holes.c */
void				draw_wall_bh(t_render *render, t_vline *vline);
/* File: srcs/Draw/draw_ceiling.c */
void				draw_ceiling_texture(t_render *render, t_vline *vline);
/* File: srcs/Draw/draw_circle.c */
void				draw_circle(SDL_Surface *surface, Uint32 color,
						t_point center, int size);
/* File: srcs/Draw/draw_crosshair.c */
void				draw_crosshair(t_doom *doom);
/* File: srcs/Draw/draw_entity.c */
void				blit_entity(t_entity_thread *thread, int coord,
						t_v3 text);
int					draw_entity(void *arg);
void				draw_entities(t_doom *doom);
/* File: srcs/Draw/draw_floor.c */
void				draw_floor_texture(t_render *render, t_vline *vline);
/* File: srcs/Draw/draw_floor_and_ceiling.c */
void				draw_floor_and_ceiling(t_render *render, t_vline *vline);
/* File: srcs/Draw/draw_hud.c */
void				draw_hud(t_doom *doom);
/* File: srcs/Draw/draw_hud_utils.c */
void				hud_health(t_doom *doom, SDL_Rect *dstr);
void				hud_armour(t_doom *doom, SDL_Rect *dstr);
void				hud_curr_ammo(t_doom *doom, SDL_Rect *dstr);
void				hud_mag_ammo(t_doom *doom, SDL_Rect *dstr);
void				hud_dosh(t_doom *doom, SDL_Rect *dstr);
/* File: srcs/Draw/draw_line.c */
void				draw_line(SDL_Surface *surf, Uint32 color, t_point v1,
						t_point v2);
/* File: srcs/Draw/draw_neighbor_wall.c */
void				draw_neighbor_wall(t_render *render, t_vline *vline);
/* File: srcs/Draw/draw_portal_texture.c */
void				draw_portal_texture(t_render *render, t_vline *vline);
/* File: srcs/Draw/draw_projectile.c */
void				draw_projectiles(t_doom *doom);
/* File: srcs/Draw/draw_skybox.c */
void				draw_skybox(t_render *render, t_vline *vline, int side);
/* File: srcs/Draw/draw_skybox_plane.c */
void				skybox_plane_vline(t_render *render, t_vline vline,
						float start, int tx);
/* File: srcs/Draw/draw_skybox_wall.c */
void				skybox_wall_vline(t_render *render, t_vline vline,
						int tx);
/* File: srcs/Draw/draw_vline.c */
void				depth_shadding(t_render *render, t_vline *vline,
						int side);
void				vline_color_bot_top(t_render *render, t_vline *vline,
						int side);
void				vline_color_walls(t_render *render, t_vline *vline);
void				vline_monochromic(t_render *render, t_vline *vline,
						int side);
/* File: srcs/Draw/draw_wall.c */
void				draw_wall_texture(t_render *render, t_vline *vline);
/* File: srcs/Draw/draw_weapon.c */
int					weapon_thread(void *args);
void				draw_weapon(t_doom *doom);
/* File: srcs/Draw/draw_wsprites.c */
void				draw_wsprites(t_render *render, t_vline *vline);
/* File: srcs/EntityCoords/alfred1.c */
void				init_alfred(t_doom *doom);
/* File: srcs/EntityCoords/alfred2.c */
void				move_pos_alfred2(t_rect **pos);
/* File: srcs/EntityCoords/barrel.c */
void				init_barrel(t_doom *doom);
/* File: srcs/EntityCoords/ceiling_lamp.c */
void				init_ceiling_lamp(t_doom *doom);
/* File: srcs/EntityCoords/gargoyle.c */
void				init_gargoyle(t_doom *doom);
/* File: srcs/EntityCoords/ghost1.c */
void				init_ghost(t_doom *doom);
/* File: srcs/EntityCoords/ghost2.c */
void				move_pos_ghost2(t_rect **pos);
void				attack_pos_ghost2(t_rect **pos);
/* File: srcs/EntityCoords/lamp.c */
void				init_lamp(t_doom *doom);
/* File: srcs/EntityCoords/meat_hook.c */
void				init_meat_hook(t_doom *doom);
/* File: srcs/EntityCoords/med_kit.c */
void				init_med_kit(t_doom *doom);
/* File: srcs/EntityCoords/rift.c */
void				init_rift(t_doom *doom);
/* File: srcs/EntityCoords/spooky1.c */
void				init_spooky(t_doom *doom);
/* File: srcs/EntityCoords/spooky2.c */
void				move_pos_spooky2(t_rect **pos);
/* File: srcs/EntityCoords/torch.c */
void				init_torch(t_doom *doom);
/* File: srcs/Events/map_events.c */
void				map_events(t_doom *doom);
/* File: srcs/Events/sector_events.c */
void				sector_trigger_events(t_doom *doom, t_event *event);
/* File: srcs/Events/wsprite_events.c */
void				wsprite_trigger_events(t_doom *doom, t_event *event);
/* File: srcs/Free/free1.c */
void				free_doom(t_doom *doom);
/* File: srcs/Free/free2.c */
void				free_map(t_doom *doom);
void				free_render_utils(t_doom *doom);
void				free_font(t_doom *doom);
void				free_shade_shade(t_bxpm *bxpm);
/* File: srcs/Free/free3.c */
void				free_sprites_pos(t_doom *doom);
void				free_entities(t_doom *doom);
void				free_rifts(t_doom *doom);
void				free_textures(t_doom *doom);
void				free_projectiles(t_doom *doom);
/* File: srcs/Free/free4.c */
void				free_weapons(t_doom *doom);
void				free_sounds(t_doom *doom);
void				free_icon(t_doom *doom);
/* File: srcs/Init/init.c */
void				set_true_mouse(t_doom *doom);
void				init_doom(t_doom *doom);
/* File: srcs/Init/init_entity.c */
void				init_entities(t_doom *doom);
/* File: srcs/Init/init_game_mode.c */
void				init_game_mode(t_doom *doom);
/* File: srcs/Init/init_glock.c */
void				init_glock(t_doom *doom, t_weapon *weapon);
/* File: srcs/Init/init_inventory.c */
void				init_inventory(t_doom *doom);
/* File: srcs/Init/init_kar.c */
void				init_kar98(t_doom *doom, t_weapon *weapon);
/* File: srcs/Init/init_launcher.c */
void				init_launcher(t_doom *doom, t_weapon *weapon);
/* File: srcs/Init/init_minigun.c */
void				init_minigun(t_doom *doom, t_weapon *weapon);
/* File: srcs/Init/init_minimap.c */
void				init_minimap(t_doom *doom);
/* File: srcs/Init/init_player.c */
void				init_player(t_doom *doom);
/* File: srcs/Init/init_render.c */
void				init_render(t_doom *doom);
/* File: srcs/Init/init_scale.c */
void				scale_wall_height(t_doom *doom, t_wall *wall);
void				init_scale(t_doom *doom);
/* File: srcs/Init/init_sdl.c */
void				init_sdl(t_doom *doom);
/* File: srcs/Init/init_shotgun.c */
void				init_shotgun(t_doom *doom, t_weapon *weapon);
/* File: srcs/Init/init_slope.c */
float				ceiling_at(t_sector *sector, t_v3 pos);
float				floor_at(t_sector *sector, t_v3 pos);
void				init_slope_normal(t_doom *doom);
/* File: srcs/Init/init_surface_textures.c */
void				parse_surface_textures(t_doom *doom, int i, int j);
/* File: srcs/Init/init_textures.c */
void				init_textures(t_doom *doom);
/* File: srcs/Init/init_wav.c */
void				init_wav(t_doom *doom);
/* File: srcs/Init/init_weapons.c */
void				init_weapons(t_doom *doom);
/* File: srcs/ParseMap/parse_map.c */
void				parse_player(t_doom *doom, int nb, char **arr);
void				read_line(t_doom *doom, int fd,
						void (*f)(t_doom*, int, char **));
int					parse_map(t_doom *doom, char *file_name);
/* File: srcs/ParseMap/parse_map_events1.c */
void				parse_events(t_doom *doom, int nb, char **arr);
/* File: srcs/ParseMap/parse_map_events2.c */
void				floor_ceiling_event(t_event *event, int nb, char **arr);
void				spawn_event(t_doom *doom, t_event *event, int nb,
						char **arr);
void				audio_event(t_event *event, int nb, char **arr);
void				hazard_event(t_event *event, int nb, char **arr);
void				light_event(t_event *event, int nb, char **arr);
/* File: srcs/ParseMap/parse_map_header.c */
void				parse_header(t_doom *doom, int nb, char **arr);
/* File: srcs/ParseMap/parse_map_sector.c */
void				parse_vertex(t_doom *doom, int nb, char **arr);
void				parse_wall(t_doom *doom, int nb, char **arr);
void				parse_fc(t_doom *doom, int nb, char **arr);
void				complete_wall(t_sector *sect, t_wall *walls, char **id,
						char **neighbour);
void				parse_sector(t_doom *doom, int ac, char **arr);
/* File: srcs/ParseMap/parse_map_sprite.c */
int					wsprite_state(char *str);
void				parse_wsprite(t_doom *doom, int nb, char **arr);
void				parse_entity(t_doom *doom, int nb, char **arr);
/* File: srcs/ParseMap/validate_map1.c */
int					validate_map(t_doom *doom);
/* File: srcs/ParseMap/validate_map2.c */
void				sector_center(t_sector *sector);
void				fix_wall_orientation(t_sector *sector);
int					fix_wall_order(t_sector *sector);
int					is_convex(t_sector *sector);
/* File: srcs/UI/game_loading.c */
void				game_loading(t_doom *doom);
/* File: srcs/UI/game_over.c */
void				game_over(t_doom *doom);
void				game_win(t_doom *doom);
/* File: srcs/UI/game_quit.c */
void				game_quit(t_doom *doom);
/* File: srcs/BuyMenu/buymenu.c */
void				buymenu(SDL_Window *window, SDL_Surface *surf, t_inv *inv);

#endif
