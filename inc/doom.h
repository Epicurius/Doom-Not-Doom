/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 11:28:34 by nneronin          #+#    #+#             */
/*   Updated: 2021/08/27 12:42:44 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_H
# define DOOM_H

# include "SDL.h"
# include "SDL_ttf.h"
# include "SDL_mixer.h"
# include "libft.h"
# include "libpf.h"
# include "tpool.h"
# include "bxpm.h"
# include "macros.h"
# include "libm.h"
# include "enum.h"
# include "path.h"
# include "resources.h"
# include <math.h>
# include <fcntl.h>

# define PROT_ALLOC(size)	prot_alloc(size, __FILE__, __FUNCTION__, __LINE__)

typedef struct s_settings
{
	t_point			size;
	float			rresolution;
	t_v2			mouse;
	int				difficulty;
	int				fov;
	int				debug;
	int				launcher;
}					t_settings;

typedef struct s_plane
{
	int				tx;
	double			y;
	double			correct;
	double			head;
	double			feet;
	double			scale;
}					t_plane;

typedef struct s_fc
{
	double			floor;
	double			ceiling;
}					t_fc;

typedef struct s_vline
{
	int				y1;
	int				y2;
	double			alpha;
	double			clipped_alpha;
	double			divider;
	double			z;
	double			zrange;
	double			z_near_z;
	double			line_height;
	t_fc			start;
	t_fc			height;
	t_fc			max;
	t_fc			curr;
	t_fc			max_n;
	t_fc			curr_n;
	t_v2			texel;
	t_v2			texel_nearz;
	t_v2			texel_range;
	double			real_floor;
	double			real_ceiling;
}					t_vline;

typedef struct s_projectile
{
	t_v3			start;
	t_v3			where;
	t_v3			velocity;
	double			dist;
	int				sector;
	int				moving;
	int				target;
	int				range;
}					t_projectile;

typedef struct s_weapon_thread
{
	SDL_Surface		*dst;
	t_bxpm			*src;
	t_rect			dstr;
	t_rect			srcr;	
}					t_weapon_thread;

typedef struct s_player
{
	t_v3			where;
	t_v3			velocity;
	int				eyelvl;
	int				sector;
	double			yaw;
	double			pitch;
	double			anglesin;
	double			anglecos;
	double			horizon;
	int				health;
	int				armour;
	int				flight;
	int				action;
	int				equiped;
	int				debug;
	int				store_access;
	int				hm;
	float			walk_speed;
	float			sprint_speed;
	float			jump_height;
}					t_player;

typedef struct s_wsprite
{
	int				id;
	t_v3			where;
	int				tx;	
	int				frame;
	int				time;
	t_rect			src;
	double			scale_w;
	double			scale_h;
	t_v2			tscale;
	int				ready;
	int				trigger;
	int				state;
	int				action;
}					t_wsprite;

typedef struct s_wsprites
{
	t_wsprite		*num;
	int				curr;
	int				total;
}					t_wsprites;

typedef struct s_bullet_hole
{
	t_wsprite		num[MAX_BULLET_HOLES];
	int				curr;
	int				total;
}					t_bullet_hole;

typedef struct s_wall
{
	int				id;
	int				sect;
	int				visible;
	int				n;
	t_v3			v1;
	t_v3			v2;
	t_v3			sv1;
	t_v3			sv2;
	t_v3			cv1;
	t_v3			cv2;
	double			scale_w;
	double			scale_h;
	double			width;
	double			height;
	double			scale;
	double			scale_v1;
	double			scale_v2;
	double			angle_z1;
	double			angle_z2;
	double			x1;
	double			x2;
	double			cx1;
	double			cx2;
	t_fc			static_v1;
	t_fc			static_v2;
	t_fc			static_range;
	t_fc			slope_v1;
	t_fc			slope_v2;
	t_fc			slope_range;
	t_fc			nslope_v1;
	t_fc			nslope_v2;
	t_fc			nslope_range;
	double			xrange;
	double			zrange;
	double			zcomb;
	double			xzrange;
	double			yzrange;
	double			x1z0;
	double			x0z1;
	double			y1z0;
	double			y0z1;
	t_v2			tscale;
	signed char		wtx;
	signed char		ptx;
	signed char		solid;
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
	int				wall_ceiling_slope;
	float			ceiling_slope;
	int				wall_floor_slope;
	float			floor_slope;
	t_v2			ceiling_normal;
	t_v2			floor_normal;
	int				trigger;
	char			visible;
}					t_sector;

typedef struct s_camera
{
	double			hfov;
	double			vfov;
	double			near_left;
	double			near_right;
	double			far_left;
	double			far_right;
	double			range;
	double			near_up;
	double			near_down;
	double			scale;
}					t_camera;

typedef struct s_entity_render
{
	t_point			start;
	t_point			end;
	t_point			clamp_start;
	t_point			clamp_end;
	double			xrange;
	double			yrange;
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
	int				*hm;
	int				shooting;
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
	t_camera		cam;
	t_player		player;
	int				ytop;
	int				ybot;
	int				x;
	int				xend;
	t_wall			wall;
	t_plane			floor;
	t_plane			ceiling;
	int				light;
	int				s;
	t_bullet_hole	*bullet_hole;
	t_v3			center;
	t_wsprites		wsprite;
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
	struct tm		date;
	SDL_Color		clock_fg;
	SDL_Color		clock_bg;
}					t_time;

typedef struct s_npc_bxpm
{
	t_bxpm			*bxpm;
	t_rect			***pos;
	int				nb[4][2];
}					t_npc_bxpm;

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
	float			x_offset;
	int				frame_rate;
	int				sound;
	float			scale;
	int				time;
	int				frame;
	int				fire_frames;
	int				reload_frames;
	t_bxpm			*bxpm;
}					t_weapon;

typedef struct s_dialog
{
	Mix_Chunk		*sound1;
	Mix_Chunk		*sound2;
	int				*done;
}					t_dialog;

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
	t_sector		*event_sector;
	t_wsprite		*wsprite;
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
	char			*path;
	int				entity;
	t_v3			pos;
	int				yaw;
	int				light;
}					t_event;

typedef struct s_motion
{
	int				flight;
	int				sector;
	double			height;
	double			step;
	t_v3			where;
	t_v3			velocity;
	t_v3			dest;
}					t_motion;

typedef struct s_doom
{
	t_settings		settings;
	SDL_Window		*win;
	SDL_Surface		*surface;
	SDL_Texture		*texture;
	SDL_Renderer	*renderer;
	double			*zbuffer;
	int				quit;
	int				*sectbool;
	double			map_scale;
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
	t_npc_bxpm		npc_bxpm[ENTITY_AMOUNT];
	t_event			*events;
	char			keys[517];
}					t_doom;

/* File: ai_attack.c */
void				ai_attack(t_doom *doom, t_entity *entity);
/* File: ai_movement.c */
int					ai_track_player(t_doom *doom, t_entity *entity);
int					ai_rand_move(t_doom *doom, t_entity *entity,
						int chance, int angle);
