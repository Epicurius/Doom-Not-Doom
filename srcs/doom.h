/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 11:28:34 by nneronin          #+#    #+#             */
/*   Updated: 2021/06/19 17:48:31 by nneronin         ###   ########.fr       */
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
# include "../path.h"
# include "./macros.h"
# include "math.h"
# include "./enum.h"
# include <math.h>
# include <fcntl.h>

typedef struct s_settings
{
	int				display_h;
	int				display_w;
	float			render_resolution;
	float			mouse_sens_x;
	float			mouse_sens_y;
	int				difficulty;
	int				fov;
	int				flag;
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
	int				chr;
	int				fnc;
	int				w;
	int				a;
	int				s;
	int				d;
	int				t;
	int				p;
	int				r;
	int				m;
	int				space;
	int				ctr_l;
	int				shift_l;
	int				lmouse;
	int				tab;
	int				num;
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
	t_v3			texel;
	t_v3			texel_nearz;
	t_v3			texel_range;
	double			real_floor;
	double			real_ceiling;
}					t_vline;

typedef struct s_project
{
	t_v3			start;
	t_v3			where;
	t_v3			velocity;
	double			dist;
	int				sector;	
}					t_project;

typedef struct s_data
{
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
	double			attack_speed;
	int				head_y;
}					t_data;

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
	int				hp;
	int				armour;
	float			walk_speed;
	float			sprint_speed;
	float			jump_height;
	int				flying;
	int				shooting;
	int				equiped;
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
}					t_wsprite;

typedef struct s_wsprites
{
	t_wsprite		*num;
	int				curr;
	int				total;
}					t_wsprites;

typedef struct s_bh
{
	t_wsprite		num[MAX_BH];
	int				curr;
	int				total;
}					t_bh;

typedef struct s_wall
{
	t_wsprites		wsprite;
	t_bh			bh;
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
	signed char		n;
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
	t_v3			ceiling_normal;
	t_v3			floor_normal;
}					t_sector;

typedef struct s_collision
{
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
	double			hscale;
	double			vscale;
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
	t_data			*data;
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
	t_bh			*bh;
	t_wsprites		wsprite;
}					t_render;

