/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 11:28:34 by nneronin          #+#    #+#             */
/*   Updated: 2021/07/25 09:20:26 by nneronin         ###   ########.fr       */
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

static const char	*g_launcher[2] =
{
	ROOT_PATH"ui/menu",
	NULL	
};

typedef struct s_settings
{
	t_point			size;
	float			render_resolution;
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

typedef struct s_keys
{
	int				w;
	int				a;
	int				s;
	int				d;
	int				t;
	int				p;
	int				r;
	int				m;
	int				e;
	int				space;
	int				lctr;
	int				lshift;
	int				lmouse;
	int				tab;
	int				num;
	int				equal;
}					t_keys;

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
}					t_projectile;

typedef struct s_weapon_thread
{
	SDL_Surface		*dst;
	t_rect			dstr;
	t_bxpm			*src;
	t_rect			srcr;	
}					t_weapon_thread;

typedef struct s_player
{
	t_v3			where;
	t_v3			velocity;
	int				eye_lvl;
	int				sector;
	double			yaw;
	double			pitch;
	double			anglesin;
	double			anglecos;
	double			horizon;
	int				health;
	int				armour;
	float			walk_speed;
	float			sprint_speed;
	float			jump_height;
	int				flying;
	int				action;
	int				equiped;
	int				debug;
	int				store_access;
}					t_player;

typedef struct s_wsprite
{
	int				id;
	t_v3			where;
	int				tx;	
	double			time;
	int				frame;
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
	t_wsprite		num[MAX_BH];
	int				curr;
	int				total;
}					t_bullet_hole;

typedef struct s_wall
{
	t_wsprites		wsprite;
	t_bullet_hole	bh;
	int				id;
	int				sect;
	int				visible;
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
	signed char		wtx;
	signed char		ptx;
	double			scale;
	signed char		solid;
	int				n;
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
	char			visible;
	t_v3			center;
	int				wall_ceiling_slope;
	float			ceiling_slope;
	int				wall_floor_slope;
	float			floor_slope;
	t_v2			ceiling_normal;
	t_v2			floor_normal;
}					t_sector;

typedef struct s_collision
{
	int				suffocate;
	t_v3			*where;
	t_v3			*velocity;
	t_sector		*sectors;
	t_list			*entities;
	int				*sector;
	int				nb_entities;
	int				player;
	float			hitbox_height;
	float			hitbox_radius;
	float			step_height;
}					t_collision;

typedef struct s_camera
{
	double			hfov;
	double			vfov;
	double			near_left;
	double			near_right;
	double			far_left;
	double			far_right;
	double			near_z;
	double			far_z;
	double			range;
	double			near_up;
	double			near_down;
	double			scale;
}					t_camera;

typedef struct s_entity_render
{
	float			z;
	t_point			start;
	t_point			end;
	t_point			clamp_start;
	t_point			clamp_end;
	double			xrange;
	double			yrange;
}					t_entity_render;

typedef struct s_entity
{
	t_v3			where;
	t_v3			dest;
	t_v3			velocity;
	int				sector;
	double			yaw;
	int				danger;
	int				state;
	int				frame;
	int				angle;
	t_entity_render	render;
	int				id;
	int				hp;
	int				type;
	double			scale;
	double			time;
}					t_entity;

typedef struct s_entity_thread
{
	SDL_Surface		*surface;
	t_entity_render	render;
	t_bxpm			*bxpm;
	t_rect			pos;
	int				dmg;
	int				*hp;
	int				shooting;
	int				center;
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
	t_bullet_hole	*bh;
	int				center;
	t_wsprites		wsprite;
}					t_render;

typedef struct s_map
{
	t_point			pos;
	t_rect			size;
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
	float			curr;
	float			prev;
	int				fps;
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
	int				nb[4][2];
	t_rect			***pos;
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
	int				dosh;
	int				*hp;
	int				*armour;
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
	TTF_Font		*amaz50;
	TTF_Font		*digi50;
	TTF_Font		*digi100;
}					t_fonts;