int					ai_rand_dodge(t_doom *doom, t_entity *entity,
						int chance, int angle);
void				ai_collision(t_doom *doom, t_entity *entity);
/* File: animate_wsprite.c */
int					animate_wsprite(t_doom *doom, t_wsprite *entity);
/* File: args.c */
void				args(int ac, char **av, t_settings *init);
/* File: blit_bxpm.c */
void				blit_bxpm(SDL_Surface *surface, t_bxpm *bxpm,
						int sx, int sy);
void				blit_bxpm_scaled(SDL_Surface *dst, t_rect dstr,
						t_bxpm *src, t_rect srcr);
/* File: camera.c */
void				init_camera(t_doom *doom);
void				update_camera(t_doom *doom);
/* File: clock.c */
void				init_clock(t_doom *doom, t_bxpm *bxpm);
int					clock_wsprite(t_doom *doom, t_wall *wall, int x);
/* File: color_and_brightness.c */
SDL_Color			hex_to_sdl_color(int hex);
Uint32				brightness(Uint32 src, int light);
int					blend_alpha(unsigned int src, unsigned int dest,
						uint8_t alpha);
void				shade_palets(t_doom *doom, int s, int w);
/* File: compute_vline.c */
void				compute_vline_data(t_render *render, t_wall wall,
						t_vline *vline);
