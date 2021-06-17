/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 11:28:34 by nneronin          #+#    #+#             */
/*   Updated: 2021/06/17 13:52:09 by nneronin         ###   ########.fr       */
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
# include "../../path.h"
# include "./macros.h"
#include "math.h"
# include "./enum.h"
# include "./utils.h"
# include <math.h>
# include <fcntl.h>

typedef struct	s_settings
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

typedef	struct		s_fc
{
	double			floor;
	double			ceiling;
	double			f;
	double			c;
}					t_fc;

typedef struct		s_vline
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

	t_fc	start;
	t_fc	height;

	t_fc	max;
	t_fc	curr;

	/* Neighbor */
	t_fc	max_n;
	t_fc	curr_n;

	/* Texel */
	t_v3			texel;
	t_v3			texel_nearz;
	t_v3			texel_range;

	double			real_floor;
	double			real_ceiling;
}					t_vline;

typedef struct		s_project
{
	t_v3			start;
	t_v3			where;
	t_v3			velocity;
	double			dist;
	int				sector;	
}					t_project;

typedef struct		s_data
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

typedef struct		s_player
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

typedef struct		s_wsprite
{
	int				id;
	t_v3			where;
	int				tx;	
	double			time;
	int				frame;
	t_rect			src;
	double			scale_w;
	double			scale_h;
	t_v3			tscale;
	int				ready;
}					t_wsprite;

typedef struct		s_wsprites
{
	t_wsprite		*num;
	int				curr;
	int				total;
}					t_wsprites;

typedef struct		s_bh
{
	t_wsprite		num[MAX_BH];
	int				curr;
	int				total;
}					t_bh;

typedef struct		s_wall
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

	/*Perspective*/
	double			scale_v1;
	double			scale_v2;
	double			angle_z1;
	double			angle_z2;
	double			x1;
	double			x2;
	double			cx1;
	double			cx2;

	t_fc	s1;
	t_fc	s2;
	t_fc	range;

	/*Neighbors values*/
	t_fc	s1_n;
	t_fc	s2_n;
	t_fc	range_n;

	/*Texture values*/
	double			xrange;
	double			zrange;
	double			zcomb;
	double			xzrange;
	double			yzrange;
	double			x1z0;
	double			x0z1;
	double			y1z0;
	double			y0z1;
	t_v3			tscale;
}					t_wall;

typedef struct		s_sector
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
} 					t_sector;


typedef struct		s_collision
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

typedef struct		s_camera
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

typedef struct		s_entity_render
{
	float			z;
	t_point			start;
	t_point			end;
	t_point			clamp_start;
	t_point			clamp_end;
	double			xrange;
	double			yrange;
}					t_entity_render;

typedef struct		s_entity
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

typedef struct		s_entity_thread
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

