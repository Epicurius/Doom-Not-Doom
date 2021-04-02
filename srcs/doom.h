/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DOOM.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 11:28:34 by nneronin          #+#    #+#             */
/*   Updated: 2020/11/26 14:47:42 by nneronin         ###   ########.fr       */
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
# include <pthread.h>
# include <fcntl.h>

#define min(a,b)			(((a) < (b)) ? (a) : (b))
#define max(a,b)			(((a) > (b)) ? (a) : (b))
#define clamp(a, mi,ma)			min(max(a,mi),ma)
//#define vxs(x0,y0, x1,y1)		((x0)*(y1) - (x1)*(y0)) //Vector cross product

typedef	struct	s_floor_ceiling
{
	double	floor;
	double	ceiling;
}		t_floor_ceiling;

typedef struct	s_vline
{
	int	y1;
	int	y2;
	double	alpha;
	double	clipped_alpha;
	double	divider;
	double	z;
	double	zrange;
	double	z_near_z;
	double	line_height;

	t_floor_ceiling	start;
	t_floor_ceiling	height;

	t_floor_ceiling	max;
	t_floor_ceiling	curr;

	/* Neighbor */
	t_floor_ceiling	max_n;
	t_floor_ceiling	curr_n;

	/* Texel */
	t_v2	texel;
	t_v2	texel_nearz;
	t_v2	texel_range;
}		t_vline;

typedef struct		s_projectile
{
	int		render;
	t_xyz		where;
	t_xyz		velocity;
	double		dist;
	int		sector;	
}			t_projectile;

typedef struct	s_stats
{
	int		hp;
	int		height;
	double		speed;
	int		flying;

	int		dmg;
	int		hostile;
	int		attack_style;
	double		scale;
	int		wonder_distance;
	int		view_distance;
	int		detection_radius;
	int		attack_range;
	int		frame_rate[4];
}		t_stats;

typedef struct		s_entity
{
	int		render;
	t_xyz		where;
	t_xyz		dest;
	t_xyz		velocity;
	int		sector;
	double		yaw;

	int		ground;


	t_stats		stat;
	int		state;
	int		frame;
	int		angle;
	
	int		id;
	int		type;
	double		scale;
	double		time;
	t_projectile	*orb;
}			t_entity;

typedef struct		s_player
{
	t_xyz		where;
	t_xyz		velocity;
	int		sector;
	double		yaw;
	double		pitch;
	double		anglesin;
	double		anglecos;
	double		horizon;

	int		hp;

	int		flying;
	int		shooting;
}			t_player;




typedef struct		s_sprite
{
	int	id;
	t_xyz	where;
	int	tx;	
	double	time;
	int	frame;
	t_rect	src;
	double	scale_w;
	double	scale_h;
	t_v2	tscale;
	int	ready;
}			t_sprite;

typedef struct		s_bh
{
	t_sprite		num[MAX_BH];
	int			curr;
	int			total;
}			t_bh;

typedef struct		s_wsprite
{
	t_sprite		*num;
	int			curr;
	int			total;
}			t_wsprite;

typedef struct		s_wall
{
	t_wsprite		wsprite;
	t_bh			bh;
	int			id;
	int			sect;
	int			visible;
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
	double		scale_v1;
	double		scale_v2;
	double		angle_z1;
	double		angle_z2;
	double		x1;
	double		x2;
	double		cx1;
	double		cx2;

	t_floor_ceiling	s1;
	t_floor_ceiling	s2;
	t_floor_ceiling	range;

	/*Neighbors values*/
	t_floor_ceiling	s1_n;
	t_floor_ceiling	s2_n;
	t_floor_ceiling	range_n;

	/*Texture values*/
	double		xrange;
	double		zrange;
	double		zcomb;
	double		xzrange;
	double		yzrange;
	double		x1z0;
	double		x0z1;
	double		y1z0;
	double		y0z1;
	t_v2		tscale;
}			t_wall;

typedef struct		s_sector
{
	int		id;
    	int		npoints;
	t_wall		**wall;
	t_plane		floor;
	t_plane		ceiling;
	int		light;
	float		gravity;
	char		visible;
} 			t_sector;