typedef struct s_map
{
	int				pos_x;
	int				pos_y;
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
	int				sprites;
	int				rifts;
	int				kills;
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

typedef struct s_game_mode
{
	int				round;
	int				spawns;
	int				time;
	int				spawn_rate;
	int				cool_down;
}					t_game_mode;

typedef struct s_weapon
{
	int				own;
	int				damage;
	int				mag_size;
	int				cur_ammo;
	int				mag_ammo;				
	int				max_ammo;
	t_bxpm			*bxpm;
	float			x_offset;
	int				frame_rate;
	int				sound;
	float			scale;
	int				time;
	int				frame;
	int				fire_frames;
	int				reload_frames;
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

typedef struct s_doom
{
	char			*root;
	int				quit;
	SDL_Window		*win;
	int				*fustrum;
	double			*zbuffer;
	t_render		*render;
	SDL_Surface		*surface;
	SDL_Texture		*texture;
	SDL_Renderer	*renderer;
	t_fonts			font;
	double			map_scale;
	float			tx_scale;
	int				w2;
	int				h2;
	int				c;
	t_game_mode		game;
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
	t_list			*sprite;
	t_list			*rifts;
	t_list			*orb;
	t_camera		cam;
	t_player		player;
	t_bxpm			stx[12];
	t_bxpm			mtx[20];
	t_bxpm			icon[5];
	t_weapon		weapon[5];
	t_bxpm			sprite_sheets[4];
	t_npc_bxpm		npc_bxpm[7];
	t_data			npe_data[7];
	int				volume;
	Mix_Chunk		*sound[7];
	int				intro[1];
	t_dialog		d;
	pthread_t		t;
}					t_doom;

//	Command + z

/* File:			srcs/ai_attack.c */
void				ai_attack(t_doom *doom, t_entity *entity);
/* File:			srcs/ai_movement.c */
void				ai_movement(t_doom *doom, t_entity *entity);
/* File:			srcs/ai_rand.c */
int					ai_track_player(t_doom *doom, t_entity *entity);
int					ai_rand_move(t_doom *doom, t_entity *entity, int chance, int angle);
int					ai_rand_dodge(t_doom *doom, t_entity *entity, int chance, int angle);
/* File:			srcs/animate.c */
int					animate_wsprite(t_doom *doom, t_wsprite *sprite);
void				animated_entity_state(t_doom *doom, t_entity *entity);
/* File:			srcs/blit_bxpm.c */
void				blit_bxpm(SDL_Surface *surface, t_bxpm *bxpm, int sx, int sy);
void				blit_bxpm_scaled(SDL_Surface *dst, t_rect dstr,
						t_bxpm *src, t_rect srcr);
/* File:			srcs/blit_entity.c */
int					blit_game_entity(void *arg);
/* File:			srcs/bxpm_weapons.c */
void				load_shotgun(t_weapon *weapon);
void				load_gun(t_weapon *weapon);
void				load_mini(t_weapon *weapon);
void				load_kar(t_weapon *weapon);
void				load_pump(t_weapon *weapon);
/* File:			srcs/camera.c */
void				init_camera(t_doom *doom);
void				update_camera(t_doom *doom, int x, int y);
/* File:			srcs/clock.c */
void				init_clock(t_doom *doom, t_bxpm *bxpm);
int					clock_wsprite(t_doom *doom, t_wall *wall, int x);
/* File:			srcs/cohen_sutherland.c */
int					cohen_sutherland(t_point v[2], t_rect size);
/* File:			srcs/collision_detection.c */
int					horizontal_collision(t_collision *sprite, t_v3 dest);
int					collision_detection(t_collision *sprite);
/* File:			srcs/color_and_brightness.c */
SDL_Color			hex_to_sdl_color(int hex);
Uint32				brightness(Uint32 src, int light);
int					blend_alpha(unsigned int src, unsigned int dest, uint8_t alpha);
void				color_palet(t_bxpm *bxpm, int light);
void				color_palets(t_doom *doom);
/* File:			srcs/compute_vline.c */
void				compute_vline_data(t_render *render, t_wall wall, t_vline *vline);
void				compute_vline_texels(t_render *render, t_wall wall, t_vline *vline);
/* File:			srcs/crosshair_position.c */
void				crosshair_position(t_render *render, t_vline *vline, double alpha);
/* File:			srcs/debug_loop.c */
void				cs(void);
void				ce(char *str);
void				debug_loop(t_doom *doom, SDL_Event *event);
/* File:			srcs/doom.c */
/* File:			srcs/draw2.c */
void				draw_screen(t_doom *doom);
/* File:			srcs/draw_bullet_holes.c */
void				draw_wall_bh(t_render *render, t_vline *vline);
/* File:			srcs/draw_ceiling.c */
void				draw_ceiling_texture(t_render *render, t_vline *vline);
/* File:			srcs/draw_crosshair.c */
void				draw_crosshair(t_doom *doom);
/* File:			srcs/draw_entity.c */
void				draw_sprites(t_doom *doom);
/* File:			srcs/draw_floor.c */
void				draw_floor_texture(t_render *render, t_vline *vline);
/* File:			srcs/draw_floor_and_ceiling.c */
void				draw_floor_and_ceiling(t_render *render, t_vline *vline);
/* File:			srcs/draw_hud.c */
void				draw_hud(t_doom *doom);
/* File:			srcs/draw_neighbor_wall.c */
void				draw_neighbor_wall(t_render *render, t_vline *vline);
/* File:			srcs/draw_portal_texture.c */
void				draw_portal_texture(t_render *render, t_vline *vline);
/* File:			srcs/draw_projectile.c */
void				draw_projectiles(t_doom *doom);
/* File:			srcs/draw_skybox.c */
void				draw_skybox(t_render *render, t_vline *vline, int side);
/* File:			srcs/draw_wall.c */
void				draw_wall_texture(t_render *render, t_vline *vline);
/* File:			srcs/draw_weapon.c */
void				draw_weapon(t_doom *doom);
/* File:			srcs/draw_wsprites.c */
void				draw_wsprites(t_render *render, t_vline *vline);
/* File:			srcs/entity_stats1.c */
void				alfred(t_doom *doom, t_data *alfred);
void				spooky(t_doom *doom, t_data *spooky);
/* File:			srcs/entity_stats2.c */
void				rift(t_doom *doom, t_data *rift);
void				barrel(t_doom *doom, t_data *sprite);
void				lamp(t_doom *doom, t_data *sprite);
void				torch(t_doom *doom, t_data *sprite);
void				meat_hook(t_doom *doom, t_data *sprite);
/* File:			srcs/error.c */
void				*ft_pmalloc(size_t size, char *str);
void				error_msg(const char *restrict format, ...);
/* File:			srcs/find_sector.c */
int					in_sector(t_sector *sector, t_v3 pos);
int					find_sector(t_sector *sectors, int nb, t_v3 pos);
/* File:			srcs/fps.c */
void				blit_fps(t_doom *doom);
void				fps_func(t_doom *doom);
void				init_fps(t_doom *doom);
/* File:			srcs/free.c */
void				free_doom(t_doom *doom);
/* File:			srcs/free1.c */
void				free_map(t_doom *doom);
void				free_render_utils(t_doom *doom);
void				free_font(t_doom *doom);
void				free_color_palet(t_bxpm *bxpm);
void				free_sprite_pos(t_npc_bxpm *sprite);
/* File:			srcs/free2.c */
void				free_sprites_pos(t_doom *doom);
void				free_sprites(t_doom *doom);
void				free_rifts(t_doom *doom);
void				free_textures(t_doom *doom);
void				free_projectiles(t_doom *doom);
/* File:			srcs/free3.c */
void				free_weapons(t_doom *doom);
void				free_sounds(t_doom *doom);
void				free_icon(t_doom *doom);
/* File:			srcs/game_loading.c */
void				game_loading(t_doom *doom);
/* File:			srcs/game_over.c */
void				game_over(t_doom *doom);
/* File:			srcs/game_pause.c */
void				game_pause(t_doom *doom);
/* File:			srcs/game_quit.c */
void				game_quit(t_doom *doom);
/* File:			srcs/hud_utils.c */
void				hud_health(t_doom *doom);
void				hud_armour(t_doom *doom);
void				hud_currammo(t_doom *doom);
void				hud_magammo(t_doom *doom);
void				hud_dosh(t_doom *doom);
/* File:			srcs/icon.c */
int					set_icon(SDL_Window *window, char *dir);
/* File:			srcs/init.c */
void				init_doom(t_doom *doom, t_settings init);
/* File:			srcs/init_alfred.c */
void				init_alfred(t_doom *doom);
/* File:			srcs/init_barrel.c */
void				init_barrel(t_doom *doom);
/* File:			srcs/init_entity.c */
void				init_game_entity(t_doom *doom);
/* File:			srcs/init_inv.c */
void				init_inv(t_doom *doom);
/* File:			srcs/init_lamp.c */
void				init_lamp(t_doom *doom);
/* File:			srcs/init_meat_hook.c */
void				init_meat_hook(t_doom *doom);
/* File:			srcs/init_player.c */
void				init_player(t_doom *doom);
/* File:			srcs/init_render.c */
void				init_render(t_doom *doom);
/* File:			srcs/init_rift.c */
void				init_rift(t_doom *doom);
/* File:			srcs/init_scale.c */
void				init_scale(t_doom *doom);
/* File:			srcs/init_sdl.c */
void				init_sdl(t_doom *doom, t_settings init);
/* File:			srcs/init_slope.c */
double				get_ceiling_at_pos(t_sector *sector, t_v3 pos);
double				get_floor_at_pos(t_sector *sector, t_v3 pos);
t_v3				get_slope_normal(t_sector *sector, int wall);
void				precompute_slopes(t_doom *doom);
/* File:			srcs/init_spooky.c */
void				init_spooky(t_doom *doom);
/* File:			srcs/init_textures.c */
void				init_textures(t_doom *doom);
/* File:			srcs/init_torch.c */
void				init_torch(t_doom *doom);
/* File:			srcs/init_weapons.c */
void				init_weapons(t_doom *doom);
/* File:			srcs/keys.c */
void				poll_event(t_doom *doom, SDL_Event *event);
/* File:			srcs/line.c */
void				line(SDL_Surface *surf, Uint32 color, t_point *p);
/* File:			srcs/malloc_texture_pos.c */
void				malloc_texture_pos(t_npc_bxpm *sprite);
/* File:			srcs/math1.c */
t_point				new_point(int x, int y);
t_v2				new_v2(double x, double y);
t_v3				new_v3(double x, double y, double z);
t_rect				rect_xy2(int x1, int y1, int x2, int y2);
t_rect				rect_xywh(int x1, int y1, int w, int h);
/* File:			srcs/math2.c */
int					comp_v3(t_v3 v1, t_v3 v2);
t_v3				add_v3(t_v3 v1, t_v3 v2);
t_v3				sub_v3(t_v3 v1, t_v3 v2);
t_v3				mult_v3(t_v3 vec, float scalar);
/* File:			srcs/math3.c */
int					intersect_check_v2(t_v3 w1, t_v3 w2, t_v3 p1, t_v3 p2);
double				point_distance_v3(t_v3 p1, t_v3 p2);
t_v3				closest_point_on_segment_v2(t_v3 p, t_v3 a, t_v3 b);
int					point_on_segment_v2(t_v3 p, t_v3 v1, t_v3 v2, double buffer);
t_v3				get_intersection_v2(t_v3 a1, t_v3 a2, t_v3 b1, t_v3 b2);
/* File:			srcs/math4.c */
double				vector_magnitude_v2(t_v3 v);
double				vector_magnitude_v3(t_v3 v);
double				pythagoras(double x, double y);
double				space_diagonal(t_v3 v);
t_v3				normalize(t_v3 vec);
/* File:			srcs/math5.c */
double				dot_product_v2(t_v3 v1, t_v3 v2);
double				dot_product_v3(t_v3 v1, t_v3 v2);
double				vectors_angle(t_v3 v1, t_v3 v2);
double				cross_product_v2(double x1, double y1, double x2, double y2);
t_v3				cross_product_v3(t_v3 v1, t_v3 v2);
/* File:			srcs/math6.c */
void				get_polar_cordinates(double len, double angle, t_v2 *polar);
void				get_cartesian_cordinates(double x, double y, double *len, double *angle);
float				to_radians(float degrees);
float				to_degrees(float radians);
/* File:			srcs/math7.c */
double				angle_to_point_v2(t_v3 p1, t_v3 p2);
int					ft_sign(double x);
int					nb_overlap(double a0, double a1, double b0, double b1);
double				point_side_v2(t_v3 v1, t_v3 v2, t_v3 p);
double				point_distance_v2(double x1, double y1, double x2, double y2);
/* File:			srcs/minimap.c */
void				map(t_doom *doom);
void				init_minimap(t_doom *doom);
/* File:			srcs/movement.c */
void				movement(t_doom *doom);
/* File:			srcs/object_collision.c */
void				object_collision(t_doom *doom, t_player *player);
int					sprite_collision(t_collision *e, t_v3 dest);
/* File:			srcs/orientation.c */
void				degree_fix(double *degrees);
int					orientation(t_v3 p1, t_v3 p2, double yaw, int nb_angles);
/* File:			srcs/parse_map_header.c */
void				parse_header(t_doom *doom, char **arr);
/* File:			srcs/parse_map_sector.c */
void				parse_vertex(t_doom *doom, char **arr);
void				parse_wall(t_doom *doom, char **arr);
void				parse_fc(t_doom *doom, char **arr);
void				complete_wall(t_sector *sect, t_wall *walls, char **id,
						char **neighbour);
void				parse_sector(t_doom *doom, char **arr);
/* File:			srcs/parse_map_sprite.c */
void				parse_wsprite(t_doom *doom, char **arr);
int					sprite_type(char *str);
void				parse_entity(t_doom *doom, char **arr);
/* File:			srcs/player_collision.c */
void				player_collision(t_doom *doom);
/* File:			srcs/precompute_entities.c */
int					frame_animation(t_doom *doom, t_entity *entity);
void				get_entity_state(t_doom *doom, t_entity *entity);
void				preforme_entity_state_fuction(t_doom *doom, t_entity *entity);
int					get_coresponding_entity_state_frame(t_doom *doom, t_entity *entity);
void				precompute_entities(t_doom *doom);
/* File:			srcs/precompute_projectiles.c */
int					player_contact(t_doom *doom, t_v3 start, t_v3 dest);
int					projectile_collision(t_doom *doom, t_project *orb, t_v3 dest);
void				precompute_projectiles(t_doom *doom);
/* File:			srcs/precompute_skybox.c */
void				compute_skybox(t_doom *doom);
void				project_skybox(t_doom *doom, t_wall *wall);
void				precompute_skybox(t_doom *doom);
void				init_skybox(t_doom *doom);
/* File:			srcs/precompute_walls.c */
void				clip_to_fustrum(t_camera cam, t_wall *wall);
int					clip_wall(t_camera cam, t_wall *wall);
void				precompute_texture(t_doom *doom, t_wall *wall);
void				precompute_floor_ceil(t_doom *doom, t_sector *sector);
void				precompute_walls(t_doom *doom);
/* File:			srcs/precompute_weapon.c */
void				weapon_fire_animate(t_doom *doom, t_weapon *weapon);
void				weapon_reload_animate(t_doom *doom, t_weapon *weapon);
void				equip_weapon(t_doom *doom);
void				precompute_weapon(t_doom *doom);
/* File:			srcs/project_entity.c */
void				project_entity(t_doom *doom, t_entity *entity, t_entity_render *render);
/* File:			srcs/project_wall.c */
void				project_wall(t_doom *doom, t_wall *wall);
/* File:			srcs/put_pixels.c */
void				blit_pixel_brightness(t_render *render, int coord, t_v3 text,
						t_bxpm *bxpm);
void				blit_pixel_alpha(t_render *render, int coord, t_v3 text, t_bxpm *bxpm);
void				blit_pixel_opaque(t_render *render, int coord, t_v3 text, t_bxpm *bxpm);
void				blit_pixel_skybox(t_render *render, int coord, t_v3 text, int side);
/* File:			srcs/random.c */
void				get_entity_state_name(t_entity *entity);
void				what_vert(t_doom *doom);
/* File:			srcs/read_map.c */
void				parse_player(t_doom *doom, char **arr);
void				read_line(t_doom *doom, int fd, void (*f)(t_doom*, char**));
void				read_type(t_doom *doom, int fd, char *line);
int					read_file(t_doom *doom, char *file_name);
/* File:			srcs/skybox_ceiling_vline.c */
void				skybox_ceiling_vline(t_render *render, t_vline vline, int tx);
/* File:			srcs/skybox_floor_vline.c */
void				skybox_floor_vline(t_render *render, t_vline vline, int tx);
/* File:			srcs/skybox_wall_vline.c */
void				skybox_wall_vline(t_render *render, t_vline vline, int tx);
/* File:			srcs/sound.c */
void				mute(int i);
void				load_wav(t_doom *doom);
void				intro(void *arg);
void				init_sound(t_doom *doom);
/* File:			srcs/stats_weapons.c */
void				init_shotgun(t_doom *doom, t_weapon *weapon);
void				init_pump(t_doom *doom, t_weapon *weapon);
void				init_gun(t_doom *doom, t_weapon *weapon);
void				init_minigun(t_doom *doom, t_weapon *weapon);
void				init_kar98(t_doom *doom, t_weapon *weapon);
/* File:			srcs/update_screen.c */
void				update_screen(t_doom *doom, SDL_Surface *surface);
/* File:			srcs/validate_map1.c */
int					check_entities(t_doom *doom);
int					check_player(t_doom *doom);
int					check_map(t_doom *doom);
int					validate_map(t_doom *doom);
/* File:			srcs/validate_map2.c */
void				sector_center(t_sector *sector);
void				fix_wall_orientation(t_sector *sector);
int					fix_wall_order(t_doom *doom, t_sector *sector);
int					is_convex(t_doom *doom, t_sector *sector);
/* File:			srcs/vertical_line.c */
Uint32				z_clr(double z, double max_z);
void				shade_zbuffer(t_render *render, t_vline *vline, int side);
void				vline_color_bot_top(t_render *render, t_vline *vline, int side);
void				vline_color_walls(t_render *render, t_vline *vline);
void				vline_monochromic(t_render *render, t_vline *vline, int side);
/* File:			srcs/wall_to_screen_xz.c */
void				wall_to_screen_xz(t_player player, t_wall *wall);
/* File:			srcs/wave.c */
void				init_gamemode(t_doom *doom);
void				spawn_mob(t_doom *doom, t_entity *rift);
void				rift_spawn(t_doom *doom);
int					eternal_round(t_doom *doom);
void				respawn_rifts(t_doom *doom);
void				game_mode(t_doom *doom);

#endif