typedef struct		s_render
{
	SDL_Surface		*surface;
	t_sector		*sectors;
	int 			*fustrum;
	t_wall			*skybox;
	t_bxpm			*mtx;
	t_bxpm			*stx;
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

typedef struct		s_map
{
	int				pos_x;
	int				pos_y;
	t_rect			size;
}					t_map;

typedef struct		t_nb
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

typedef	struct		s_time
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

typedef struct		s_npc_bxpm
{
	t_bxpm			*bxpm;
	int				nb[4][2];
	t_rect			***pos;
}					t_npc_bxpm;

typedef struct		s_game_mode
{
	int				round;
	int				spawns;
	int				time;
	int				spawn_rate;
	int				cool_down;
}					t_game_mode;

typedef struct		s_weapon
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

typedef struct		s_dialog
{
	Mix_Chunk		*sound1;
	Mix_Chunk		*sound2;
	int				*done;
}					t_dialog;

typedef struct		t_inv
{
	int				dosh;
	int				*hp;
	int				*armour;
	t_weapon		*weapon;
	float			*speed;
	float			*jump;
}					t_inv;

typedef struct		s_fonts
{
	TTF_Font		*amaz50;
	TTF_Font		*digi50;
	TTF_Font		*digi100;
}					t_fonts;

typedef struct		s_doom
{
	int				quit;
	SDL_Window		*win;

	//	Render
	int				*fustrum;
	double			*zbuffer;
	t_render		*render;
	SDL_Surface		*surface;
	SDL_Texture		*texture;
	SDL_Renderer	*renderer;
	t_fonts			font;

	double 			map_scale;
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

	//	Map
	t_v3			*vert;
	t_wall			*walls;
	t_wall			skybox[4];
	t_sector		*sectors;
	t_list			*sprite;
	t_list			*rifts;


	t_list			*orb;
	t_camera		cam;
	t_player		player;

	//	Textures
	t_bxpm			stx[12];
	t_bxpm			mtx[20];
	t_bxpm			icon[5];
	t_weapon		weapon[5];
	t_bxpm			sprite_sheets[4];
	t_npc_bxpm		npc_bxpm[7];
	t_data			npe_data[7];

	Mix_Chunk		*sound[7];
	int				intro[1]; //idk frogga jony
	t_dialog		d;
	pthread_t		t;
}					t_doom;

void	*ft_pmalloc(size_t size, char *str);

//		Sound
void	init_sound(t_doom *doom);

//		Debug
void	debug_loop(t_doom *doom, SDL_Event *event);

//		Game
void	poll_event(t_doom *doom, SDL_Event *event);
void	game(char *map, t_settings init);
void	gamemode(t_doom *doom);
void	draw_weapon(t_doom *doom);
void	precompute_weapon(t_doom *doom);
void	blit_bxpm_scaled(SDL_Surface *dst, t_rect dstr, t_bxpm *src, t_rect srcr);
void	game_over(t_doom *doom);
void	game_pause(t_doom *doom);
void	game_quit(t_doom *doom);
void	game_loading(t_doom *doom);
void	update_screen(t_doom *doom, SDL_Surface *surface);

//		Read_file
int		read_file(t_doom *doom, char *file_name);
void	parse_header(t_doom *doom, char **arr);
void	parse_vertex(t_doom *doom, char **arr);
void	parse_wall(t_doom *doom, char **arr);
void	parse_player(t_doom *doom, char **arr);
void	parse_sector(t_doom *doom, char **arr);
void	parse_wsprite(t_doom *doom, char **arr);
void	parse_entity(t_doom *doom, char **arr);
void	parse_fc(t_doom *doom, char **arr);

//		Init
void	init(t_doom *doom, t_settings init);
void	init_sdl(t_doom *doom, t_settings init);
void	init_weapons(t_doom *doom);
void	init_player(t_doom *doom);
void	init_render(t_doom *doom);
void	init_fps(t_doom *doom);
void	init_game_entity(t_doom *doom);
void	init_scale(t_doom *doom);
void	init_textures(t_doom *doom);
void	init_minimap(t_doom *doom);
void	init_skybox(t_doom *doom);
void	init_camera(t_doom *doom);
void	init_clock(t_doom *doom);
void	init_inv(t_doom *doom);
void	init_gamemode(t_doom *doom);

void	init_alfred(t_doom *doom);
void	init_spooky(t_doom *doom);
void	init_rift(t_doom *doom);
void	init_barrel(t_doom *doom);
void	init_lamp(t_doom *doom);
void	init_torch(t_doom *doom);
void	init_meat_hook(t_doom *doom);


//		Time
void	get_time(time_t *t);
void	blit_fps(t_doom *doom);
void	fps_func(t_doom *doom);

//	Render map
void	DrawMap(t_doom *doom);
void	precompute_walls(t_doom *doom);
void	precompute_skybox(t_doom *doom);
void	wall_to_screen_xz(t_player player, t_wall *wall);
void	project_wall(t_doom *doom, t_wall *wall);
void	vline_monochromic(t_render *render, t_vline *vline);
int		find_start_sectors(t_doom *doom);
int		clip_wall(t_camera cam, t_wall *wall);
void	compute_vline_data(t_render *render, t_wall wall, t_vline *vline);

//	Enteties
void	Drawsprite(t_doom *doom);
void	precompute_entities(t_doom *doom);
void	ai_movement(t_doom *doom, t_entity *entity);
void	ai_attack(t_doom *doom, t_entity *entity);
int		blit_game_entity(void *arg);
int		ai_track_player(t_doom *doom, t_entity *entity);
int		ai_rand_move(t_doom *doom, t_entity *entity, int chance, int angle);
int		ai_rand_dodge(t_doom *doom, t_entity *entity, int chance, int angle);
void	malloc_texture_pos(t_npc_bxpm *sprite);
void	get_entity_render(t_doom *doom, t_entity *entity);

//	Projectiles
void	precompute_projectiles(t_doom *doom);
void	DrawProjectiles(t_doom *doom);

//	Bullet Holes
void	draw_crosshair(t_doom *doom);
void	crosshair_position(t_render *render, t_vline *vline, double alpha);
void	draw_wall_bh(t_render *render, t_vline *vline);
void	reset_bh(t_doom *doom);

//	Wall Sprites
void	draw_wsprites(t_render *render, t_vline *vline);
int		clock_wsprite(t_doom *doom, t_wall *wall, int x);
int		animate_wsprite(t_doom *doom, t_wsprite *sprite);
int		animate_entities(t_doom *doom, t_wsprite *sprite);

//	Minimap
void	map(t_doom *doom);
int		cohen_sutherland(t_point vec[2], t_rect size);
void	line(SDL_Surface *surf, Uint32 color, t_point *p);

//	Movement
void	movement(t_doom *doom);
int		horizontal_collision(t_collision *sprite, t_v3 dest);
void	player_collision(t_doom *doom);
int		sprite_collision(t_collision *entity, t_v3 dest);
int		collision_detection(t_collision *sprite);

//	Texture
void	DrawScreen(t_doom *doom);
void	draw_ceiling_texture(t_render *render, t_vline *vline);
void	draw_floor_texture(t_render *render, t_vline *vline);
void	draw_wall_texture(t_render *render, t_vline *vline);
void	draw_neighbor_wall(t_render *render, t_vline *vline);
void	draw_floor_and_ceiling(t_render *render, t_vline *vline);
void	draw_portal_texture1(t_render *render, t_vline *vline);
void	draw_portal_texture(t_render *render, t_vline *vline);

//	Blit pixels
void	blit_pixel_brightness(t_render *render, int coord, t_v3 text, t_bxpm *bxpm);
void	blit_pixel_skybox(t_render *render, int coord, t_v3 text, int side);
void	blit_pixel_opaque(t_render *render, int coord, t_v3 text, t_bxpm *tx);
void	blit_pixel_alpha(t_render *render, int coord, t_v3 text, t_bxpm *tx);

//	Skybox
void	draw_skybox(t_render *render, t_vline *vline, int side);
void	skybox_wall_vline(t_render *render, t_vline vline, int tx);
void	skybox_ceiling_vline(t_render *render, t_vline vline, int tx);
void	skybox_floor_vline(t_render *render, t_vline, int tx);


void	update_camera(t_doom *doom, int x, int y);
int		orientation(t_v3 p1, t_v3 p2, double yaw, int nb_angles);
void	keys(t_doom *doom, SDL_Event *event);

//Math wiki func
t_v3	new_v3(double x, double y, double z);
t_v3	get_intersection_v2(t_v3 a, t_v3 b, t_v3 c, t_v3 d);
int		find_sector(t_doom *doom, t_v3 e);
int		nb_overlap(double a0, double a1, double b0 , double b);
int		intersect_box(t_v3 p, t_v3 d, t_v3 vert1, t_v3 vert2);
double	point_side_v2(t_v3 a, t_v3 b, t_v3 p);
int		intersect_check_v2(t_v3 w1, t_v3 w2, t_v3 p1, t_v3 p2);
double	point_distance_v2(double x1, double y1, double x2, double y2);
double	point_distance_v3(t_v3 p1, t_v3 p2);
t_v3	closest_point_on_segment_v2(t_v3 p, t_v3 a, t_v3 b);
int		point_on_segment_v2(t_v3 p, t_v3 v1, t_v3 v2, double buffer);
int		ft_sign(double x);
void	rect_clamp(int cx, int cy, int rw, int rh, int *x, int *y);
double	angle_to_point_v2(t_v3 p1, t_v3 p2);
int		comp_v3(t_v3 a, t_v3 b);


SDL_Color	hex_to_sdl_color(int hex);
int		blend_alpha(unsigned int src, unsigned int dest, uint8_t alpha);
Uint32	brightness(Uint32 src, int brightness);
void	color_palet(t_bxpm *bxpm, int light);
void	color_palets(t_doom *doom);
void	free_doom(t_doom *doom);

void	rift_spawn(t_doom *doom);

void	load_bxpm(t_doom *doom);
void	load_bxpm2(t_doom *doom);
void	blit_bxpm(SDL_Surface *surface, t_bxpm *bxpm, int sx, int sy);

int		set_icon(SDL_Window *window, char *dir);
void	error_msg(const char *restrict format, ...);


double		get_floor_at_pos(t_sector *sector, t_v3 pos);
double		get_ceiling_at_pos(t_sector *sector, t_v3 pos);
void		precompute_slopes(t_doom *doom);

void	sector_center(t_sector *sector);
void	fix_wall_orientation(t_sector *sector);
int	fix_wall_order(t_doom *doom, t_sector *sector);
int	is_convex(t_doom *doom, t_sector *sector);


//REMOVE//
void	cs(void);
void	ce(char *str);

#endif