typedef struct s_event
{
	t_sector		*event_sector;
	t_sector		*trigger_sector;
	t_wsprite		*wsprite;
	int				type;
	float			min;
	float			max;
	float			amount;
	float			speed;
	float			time;
	int				dir;
	int				action;
}					t_event;

typedef struct s_doom
{
	t_settings		settings;
	int				quit;
	SDL_Window		*win;
	SDL_Surface		*surface;
	SDL_Texture		*texture;
	SDL_Renderer	*renderer;
	double			*zbuffer;
	t_fonts			font;
	t_render		*render;
	double			map_scale;
	int				w2;
	int				h2;
	int				surface_center;
	t_game			game;
	t_inv			inv;
	t_nb			nb;
	t_tpool			tpool;
	t_time			time;
	t_keys			key;
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
}					t_doom;

/* File: ai_attack.c */
void				ai_attack(t_doom *doom, t_entity *entity);
/* File: ai_movement.c */
int					ai_track_player(t_doom *doom, t_entity *entity);
int					ai_rand_move(t_doom *doom, t_entity *entity, int chance, int angle);
int					ai_rand_dodge(t_doom *doom, t_entity *entity, int chance, int angle);
void				entity_collision(t_doom *doom, t_entity *entity);
/* File: animate_wsprite.c */
int					animate_wsprite(t_doom *doom, t_wsprite *entity);
/* File: args.c */
void				args(int ac, char **av, t_settings *init);
/* File: blit_bxpm.c */
void				blit_bxpm(SDL_Surface *surface, t_bxpm *bxpm, int sx, int sy);
void				blit_bxpm_scaled(SDL_Surface *dst, t_rect dstr,
						t_bxpm *src, t_rect srcr);