void				compute_vline_texels(t_render *render, t_wall wall,
						t_vline *vline);
/* File: crosshair_position.c */
void				crosshair_position(t_render *render,
						t_vline *vline, double alpha, int coord);
/* File: doom.c */
/* File: endless.c */
int					endless_round(t_doom *doom);
void				game_mode_endless(t_doom *doom);
void				game_mode(t_doom *doom);
/* File: find_sector.c */
int					in_sector(t_sector *sector, t_v3 pos);
int					find_sector(t_sector *sectors, int nb, t_v3 pos);
int					in_sector_area(t_sector *sector, t_v3 pos);
int					find_sector_no_z(t_sector *sectors, int nb, t_v3 pos);
/* File: fps.c */
void				fps_func(t_doom *doom);
void				init_fps(t_doom *doom);
/* File: get_entity_state.c */
int					ray_collision(t_doom *doom, t_v3 enemy, t_v3 player,
						int sector);
void				get_entity_state2(t_doom *doom, t_entity *entity);
void				get_entity_state(t_doom *doom, t_entity *entity);
/* File: help.c */
void				print_help_msg(void);
/* File: icon.c */
int					set_icon(SDL_Window *window, char *dir);
/* File: keys.c */
void				poll_event(t_doom *doom);
/* File: malloc_texture_pos.c */
void				malloc_texture_pos(t_npc_bxpm *entity);
/* File: map_events.c */
void				map_events(t_doom *doom);
/* File: minimap.c */
void				map(t_doom *doom);
/* File: movement.c */
void				movement(t_doom *doom);
/* File: orientation.c */
int					orientation(t_v3 p1, t_v3 p2, double yaw, int nb_angles);
/* File: precompute_buy_menu.c */
void				precompute_buy_menu(t_doom *doom);
/* File: precompute_entities.c */
void				precompute_entities(t_doom *doom);
/* File: precompute_projectiles.c */
void				precompute_projectiles(t_doom *doom);
/* File: precompute_skybox.c */
void				compute_skybox(t_doom *doom);
void				project_skybox(t_doom *doom, t_wall *wall);
void				precompute_skybox(t_doom *doom);
void				init_skybox(t_doom *doom);
/* File: precompute_walls.c */
void				clip_to_fustrum(t_camera cam, t_wall *wall);
int					clip_wall(t_camera cam, t_wall *wall);
void				precompute_texture(t_doom *doom, t_wall *wall);
void				precompute_floor_ceil(t_doom *doom, t_sector *sector);
void				precompute_walls(t_doom *doom);
/* File: precompute_weapon.c */
void				weapon_fire_animate(t_doom *doom, t_weapon *weapon);
void				weapon_reload_animate(t_doom *doom, t_weapon *weapon);
void				equip_weapon(t_doom *doom);
void				precompute_weapon(t_doom *doom);
/* File: project_entity.c */
void				project_entity(t_doom *doom, t_entity *ent,
						t_entity_render *render);
/* File: project_wall.c */
void				project_wall(t_doom *doom, t_wall *wall);
/* File: protalloc.c */
void				*prot_alloc(size_t size, char *file, char *func, int line);
void				*protalloc(size_t siz, char *str);
void				reset_sectbool(t_doom *doom, int curr_sect);
/* File: purge_entities.c */
void				purge_entities(t_doom *doom);
/* File: put_pixels.c */
void				blit_pixel_brightness(t_render *render, int coord,
						t_v3 text, t_bxpm *bxpm);
void				blit_pixel_alpha(t_render *render, int coord,
						t_v3 text, t_bxpm *bxpm);
void				blit_pixel_opaque(t_render *render, int coord,
						t_v3 text, t_bxpm *bxpm);
