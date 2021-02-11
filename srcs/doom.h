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
# include <math.h>
# include <pthread.h>
# include <fcntl.h>

#define min(a,b)			(((a) < (b)) ? (a) : (b))
#define max(a,b)			(((a) > (b)) ? (a) : (b))
#define clamp(a, mi,ma)			min(max(a,mi),ma)
#define vxs(x0,y0, x1,y1)		((x0)*(y1) - (x1)*(y0)) //Vector cross product
#define Yaw(y,z)			(y + z*doom->player.pitch)

typedef struct s_item
{
	int sectorno;
	int sx1;
	int sx2;
}				t_item;

typedef struct	s_xyz
{
	float	x;
	float	y;
	float	z;
}				t_xyz;

typedef struct	s_tetragon
{
	t_xyz		a;
	t_xyz		b;
	t_xyz		c;
	t_xyz		d;
}				t_tetragon;

typedef struct	s_ab
{
	int			a1;
	int			a2;
	int			b1;
	int			b2;
}				t_ab;

typedef struct	s_scale
{
	t_xyz		edges[2];
	float		xscale1;
	float		yscale1;
	float		xscale2;
	float		yscale2;
	int			x1;
	int			x2;
}				t_scale;

typedef struct	s_height_info //yinfo
{
	float		yceil;
	float		yfloor;
	float		nyceil;
	float		nyfloor;
	t_ab		y;
	t_ab		ny;
}				t_height_info;

typedef struct		s_entity
{
	short			id;
	t_xyz			where;
	short			sect;
	float			dist;
	SDL_Rect		srcr;
	SDL_Rect		dstr;
}					t_entity;

typedef struct	s_sector
{
    float		floor;
	float		ceil;
    signed char *neighbors;
    signed char *textures;
    unsigned	npoints;
    t_xyz		*vertex;
	float		light;
	float		gravity;
} 				t_sector;

typedef struct	s_player
{
	t_xyz		where;
    t_xyz		velocity;
	float 		pitch;
    float		yaw;
	float		anglesin;
	float		anglecos;
	int 		moving;
	int			falling;
	int			ground;
	int			ducking;
    unsigned	sector;
}				t_player;

typedef	struct		s_keys
{
	int				chr;
	short			num;
	int				fnc;
	int				w;
	int				a;
	int				s;
	int				d;
	int				t;
	int				p;
	int				space;
	int				l_ctrl;
	int				l_shift;
	int				tab;
}					t_keys;

typedef	struct		s_fps
{
	float		curr;
	float		prev;
	float		avg;
	TTF_Font	*font;
}					t_fps;

typedef struct		s_wall
{
	t_xyz			v1;
	t_xyz			v2;
	int				texture;
}					t_wall;

typedef struct		s_render
{
	int				x;
	int 			neighbor;
	int				texture;
	SDL_Surface		*surface;
	SDL_Surface		*ctx;
	SDL_Surface		*wtx;
	SDL_Surface		*ftx;
	short			*ytop;
	short			*ybot;
	int				img_res;
	float			light;
	int				affine_x;
	t_player		player;
	t_height_info	height_info;
	int				x1;
	int				x2;
}					t_render;


typedef struct		s_doom
{
	//window_init
	int					quit;
	char				*file;
	char				*name;
	SDL_Window			*win;
	SDL_Surface			*surface;
	SDL_Texture			*tx;
	SDL_Renderer			*rend;
	t_tpool				tpool;

	//read_map
	t_xyz				*vert;//is redundant after secotors are created
	t_wall				*walls; //temp
	t_sector			*sectors;
	t_entity			*entity;
	t_player			player;
	unsigned			num_sector;
	unsigned			num_sectors;
	unsigned			num_entity;

	//Input
	t_keys				key;

	//random
	int					start_x;
	int					end_x;
	float				pitch;
	t_fps				fps;
	short				ytop[W]; //20 sectors see at onece
	short				ybot[W]; //W must be >= H
	t_height_info		height_info;
	char				pz[W * H];

	//Textures
	SDL_Surface			*texture[5];
	int					u0;
	int					u1;
	SDL_Surface				*imp;

}						t_doom;

void	player_view_fustrum(t_doom *doom, t_scale *viewpoint);
void	vline1(t_render *render, int y1, int y2, int color);
void	t_vline1(t_doom *doom, int x, t_ab y, t_ab cy, float light);
int		t_vline2(void *arg);
int		t_vline3(t_render *render, t_ab y, t_ab cy);
void	rotate_wall_sector(t_sector *sect, int s, t_player *player, t_scale *vewpoint);
void	player_perspective_tranformation(t_scale *viewpoint);
void	DrawScreen(t_doom *doom);
void	DrawMap(t_doom *doom);
void	sector_behind_edge(t_doom *doom, int x, int neighbor, int z);
void	render_wall(t_doom *doom, t_item now, int s, t_render *render, t_scale viewpoint);
void	floor_ceiling_heights(t_doom *doom, int neighbor, t_sector *sect, t_scale viewpoint);
void	draw_sector(t_doom *doom, t_item *queue, int *qtotal, t_item curr);
int		read_file(t_doom *doom, char *file_name);
void	vertical_collision(t_doom *doom);
void	horizontal_collision(t_doom *doom);
void	move_player(t_doom *doom, float dx, float py);
void	mouse_and_keys(t_doom *doom);
int		keys(t_doom *doom, SDL_Event *event);
void	fps_func(t_doom *doom);
int		shade_hex_color(int hex, float shade_factor);
void	floor_text(t_doom *doom, int x, int sy, int sx);
void	trigon_rasterizer(SDL_Surface *surface, t_xyz a, t_xyz b, t_xyz c);
void	ft_circle(SDL_Surface *surface, int xc, int yc, int r);
//void	render_entity(t_doom *doom, t_sector *sect, int sect_num);
void	render_entity(t_doom *doom, t_item curr);
int	BlitScaled(SDL_Surface *src, SDL_Surface *dst, t_entity e);
int	doom_pixel_copy(t_render *render, int pixel, int dst_add);

//Math wiki func
int		overlap(double a0, double a1, double b0 , double b);
int		intersect_box(t_xyz p, t_xyz d, t_xyz vert1, t_xyz vert2);
float	point_side(t_xyz p, t_xyz d, t_xyz vert1, t_xyz vert2);
t_xyz	intersect(t_xyz s[2], float x3, float y3, float x4, float y4);
int		find_sector(t_doom *doom, t_xyz e);

#endif
