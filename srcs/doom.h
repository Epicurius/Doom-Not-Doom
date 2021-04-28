/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DOOM.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 11:28:34 by nneronin          #+#    #+#             */
/*   Updated: 2021/04/28 15:04:05 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_H
# define DOOM_H

# include "../lib/libft/libft.h"
# include "../lib/libpf/ft_printf.h"
# include "../lib/tpool/tpool.h"
# include "../SDL2/includes/SDL.h"
# include "../SDL2/includes/SDL_ttf.h"
# include "../SDL2/includes/SDL_image.h"
# include "./macros.h"
# include "./utils.h"
# include <math.h>
# include <fcntl.h>

#define min(a,b)			(((a) < (b)) ? (a) : (b))
#define max(a,b)			(((a) > (b)) ? (a) : (b))


typedef struct		s_bxpm
{
	int32_t			w;
	int32_t			h;
	int32_t			bpp;
	int32_t			clr_nb;
	int32_t			pix_nb;
	uint32_t		*clr;
	unsigned short	*pix;
	uint32_t		*palet[(256 + 256)];
}					t_bxpm;

typedef	struct		s_floor_ceiling
{
	double			floor;
	double			ceiling;
}					t_floor_ceiling;

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

	t_floor_ceiling	start;
	t_floor_ceiling	height;

	t_floor_ceiling	max;
	t_floor_ceiling	curr;

	/* Neighbor */
	t_floor_ceiling	max_n;
	t_floor_ceiling	curr_n;

	/* Texel */
	t_xyz			texel;
	t_xyz			texel_nearz;
	t_xyz			texel_range;
}					t_vline;

typedef struct		s_projectile
{
	int				render;
	t_xyz			where;
	t_xyz			velocity;
	double			dist;
	int				sector;	
}					t_projectile;

typedef struct		s_stats
{
	int				health;
	int				height;
	double			speed;
	int				flying;
	int				damage;
	int				animate;
	int				hostile;
	int				attack_style;
	double			scale;
	int				wonder_distance;
	int				view_distance;
	int				detection_radius;
	int				attack_range;
	int				frame_rate[4];
}					t_stats;

typedef struct		s_sprite
{
	int				render;
	t_xyz			where;
	t_xyz			dest;
	t_xyz			velocity;
	int				sector;
	double			yaw;

	int				state;
	int				frame;
	int				angle;

	t_stats			stat;
	int				id;
	int				hp;
	int				type;
	double			scale;
	double			time;
	t_projectile	*orb;
}					t_sprite;

typedef struct		s_player
{
	t_xyz			where;
	t_xyz			velocity;
	int				sector;
	double			yaw;
	double			pitch;
	double			anglesin;
	double			anglecos;
	double			horizon;

	int				hp;

	int				flying;
	int				shooting;
}					t_player;

typedef struct		s_wsprite
{
	int				id;
	t_xyz			where;
	int				tx;	
	double			time;
	int				frame;
	t_rect			src;
	double			scale_w;
	double			scale_h;
	t_xyz			tscale;
	int				ready;
}					t_wsprite;

typedef struct		s_bh
{
	t_wsprite		num[MAX_BH];
	int				curr;
	int				total;
}					t_bh;

typedef struct		s_wsprites
{
	t_wsprite		*num;
	int				curr;
	int				total;
}					t_wsprites;

typedef struct		s_wall
{
	t_wsprites		wsprite;
	t_bh			bh;
	int				id;
	int				sect;
	int				visible;
	t_xyz			v1;
	t_xyz			v2;
	t_xyz			sv1;
	t_xyz			sv2;
	t_xyz			cv1;
	t_xyz			cv2;
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

	t_floor_ceiling	s1;
	t_floor_ceiling	s2;
	t_floor_ceiling	range;

	/*Neighbors values*/
	t_floor_ceiling	s1_n;
	t_floor_ceiling	s2_n;
	t_floor_ceiling	range_n;

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
	t_xyz			tscale;
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
} 					t_sector;