void				blit_pixel_skybox(t_render *render, int coord,
						t_v3 text, int side);
/* File: random.c */
void				get_entity_state_name(t_entity *entity);
void				what_vert(t_doom *doom);
/* File: reload_map.c */
//void				reload_map(t_doom *doom, char *file_name);
/* File: sector_trigger_events.c */
void				sector_trigger_events(t_doom *doom, t_event *event);
/* File: sound.c */
void				mute(int i);
void				init_sound(t_doom *doom);
/* File: spawn_entity.c */
void				rift_spawn(t_doom *doom);
void				respawn_rifts(t_doom *doom);
/* File: update_screen.c */
void				update_screen(t_doom *doom);
/* File: wall_to_screen_xz.c */
void				wall_to_screen_xz(t_player player, t_wall *wall);
/* File: wsprite_trigger_events.c */
void				wsprite_trigger_events(t_doom *doom, t_event *event);
/* File: BuyMenu/buy_menu.c */
void				buymenu_new(SDL_Window *window, SDL_Renderer *renderer,
						SDL_Surface *surface, t_inv *inv);
/* File: CollisionDetection/collision_detection.c */
int					find_from_sectbool(t_doom *doom, t_motion motion);
int					collision_detection(t_doom *doom, t_motion motion,
						t_v3 *where, t_v3 *velocity);
/* File: CollisionDetection/crouch_collision.c */
int					crouch_collision(t_doom *doom, t_player *player);
/* File: CollisionDetection/horizontal_collision.c */
int					check_portal(t_doom *doom, t_motion *motion,
						t_wall *wall, t_v3 point);
int					check_collsion(t_motion *motion,
						t_wall *wall, t_v3 *point);
int					check_solid_surfaces(t_doom *doom,
						t_motion *motion, int sect);
/* File: CollisionDetection/object_collision.c */
int					entity_collision(t_doom *doom, t_v3 *where, t_v3 *velocity);
/* File: CollisionDetection/projectile_collision.c */
int					target_contact(t_doom *doom, t_projectile *orb,
						t_v3 start, t_v3 dest);
/* File: CollisionDetection/slide_collision.c */
int					check_solid_surfaces_no_slide(t_doom *doom,
						t_motion *motion, int sect);
int					slide_collision(t_doom *doom,
						t_motion *motion, t_wall *wall);
/* File: CollisionDetection/vertical_collision.c */
int					vertical_collision(t_doom *doom, t_motion *motion);
/* File: Draw/draw2.c */
void				draw_screen(t_doom *doom);
/* File: Draw/draw_bullet_holes.c */
void				draw_wall_bh(t_render *render,
						t_vline *vline);
/* File: Draw/draw_ceiling.c */
void				draw_ceiling_texture(t_render *render,
						t_vline *vline);
/* File: Draw/draw_circle.c */
void				draw_circle(SDL_Surface *surface, Uint32 color,
						t_point center, int size);
/* File: Draw/draw_crosshair.c */
void				draw_crosshair(t_doom *doom);
/* File: Draw/draw_entity.c */
void				blit_entity(t_entity_thread *thread, int coord, t_v3 text);
int					draw_entity(void *arg);
void				draw_entities(t_doom *doom);
/* File: Draw/draw_floor.c */
void				draw_floor_texture(t_render *render,
						t_vline *vline);
/* File: Draw/draw_floor_and_ceiling.c */
void				draw_floor_and_ceiling(t_render *render,
						t_vline *vline);
/* File: Draw/draw_hud.c */
void				draw_hud(t_doom *doom);
/* File: Draw/draw_hud_utils.c */
void				hud_health(t_doom *doom, SDL_Rect *dstr);
void				hud_armour(t_doom *doom, SDL_Rect *dstr);
void				hud_curr_ammo(t_doom *doom, SDL_Rect *dstr);
void				hud_mag_ammo(t_doom *doom, SDL_Rect *dstr);
void				hud_dosh(t_doom *doom, SDL_Rect *dstr);
/* File: Draw/draw_line.c */
void				draw_line(SDL_Surface *surf, Uint32 color,
						t_point v1, t_point v2);