/* File: blit_entity.c */
int					blit_game_entity(void *arg);
/* File: buy_menu.c */
void				buymenu_new(SDL_Window *window, SDL_Renderer *renderer, SDL_Surface *surface, t_inv *inv);
/* File: camera.c */
void				init_camera(t_doom *doom);
void				update_camera(t_doom *doom, int x, int y);
/* File: clock.c */
void				init_clock(t_doom *doom, t_bxpm *bxpm);
int					clock_wsprite(t_doom *doom, t_wall *wall, int x);
/* File: collision_detection.c */
int					horizontal_collision(t_collision *coll, t_v3 dest, int curr, int i);
int					collision_detection(t_collision *entity);
/* File: color_and_brightness.c */
SDL_Color			hex_to_sdl_color(int hex);
Uint32				brightness(Uint32 src, int light);
int					blend_alpha(unsigned int src, unsigned int dest, uint8_t alpha);
void				color_palet(t_bxpm *bxpm, int light);
void				color_palets(t_doom *doom);
/* File: compute_vline.c */
void				compute_vline_data(t_render *render, t_wall wall, t_vline *vline);
void				compute_vline_texels(t_render *render, t_wall wall, t_vline *vline);
/* File: crosshair_position.c */
void				crosshair_position(t_render *render, t_vline *vline, double alpha);
/* File: doom.c */
/* File: draw2.c */
void				draw_screen(t_doom *doom);
/* File: draw_bullet_holes.c */
void				draw_wall_bh(t_render *render, t_vline *vline);
/* File: draw_ceiling.c */
void				draw_ceiling_texture(t_render *render, t_vline *vline);
/* File: draw_crosshair.c */
void				draw_crosshair(t_doom *doom);
/* File: draw_entity.c */
void				draw_entities(t_doom *doom);
/* File: draw_floor.c */
void				draw_floor_texture(t_render *render, t_vline *vline);
/* File: draw_floor_and_ceiling.c */
void				draw_floor_and_ceiling(t_render *render, t_vline *vline);
/* File: draw_hud.c */
void				draw_hud(t_doom *doom);
/* File: draw_neighbor_wall.c */
void				draw_neighbor_wall(t_render *render, t_vline *vline);
/* File: draw_portal_texture.c */
void				draw_portal_texture(t_render *render, t_vline *vline);
/* File: draw_projectile.c */
void				draw_projectiles(t_doom *doom);
/* File: draw_skybox.c */
void				draw_skybox(t_render *render, t_vline *vline, int side);
/* File: draw_wall.c */
void				draw_wall_texture(t_render *render, t_vline *vline);
/* File: draw_weapon.c */
void				draw_weapon(t_doom *doom);
/* File: draw_wsprites.c */
void				draw_wsprites(t_render *render, t_vline *vline);
/* File: endless.c */
int					endless_round(t_doom *doom);
void				game_mode_endless(t_doom *doom);
void				game_mode(t_doom *doom);
/* File: error.c */
void				*ft_pmalloc(size_t size, char *str);
/* File: find_sector.c */
int					in_sector(t_sector *sector, t_v3 pos);
int					find_sector(t_sector *sectors, int nb, t_v3 pos);
/* File: fps.c */
void				blit_fps(t_doom *doom);
void				fps_func(t_doom *doom);
void				init_fps(t_doom *doom);
/* File: free.c */
void				free_doom(t_doom *doom);
/* File: free1.c */
void				free_map(t_doom *doom);
void				free_render_utils(t_doom *doom);
void				free_font(t_doom *doom);
void				free_color_palet(t_bxpm *bxpm);
void				free_entity_pos(t_npc_bxpm *entity);
/* File: free2.c */
void				free_sprites_pos(t_doom *doom);
void				free_entities(t_doom *doom);
void				free_rifts(t_doom *doom);
void				free_textures(t_doom *doom);
void				free_projectiles(t_doom *doom);
/* File: free3.c */
void				free_weapons(t_doom *doom);
void				free_sounds(t_doom *doom);
void				free_icon(t_doom *doom);
/* File: game_loading.c */
void				game_loading(t_doom *doom);
/* File: game_over.c */
void				game_over(t_doom *doom);
/* File: game_pause.c */
void				game_pause(t_doom *doom);
/* File: game_quit.c */
void				game_quit(t_doom *doom);
/* File: get_entity_state.c */
void				get_entity_state2(t_doom *doom, t_entity *entity);
void				get_entity_state(t_doom *doom, t_entity *entity);
/* File: help.c */
void				print_help_msg(void);
/* File: hud_utils.c */
void				hud_health(t_doom *doom);
void				hud_armour(t_doom *doom);
void				hud_curr_ammo(t_doom *doom);
void				hud_mag_ammo(t_doom *doom);
void				hud_dosh(t_doom *doom);
/* File: icon.c */
int					set_icon(SDL_Window *window, char *dir);
/* File: init.c */
void				init_doom(t_doom *doom);
/* File: init_alfred.c */
void				init_alfred(t_doom *doom);
/* File: init_barrel.c */
void				init_barrel(t_doom *doom);
/* File: init_entity.c */
void				init_entities(t_doom *doom);
/* File: init_game_mode.c */
void				init_game_mode(t_doom *doom);
/* File: init_glock.c */
void				init_glock(t_doom *doom, t_weapon *weapon);
/* File: init_inventory.c */
void				init_inventory(t_doom *doom);
/* File: init_kar.c */
void				init_kar98(t_doom *doom, t_weapon *weapon);
/* File: init_lamp.c */
void				init_lamp(t_doom *doom);
/* File: init_meat_hook.c */
void				init_meat_hook(t_doom *doom);
/* File: init_minigun.c */
void				init_minigun(t_doom *doom, t_weapon *weapon);
/* File: init_minimap.c */
void				init_minimap(t_doom *doom);
/* File: init_player.c */
void				init_player(t_doom *doom);
/* File: init_pump.c */
void				init_pump(t_doom *doom, t_weapon *weapon);
/* File: init_render.c */
void				init_render(t_doom *doom);
/* File: init_rift.c */
void				init_rift(t_doom *doom);
/* File: init_scale.c */
void				init_scale(t_doom *doom);
/* File: init_sdl.c */
void				init_sdl(t_doom *doom);
/* File: init_shotgun.c */
void				init_shotgun(t_doom *doom, t_weapon *weapon);
/* File: init_slope.c */
double				get_ceiling_at_pos(t_sector *sector, t_v3 pos);
double				get_floor_at_pos(t_sector *sector, t_v3 pos);
void				init_slope_normal(t_doom *doom);
/* File: init_spooky.c */
void				init_spooky(t_doom *doom);
/* File: init_textures.c */
int					multy_thread_bxpm(void *arg);
void				init_textures(t_doom *doom);
/* File: init_torch.c */
void				init_torch(t_doom *doom);
/* File: init_weapons.c */
void				init_weapons(t_doom *doom);
/* File: keys.c */
void				poll_event(t_doom *doom, SDL_Event *event);
/* File: line.c */
void				line(SDL_Surface *surf, Uint32 color, t_point *p);
/* File: malloc_texture_pos.c */
void				malloc_texture_pos(t_npc_bxpm *entity);
/* File: map_events.c */
void				scale_wall_height(t_doom *doom, t_wall *wall);
void				loop_events(t_doom *doom, t_event *event);
void				wsprite_trigger_events(t_doom *doom, t_event *event);
void				sector_trigger_events(t_doom *doom, t_event *event);
void				map_events(t_doom *doom);
/* File: math1.c */
t_point				new_point(int x, int y);
t_v2				new_v2(double x, double y);
t_v3				new_v3(double x, double y, double z);
t_rect				rect_xy2(int x1, int y1, int x2, int y2);
t_rect				rect_xywh(int x1, int y1, int w, int h);
/* File: math2.c */
int					comp_v3(t_v3 v1, t_v3 v2);
t_v3				add_v3(t_v3 v1, t_v3 v2);
t_v3				sub_v3(t_v3 v1, t_v3 v2);
t_v3				mult_v3(t_v3 vec, float scalar);
/* File: math3.c */
int					intersect_check_v2(t_v3 w1, t_v3 w2, t_v3 p1, t_v3 p2);
double				point_distance_v3(t_v3 p1, t_v3 p2);
t_v3				closest_point_on_segment_v2(t_v3 p, t_v3 a, t_v3 b);
int					point_on_segment_v2(t_v3 p, t_v3 v1, t_v3 v2, double buffer);
t_v3				get_intersection_v2(t_v3 a1, t_v3 a2, t_v3 b1, t_v3 b2);
/* File: math4.c */
double				vector_magnitude_v2(t_v3 v);
double				vector_magnitude_v3(t_v3 v);
double				pythagoras(double x, double y);
double				space_diagonal(t_v3 v);
t_v3				normalize(t_v3 vec);
/* File: math5.c */
double				dot_product_v2(t_v3 v1, t_v3 v2);
double				dot_product_v3(t_v3 v1, t_v3 v2);
double				vectors_angle(t_v3 v1, t_v3 v2);
double				cross_product_v2(double x1, double y1, double x2, double y2);
t_v3				cross_product_v3(t_v3 v1, t_v3 v2);
/* File: math6.c */
void				get_polar_cordinates(double len, double angle, t_v2 *polar);
void				get_cartesian_cordinates(double x, double y, double *len, double *angle);
float				to_radians(float degrees);
float				to_degrees(float radians);
/* File: math7.c */
double				angle_to_point_v2(t_v3 p1, t_v3 p2);
int					ft_sign(double x);
int					nb_overlap(double a0, double a1, double b0, double b1);
double				point_side_v2(t_v3 v1, t_v3 v2, t_v3 p);
double				point_distance_v2(double x1, double y1, double x2, double y2);
/* File: math8.c */
int					cohen_sutherland(t_point v[2], t_rect size);
/* File: minimap.c */
void				map(t_doom *doom);
/* File: movement.c */
void				movement(t_doom *doom);
/* File: object_collision.c */
void				object_collision(t_doom *doom, t_player *player);
int					sprite_collision(t_collision *e, t_v3 dest);
/* File: orientation.c */
void				degree_fix(double *degrees);
int					orientation(t_v3 p1, t_v3 p2, double yaw, int nb_angles);
/* File: parse_map_events.c */
void				get_event_type(t_event *event, char *str);
void				get_event_action(t_event *event, char *str);
void				parse_events(t_doom *doom, char **arr);
/* File: parse_map_header.c */
void				parse_header(t_doom *doom, char **arr);
/* File: parse_map_sector.c */
void				parse_vertex(t_doom *doom, char **arr);
void				parse_wall(t_doom *doom, char **arr);
void				parse_fc(t_doom *doom, char **arr);
void				complete_wall(t_sector *sect, t_wall *walls, char **id,
						char **neighbour);