typedef struct		s_collision
{
	t_xyz			*where;
	t_xyz			*velocity;
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
	SDL_Surface		*surface;
	t_bxpm			*bxpm;
	t_xyz			screen;
	double			scale;
	t_xyz			size;
	t_xyz			start;
	t_xyz			end;
	t_xyz			clamp_start;
	t_xyz			clamp_end;
	double			xrange;
	double			yrange;
	t_rect			pos;
	int				shooting;
	int				dmg;
	int				*hp;
}					t_entity_render;

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
	SDL_Surface		*clock;
}					t_render;

typedef struct		s_map
{
	int				w;
	int				h;
	t_i2			min;
	t_i2			max;
	int				pos_x;
	int				pos_y;
}					t_map;

typedef struct		t_nb
{
	int				walls;
	int				sectors;
	int				vertices;
	int				entities;
	int				processors;
	int				projectiles;
	int				 threads;
}					t_nb;

typedef	struct		s_fps
{
	float			curr;
	float			prev;
	int				fps;
	int				count;
	SDL_Color		color;
	TTF_Font		*font;
	SDL_Surface		*surf;
}					t_fps;

typedef struct		s_texture_sheet
{
	t_bxpm			bxpm;
	int				nb[4][2];
	t_rect			***pos;
}					t_texture_sheet;

typedef struct		s_doom
{
	int				quit;
	char			*file;
	SDL_Window		*win;
	SDL_Surface		*surface;
	double 			map_scale;
	int				w2;
	int				h2;

	t_nb			nb;
	t_tpool			tpool;
	t_fps			fps;
	t_keys			key;
	t_map			map;

	//	Map
	t_xyz			*vert;
	t_wall			*walls;
	t_wall			skybox[4];
	t_sector		*sectors;
	t_list			*entity;

	t_list			*spawners;
	t_list			*entitys1;
	t_list			*objects;

	t_stats			entity_stats[2];
	t_projectile	*orb;

	t_camera		cam;
	t_player		player;

	//	Render
	t_render		*render;
	int				*fustrum;
	double			*zbuffer;

	//	Textures
	TTF_Font		*clock_font;
	SDL_Surface		*clock;
	t_bxpm			stx[12];
	t_bxpm			mtx[5];
	t_texture_sheet	sheet[2];
}					t_doom;

//		Read_file
int	read_file(t_doom *doom, char *file_name);
void	init_map_entity(t_doom *doom, char **arr);

//		Init
void	init_render(t_doom *doom);
void	init_fps(t_doom *doom);
void	init_entity(t_doom *doom);
void	init_scale(t_doom *doom);
void	init_textures(t_doom *doom);
int		init_alfred(t_texture_sheet *sprite);
int		init_spooky(t_texture_sheet *sprite);
void	init_minimap(t_doom *doom);
void	init_skybox(t_doom *doom);
void	init_camera(t_doom *doom);

//	Render map
void	DrawMap(t_doom *doom);
void	precompute_walls(t_doom *doom);
void	precompute_skybox(t_doom *doom);
void	wall_to_screen_xz(t_player player, t_wall *wall);
void	project_wall(t_doom *doom, t_wall *wall);
void	vline_monochromic(t_render *render, t_vline *vline);
int		find_start_sectors(t_doom *doom);
int	clip_wall(t_camera cam, t_wall *wall);
void	compute_vline_data(t_render *render, t_wall wall, t_vline *vline);

//	Enteties
void	DrawEntity(t_doom *doom);
void	precompute_entities(t_doom *doom);
void	ai_movement(t_doom *doom, t_sprite *entity);
void	ai_attack(t_doom *doom, t_sprite *entity);
int		blit_entity(void *arg);
int		ai_rand_move(t_sprite *entity, int rand);

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
int	clock_wsprite(t_doom *doom, t_wall *wall, int x);
int	animate_wsprite(t_doom *doom, t_wsprite *sprite);
int	animate_entities(t_doom *doom, t_wsprite *sprite);