/* File: Draw/draw_neighbor_wall.c */
void				draw_neighbor_wall(t_render *render,
						t_vline *vline);
/* File: Draw/draw_portal_texture.c */
void				draw_portal_texture(t_render *render,
						t_vline *vline);
/* File: Draw/draw_projectile.c */
void				draw_projectiles(t_doom *doom);
/* File: Draw/draw_skybox.c */
void				draw_skybox(t_render *render,
						t_vline *vline, int side);
/* File: Draw/draw_skybox_ceiling.c */
void				skybox_ceiling_vline(t_render *render,
						t_vline vline, int tx);
/* File: Draw/draw_skybox_floor.c */
void				skybox_floor_vline(t_render *render,
						t_vline vline, int tx);
/* File: Draw/draw_skybox_wall.c */
void				skybox_wall_vline(t_render *render,
						t_vline vline, int tx);
/* File: Draw/draw_vline.c */
Uint32				z_clr(double z, double max_z);
void				shade_zbuffer(t_render *render,
						t_vline *vline, int side);
void				vline_color_bot_top(t_render *render,
						t_vline *vline, int side);
void				vline_color_walls(t_render *render,
						t_vline *vline);
void				vline_monochromic(t_render *render,
						t_vline *vline, int side);
/* File: Draw/draw_wall.c */
void				draw_wall_texture(t_render *render,
						t_vline *vline);
/* File: Draw/draw_weapon.c */
int					weapon_thread(void *args);
void				draw_weapon(t_doom *doom);
/* File: Draw/draw_wsprites.c */
void				draw_wsprites(t_render *render,
						t_vline *vline);
/* File: EntityCoords/alfred1.c */
void				init_alfred(t_doom *doom);
/* File: EntityCoords/alfred2.c */
void				move_pos_alfred2(t_rect **pos);
/* File: EntityCoords/barrel.c */
void				init_barrel(t_doom *doom);
/* File: EntityCoords/ceiling_lamp.c */
void				init_ceiling_lamp(t_doom *doom);
/* File: EntityCoords/gargoyl.c */
void				init_gargoyl(t_doom *doom);
/* File: EntityCoords/ghost1.c */
void				init_ghost(t_doom *doom);
/* File: EntityCoords/ghost2.c */
void				move_pos_ghost2(t_rect **pos);
void				attack_pos_ghost2(t_rect **pos);
/* File: EntityCoords/lamp.c */
void				init_lamp(t_doom *doom);
/* File: EntityCoords/meat_hook.c */
void				init_meat_hook(t_doom *doom);
/* File: EntityCoords/med_kit.c */
void				init_med_kit(t_doom *doom);
/* File: EntityCoords/rift.c */
void				init_rift(t_doom *doom);
/* File: EntityCoords/spooky1.c */
void				init_spooky(t_doom *doom);
/* File: EntityCoords/spooky2.c */
void				move_pos_spooky2(t_rect **pos);
/* File: EntityCoords/torch.c */
void				init_torch(t_doom *doom);
/* File: Free/free1.c */
void				free_doom(t_doom *doom);
/* File: Free/free2.c */
void				free_map(t_doom *doom);
void				free_render_utils(t_doom *doom);
void				free_font(t_doom *doom);
void				free_shade_palet(t_bxpm *bxpm);
void				free_entity_pos(t_npc_bxpm *entity);
/* File: Free/free3.c */
void				free_sprites_pos(t_doom *doom);
void				free_entities(t_doom *doom);
void				free_rifts(t_doom *doom);
void				free_textures(t_doom *doom);
void				free_projectiles(t_doom *doom);
/* File: Free/free4.c */
void				free_weapons(t_doom *doom);
void				free_sounds(t_doom *doom);
void				free_icon(t_doom *doom);
/* File: Init/init.c */
void				init_doom(t_doom *doom);
/* File: Init/init_entity.c */
void				init_entities(t_doom *doom);
/* File: Init/init_game_mode.c */
void				init_game_mode(t_doom *doom);
/* File: Init/init_glock.c */
void				init_glock(t_doom *doom, t_weapon *weapon);
/* File: Init/init_inventory.c */
void				init_inventory(t_doom *doom);
/* File: Init/init_kar.c */
void				init_kar98(t_doom *doom, t_weapon *weapon);
/* File: Init/init_launcher.c */
void				init_launcher(t_doom *doom, t_weapon *weapon);
/* File: Init/init_minigun.c */
void				init_minigun(t_doom *doom, t_weapon *weapon);
/* File: Init/init_minimap.c */
void				init_minimap(t_doom *doom);
/* File: Init/init_player.c */
void				init_player(t_doom *doom);
/* File: Init/init_render.c */
void				init_render(t_doom *doom);
/* File: Init/init_scale.c */
void				scale_wall_height(t_doom *doom, t_wall *wall);
void				init_scale(t_doom *doom);
/* File: Init/init_sdl.c */
void				init_sdl(t_doom *doom);
/* File: Init/init_shotgun.c */
void				init_shotgun(t_doom *doom, t_weapon *weapon);
/* File: Init/init_slope.c */
double				ceiling_at(t_sector *sector, t_v3 pos);
double				floor_at(t_sector *sector, t_v3 pos);
void				init_slope_normal(t_doom *doom);
/* File: Init/init_textures.c */
void				init_textures(t_doom *doom);
/* File: Init/init_weapons.c */
void				init_weapons(t_doom *doom);
/* File: ParseMap/parse_map.c */
void				parse_player(t_doom *doom, int ac, char **av);
void				read_line(t_doom *doom, int fd,
						void (*f)(t_doom*, int, char**));