void				parse_sector(t_doom *doom, char **arr);
/* File: parse_map_sprite.c */
int					wsprite_state(char *str);
void				parse_wsprite(t_doom *doom, char **arr);
int					sprite_type(char *str);
void				parse_entity(t_doom *doom, char **arr);
/* File: player_collision.c */
void				player_collision(t_doom *doom);
/* File: precompute_buy_menu.c */
void				precompute_buy_menu(t_doom *doom);
/* File: precompute_entities.c */
int					frame_animation(t_doom *doom, t_entity *entity);
void				preforme_entity_state_fuction(t_doom *doom, t_entity *entity);
int					get_coresponding_entity_state_frame(t_doom *doom, t_entity *entity);
void				precompute_entities(t_doom *doom);
/* File: precompute_projectiles.c */
int					player_contact(t_doom *doom, t_v3 start, t_v3 dest);
int					projectile_collision(t_doom *doom, t_projectile *orb, t_v3 dest);
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
void				project_entity(t_doom *doom, t_entity *ent, t_entity_render *render);
/* File: project_wall.c */
void				project_wall(t_doom *doom, t_wall *wall);
/* File: put_pixels.c */
void				blit_pixel_brightness(t_render *render, int coord, t_v3 text,
						t_bxpm *bxpm);
void				blit_pixel_alpha(t_render *render, int coord, t_v3 text, t_bxpm *bxpm);
void				blit_pixel_opaque(t_render *render, int coord, t_v3 text, t_bxpm *bxpm);
void				blit_pixel_skybox(t_render *render, int coord, t_v3 text, int side);
/* File: random.c */
void				get_entity_state_name(t_entity *entity);
void				what_vert(t_doom *doom);
/* File: read_map.c */
void				parse_player(t_doom *doom, char **arr);
void				read_line(t_doom *doom, int fd, void (*f)(t_doom*, char**));
int					read_file(t_doom *doom, char *file_name);
/* File: reload_map.c */
void				reload_map(t_doom *doom, char *file_name);
/* File: skybox_ceiling_vline.c */
void				skybox_ceiling_vline(t_render *render, t_vline vline, int tx);
/* File: skybox_floor_vline.c */
void				skybox_floor_vline(t_render *render, t_vline vline, int tx);
/* File: skybox_wall_vline.c */
void				skybox_wall_vline(t_render *render, t_vline vline, int tx);
/* File: sound.c */
void				mute(int i);
void				init_sound(t_doom *doom);
/* File: spawn_entity.c */
void				rift_spawn(t_doom *doom);
void				respawn_rifts(t_doom *doom);
/* File: update_screen.c */
void				update_screen(t_doom *doom, SDL_Surface *surface);
/* File: validate_map1.c */
int					check_entities(t_doom *doom);
int					check_player(t_doom *doom);
int					check_map(t_doom *doom);
int					validate_map(t_doom *doom);
/* File: validate_map2.c */
void				sector_center(t_sector *sector);
void				fix_wall_orientation(t_sector *sector);
int					fix_wall_order(t_doom *doom, t_sector *sector);
int					is_convex(t_doom *doom, t_sector *sector);
/* File: vertical_line.c */
Uint32				z_clr(double z, double max_z);
void				shade_zbuffer(t_render *render, t_vline *vline, int side);
void				vline_color_bot_top(t_render *render, t_vline *vline, int side);
void				vline_color_walls(t_render *render, t_vline *vline);
void				vline_monochromic(t_render *render, t_vline *vline, int side);
/* File: wall_to_screen_xz.c */
void				wall_to_screen_xz(t_player player, t_wall *wall);

#endif