typedef struct		s_camera
{
	double		hfov;
	double		vfov;
	double		near_left;
	double		near_right;
	double		far_left;
	double		far_right;
	double		near_z;
	double		far_z;
	double		range;
	double		near_up;
	double		near_down;
	double		hscale;
	double		vscale;
	double		scale;
}			t_camera;

typedef struct		s_entity_render
{
	SDL_Surface	*surface;
	SDL_Surface	*texture;
	t_xyz		screen;
	double		scale;
	t_xyz		size;
	t_xyz		start;
	t_xyz		end;
	t_xyz		clamp_start;
	t_xyz		clamp_end;
	double		xrange;
	double		yrange;
	t_rect		img;
}			t_entity_render;

typedef struct		s_render
{
	SDL_Surface		*surface;
	t_texture		*wtx;
	t_texture		*ptx;
	t_texture		*ctx;
	t_texture		*ftx;
	t_texture		*stx;
	t_wall			*skybox;
	int			*ytop;
	int			*ybot;
	t_wall			wall;
	t_plane			floor;
	t_plane			ceiling;
	t_player		player;
	
	t_bh			*bh;
	t_wsprite		*wsprite;
	int			light;
	int			x;
	int			s;
}					t_render;

typedef struct	s_map
{
	int	w;
	int	h;
	t_i2	min;
	t_i2	max;
	int	pos_x;
	int	pos_y;
}		t_map;

typedef struct	t_nb
{
	int	walls;
	int	sectors;
	int	vertices;
	int	entities;
	int	processors;
	int	projectiles;
}		t_nb;

typedef	struct				s_fps
{
	float		curr;
	float		prev;
	int		fps;
	int		count;
	SDL_Color	color;
	TTF_Font	*font;
	SDL_Surface	*surf;
}					t_fps;

typedef struct	s_texture_sheet
{
	SDL_Surface 	*surface;
	int		nb[4][2];
	t_rect		***pos;
}			t_texture_sheet;

typedef struct				s_doom
{
	t_texture_sheet			sprites[2];
	int				quit;
	char				*file;
	SDL_Window			*win;
	SDL_Surface			*surface;
	double 				map_scale;
	int				w2;
	int				h2;

	t_nb				nb;
	t_tpool				tpool;
	t_fps				fps;
	t_keys				key;
	t_map				map;

	//Map
	t_xyz				*vert;
	t_wall				*walls;
	t_plane				*floors;
	t_plane				*ceilings;
	t_wall				skybox[4];
	t_sector			*sectors;
	t_entity			*entity;
	t_projectile			*orb;

	t_camera			cam;
	t_player			player;


	//Render
	int				str_x;
	int				end_x;
	int				*ytop;
	int				*ybot;
	double				*zbuffer;

	//Textures
	TTF_Font			*clock_font;
	t_texture			textures[50];
	t_texture			skybox_t[6]; //cube has 6 sides

	//tmp
	SDL_Surface				*imp;
}						t_doom;

int	orientation(t_xyz p1, t_xyz p2, double yaw, int nb_angles);
void	init_scale(t_doom *doom);
void	load_textures(t_doom *doom);
void	precompute_walls(t_doom *doom);
void	precompute_skybox(t_doom *doom);
void	wall_to_screen_xz(t_player player, t_wall *wall);
void	project_wall(t_doom *doom, t_wall *wall);
t_xyz	xyz(double x, double y, double z);
t_xyz	get_intersection(t_xyz a, t_xyz b, t_xyz c, t_xyz d);
void	render_wall(t_doom *doom, t_item now, int s, t_render *render, t_wall *wall);
void	vline_color(t_render *render, t_vline *vline, int color);
void	find_start_sectors(t_doom *doom, t_item *queue, int *qtotal);
void	shade_zbuffer(t_doom *doom);
int	clip_wall(t_camera cam, t_wall *wall);
void	update_camera(t_doom *doom, int x, int y);
void	reset_render_arrays(t_doom *doom);
int	init_player(t_doom *doom);

//	Enteties
void	precompute_entities(t_doom *doom);
int	init_alfred(t_doom *doom, t_texture_sheet *sprite);
int	init_spooky(t_doom *doom, t_texture_sheet *sprite);
void	ai_movement(t_doom *doom, t_entity *entity);
void	ai_attack(t_doom *doom, t_entity *entity);
void	blit_entity(t_entity_render *render);
void	init_entity_stats(t_doom *doom);
int	ai_rand_move(t_entity *entity, int rand);

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
int	animate_wsprite(t_doom *doom, t_sprite *sprite);
int	animate_entities(t_doom *doom, t_sprite *sprite);