int					parse_map(t_doom *doom, char *file_name);
/* File: ParseMap/parse_map_events.c */
void				get_event_type(t_event *event, char *str);
void				get_event_action(t_event *event, char *str);
void				parse_events(t_doom *doom, int ac, char **av);
/* File: ParseMap/parse_map_header.c */
void				parse_header(t_doom *doom, int ac, char **av);
/* File: ParseMap/parse_map_sector.c */
void				parse_vertex(t_doom *doom, int ac, char **av);
void				parse_wall(t_doom *doom, int ac, char **av);
void				parse_fc(t_doom *doom, int ac, char **av);
void				complete_wall(t_sector *sect, t_wall *walls, char **id,
						char **neighbour);
void				parse_sector(t_doom *doom, int ac, char **av);
/* File: ParseMap/parse_map_sprite.c */
int					wsprite_state(char *str);
void				parse_wsprite(t_doom *doom, int ac, char **av);
void				parse_entity(t_doom *doom, int ac, char **av);
/* File: ParseMap/validate_map1.c */
int					check_entities(t_doom *doom);
int					check_player(t_doom *doom);
int					check_map(t_doom *doom);
int					validate_map(t_doom *doom);
/* File: ParseMap/validate_map2.c */
void				sector_center(t_sector *sector);
void				fix_wall_orientation(t_sector *sector);
int					fix_wall_order(t_sector *sector);
int					is_convex(t_sector *sector);
/* File: UI/game_loading.c */
void				game_loading(t_doom *doom);
/* File: UI/game_over.c */
void				game_over(t_doom *doom);
/* File: UI/game_pause.c */
void				game_pause(t_doom *doom);
/* File: UI/game_quit.c */
void				game_quit(t_doom *doom);


int	ticks_elapsed(int curr_tick, int start_tick, int ticks);
void	floor_ceiling_event(t_doom *doom, t_event *event, int nb, char **arr);
void	spawn_event(t_doom *doom, t_event *event, int nb, char **arr);
void	audio_event(t_doom *doom, t_event *event, int nb, char **arr);
void	hazard_event(t_doom *doom, t_event *event, int nb, char **arr);
void	spawn_entity(t_doom *doom, int type, t_v3 pos, int yaw);
void	light_event(t_doom *doom, t_event *event, int nb, char **arr);

#endif
