/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DOOM.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 11:28:34 by nneronin          #+#    #+#             */
/*   Updated: 2020/10/27 16:28:14 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_H
# define DOOM_H

# include "../lib/libft/libft.h"
# include "../lib/libpf/ft_printf.h"
# include "../SDL2/includes/SDL.h"
# include "../SDL2/includes/SDL_ttf.h"
# include "../SDL2/includes/SDL_image.h"
# include "./macros.h"
# include <math.h>
# include <pthread.h>
# include <fcntl.h>



#define min(a,b)			(((a) < (b)) ? (a) : (b)) // min: Choose smaller of two scalars.
#define max(a,b)			(((a) > (b)) ? (a) : (b)) // max: Choose greater of two scalars.
#define clamp(a, mi,ma)		min(max(a,mi),ma)         // clamp: Clamp value into set range.
#define vxs(x0,y0, x1,y1)	((x0)*(y1) - (x1)*(y0))   // vxs: Vector cross product
#define Yaw(y,z)			(y + z * doom->player.yaw)		//Project our ceiling & floor heights into screen coordinates (Y coordinate)

typedef struct s_item
{
    int sectorno;
	int	sx1;
	int sx2;
}				t_item;

typedef struct	s_xyz
{
	float	x;
	float	y;
	float	z;
}				t_xyz;

typedef struct	s_ab
{
	int			a1;
	int			a2;
	int			b1;
	int			b2;
}				t_ab;

typedef struct	s_scale
{
	float		xscale1;
	float		yscale1;
	float		xscale2;
	float		yscale2;
	int			x1;
	int			x2;
}				t_scale;

typedef struct	s_height_info
{
	float		yceil;
	float		yfloor;
	float		nyceil;
	float		nyfloor;
	t_ab		y;
	t_ab		ny;
}				t_height_info;

typedef struct	s_sector
{
    float		floor;//
	float		ceil;//
    signed char *neighbors;//
    unsigned	npoints;//
    t_xyz		*vertex;//
	t_xyz		viewed_sectors[2];
	t_scale		viewpoint;
} 				t_sector;

typedef struct	s_player
{
    t_xyz		where;
    t_xyz		velocity;
    float		angle;
	float		anglesin;
	float		anglecos;
	float 		yaw;
    unsigned	sector;
	int 		moving;
	int			falling;
	int			ground;
	int			ducking;
}				t_player;

typedef	struct		s_keys
{
	int				w;
	int				a;
	int				s;
	int				d;
	int				space;
	int				c;
	int 			t;
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

typedef struct		s_doom
{
	int					quit;
	char				*file;
	SDL_Window			*win;
	SDL_Surface			*surface;
	SDL_Event			event;

	t_xyz				*vert;//is redundant after secotors are created
	unsigned			num_sector;
	t_sector			*sectors;
	unsigned			num_sectors;
	t_player			player;
	t_height_info		height_info;
	int					start_x;
	int					end_x;
	t_keys				key;
	float				yaw;
	t_fps				fps;
	SDL_Surface			*txtx;
	SDL_Surface			*txtx1;
	SDL_Surface			*txtx2;
	int					affine_x;
	short				ytop[W];
	short				ybottom[W];
	int					u0;
	int					u1;

}						t_doom;

typedef	struct			s_wall_scale
{
	int					result;
	int					bop;
	int					fd;
	int					ca;
	int					cache;
}						t_wall_scale;


void	player_view_fustrum(t_doom *doom, t_xyz sect_xz[2]);
void	vline(t_doom *doom, int x, int y1, int y2);
void	t_vline(t_doom *doom, int x, int y1, int y2, t_wall_scale ty);
void	t_vline1(t_doom *doom, int x, t_ab y, t_ab cy);
void	rotate_wall_sector(t_sector *sect, int s, t_player *player, t_xyz t[2]);
void	player_perspective_tranformation(t_scale *persp, t_xyz t[2]);
void	DrawScreen(t_doom *doom);
void	DrawMap(t_doom *doom);
void	sector_behind_edge(t_doom *doom, int x, int neighbor, int z);
void	render_wall(t_doom *doom, t_item now, int neighbor);
void	floor_ceiling_heights(t_doom *doom, int neighbor, t_sector *sect);
void	draw_sector(t_doom *doom, t_item *queue, t_item **head, t_item *tail, t_item curr);
int		read_file(t_doom *doom, char *file_name);
void	vertical_collision(t_doom *doom);
void	horizontal_collision(t_doom *doom);
void	move_player(t_doom *doom, float dx, float py);
void	mouse_and_keys(t_doom *doom);
int		keys(t_doom *doom, SDL_Event *event);
void	fps_func(t_doom *doom);
int		scale_next(t_wall_scale *s);

//Math wiki func
int		overlap(double a0, double a1, double b0 , double b);
int		intersect_box(t_xyz p, t_xyz d, t_xyz vert1, t_xyz vert2);
float	point_side(t_xyz p, t_xyz d, t_xyz vert1, t_xyz vert2);
t_xyz	intersect(t_xyz s[2], float x3, float y3, float x4, float y4);

#endif