//	Minimap
void	init_minimap(t_doom *doom);
void	map(t_doom *doom);

//	Movement
void	movement(t_doom *doom);
void	vertical_collision(t_doom *doom, t_player *player);
void	horizontal_collision(t_doom *doom, t_player *player);

//	Texture
void	DrawScreen(t_doom *doom);
void	draw_ceiling_texture(t_render *render, t_vline *vline);
void	draw_floor_texture(t_render *render, t_vline *vline);
void	draw_wall_texture(t_render *render, t_vline *vline);
void	draw_portal_texture(t_render *render, t_vline *vline);
void	draw_neighbor_wall(t_render *render, t_vline *vline);
void	draw_floor_and_ceiling(t_render *render, t_vline *vline);

//	Blit pixels
void	blit_pixel(t_render *render, int coord, t_xyz text, t_texture *tx);
void	blit_pixel_brightness(t_render *render, int coord, t_xyz text, t_texture *tx);
void	blit_pixel_opaque(t_render *render, int coord, t_xyz text, t_texture *tx);
void	blit_pixel_skybox(t_render *render, int coord, t_xyz text, int side);

//	Skybox
void	init_skybox(t_doom *doom);
void	draw_skybox(t_render *render, t_vline *vline, int side);
void	skybox_wall_vline(t_render *render, t_vline vline, int texture_w);
void	skybox_ceiling_vline(t_render *render, t_vline vline);
void	skybox_floor_vline(t_render *render, t_vline);


void	DrawEntity(t_doom *doom);
void	DrawMap(t_doom *doom);
void	draw_sector(t_doom *doom, t_item *queue, int *qtotal, t_item curr);
int	read_file(t_doom *doom, char *file_name);
int	keys(t_doom *doom, SDL_Event *event);
void	fps_func(t_doom *doom);
void	ft_circle(SDL_Surface *surface, int xc, int yc, int r);
void	init_camera(t_doom *doom);
void	screen_sectors(t_doom *doom, t_item *queue, int *qtotal);
void	collision_detection(t_doom *doom, t_player *player);

//Math wiki func
int		overlap(double a0, double a1, double b0 , double b);
int		intersect_box(t_xyz p, t_xyz d, t_xyz vert1, t_xyz vert2);
int		line_intersect(t_xyz a0, t_xyz a1, t_xyz b0, t_xyz b1);
double		point_side(t_xyz a, t_xyz b, t_xyz p);
int		find_sector(t_doom *doom, t_xyz e);
t_xyz		find_triangle_c(t_xyz a, t_xyz b, float dist);
int		ft_clamp(int x, int min, int max);
Uint32		brightness(Uint32 src, int brightness);
int	intersect_check(t_xyz w1, t_xyz w2, t_xyz p1, t_xyz p2);
double		point_distance_2d(double x1, double y1, double x2, double y2);
double		point_distance_3d(t_xyz p1, t_xyz p2);
t_xyz		closest_point_on_segment_2d(t_xyz p, t_xyz a, t_xyz b);
int		point_on_segment_2d(t_xyz p, t_xyz v1, t_xyz v2, double buffer);
int		sign(double x);
void		rect_clamp(int cx, int cy, int rw, int rh, int *x, int *y);
unsigned int	blend_alpha(unsigned int src, unsigned int dest, uint8_t alpha);
SDL_Color	hex_to_sdl_color(int hex);
double 		space_diagonal(double x, double y, double z);
double		angle_to_point(t_xyz p1, t_xyz p2);
int		compare_xyz(t_xyz a, t_xyz b);
int		compare_xy(t_xyz a, t_xyz b);
t_xyz		sum_xyz(t_xyz a, t_xyz b);

int		cohen_sutherland(t_i2 *v1, t_i2 *v2, t_i2 min, t_i2 max);
void		line(SDL_Surface *surf, Uint32 color, t_i2 *p);
t_rect		new_rect(int x1, int y1, int x2, int y2);


int		free_doom(t_doom *doom);
#endif