//	Minimap
void	map(t_doom *doom);

//	Movement
void	movement(t_doom *doom);

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
void	blit_pixel_brightness(t_render *render, int coord, t_xyz text, t_bxpm *bxpm);
void	blit_pixel_skybox(t_render *render, int coord, t_xyz text, int side);
void	blit_pixel_opaque(t_render *render, int coord, t_xyz text, t_bxpm *tx);
void	blit_pixel_alpha(t_render *render, int coord, t_xyz text, t_bxpm *tx);

//	Skybox
void	draw_skybox(t_render *render, t_vline *vline, int side);
void	skybox_wall_vline(t_render *render, t_vline vline, int tx);
void	skybox_ceiling_vline(t_render *render, t_vline vline, int tx);
void	skybox_floor_vline(t_render *render, t_vline, int tx);


void	reset_render_utils(t_doom *doom);
void	update_camera(t_doom *doom, int x, int y);
int	orientation(t_xyz p1, t_xyz p2, double yaw, int nb_angles);
void	keys(t_doom *doom, SDL_Event *event);
void	fps_func(t_doom *doom);
void	ft_circle(SDL_Surface *surface, int xc, int yc, int r);

//Math wiki func
t_xyz	xyz(double x, double y, double z);
t_xyz	get_intersection(t_xyz a, t_xyz b, t_xyz c, t_xyz d);
int	find_sector(t_doom *doom, t_xyz e);
int	overlap(double a0, double a1, double b0 , double b);
int	intersect_box(t_xyz p, t_xyz d, t_xyz vert1, t_xyz vert2);
int	line_intersect(t_xyz a0, t_xyz a1, t_xyz b0, t_xyz b1);
double	point_side(t_xyz a, t_xyz b, t_xyz p);
t_xyz	find_triangle_c(t_xyz a, t_xyz b, float dist);
int	intersect_check(t_xyz w1, t_xyz w2, t_xyz p1, t_xyz p2);
double	point_distance_2d(double x1, double y1, double x2, double y2);
double	point_distance_3d(t_xyz p1, t_xyz p2);
t_xyz	closest_point_on_segment_2d(t_xyz p, t_xyz a, t_xyz b);
int	point_on_segment_2d(t_xyz p, t_xyz v1, t_xyz v2, double buffer);
int	sign(double x);
void	rect_clamp(int cx, int cy, int rw, int rh, int *x, int *y);
double 	space_diagonal(double x, double y, double z);
double	angle_to_point(t_xyz p1, t_xyz p2);
int	compare_xyz(t_xyz a, t_xyz b);
int	compare_xy(t_xyz a, t_xyz b);
t_xyz	sum_xyz(t_xyz a, t_xyz b);
int	cohen_sutherland(t_i2 *v1, t_i2 *v2, t_i2 min, t_i2 max);
void	line(SDL_Surface *surf, Uint32 color, t_i2 *p);
t_rect	new_rect(int x1, int y1, int x2, int y2);

void	player_collision(t_doom *doom);
int		entity_collision(t_collision *entity, t_xyz dest);
int		collision_detection(t_collision *entity);

SDL_Color	hex_to_sdl_color(int hex);
int	blend_alpha(unsigned int src, unsigned int dest, uint8_t alpha);
Uint32	brightness(Uint32 src, int brightness);
void	color_palet(t_bxpm *bxpm, int light);
void	color_palets(t_doom *doom);
int	free_doom(t_doom *doom);

void	free_array(char **arr);
int 	is_in_sector(t_doom *doom, int sector, t_xyz pos);
int 	find_pos_sector(t_doom *doom, t_xyz pos);

void	load_bxpm(t_doom *doom);
void	load_bbmp(t_doom *doom);
void	read_bbmp(t_bxpm *bxpm, char *file);

//REMOVE//
void	cs(void);
void	ce(char *str);

void	if_norm(char *file_name, t_bxpm *bxpm);

#endif
