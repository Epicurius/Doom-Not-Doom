/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 12:30:18 by nneronin          #+#    #+#             */
/*   Updated: 2020/11/26 13:59:37 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

typedef	struct	s_i2
{
	int	x;
	int	y;
}		t_i2;

typedef	struct	s_v2
{
	double x;
	double y;
}		t_v2;

typedef struct	s_xyz
{
	double	x;
	double	y;
	double	z;
}		t_xyz;

typedef struct	s_rect
{
	int	x1;
	int	y1;
	int	x2;
	int	y2;
	int	w;
	int	h;
	double	ratio;
}		t_rect;

typedef	struct	s_limits
{
	int	min;
	int	max;
}		t_limits;

typedef struct	s_texture
{
	SDL_Surface *surface;
	double	ratio;
	int	nb;
	int	x;
	int 	y;
	int	w;
	int	h;
}		t_texture;

typedef struct s_item
{
	int sectorno;
	int sx1;
	int sx2;
}				t_item;

typedef struct		s_plane
{
	double		y;
	int		tx;
	double		correct;
	double		head;
	double		feet;
	double		scale;
}			t_plane;

typedef	struct		s_keys
{
	int		chr;
	short		num;
	int		fnc;
	int		w;
	int		a;
	int		s;
	int		d;
	int		t;
	int		p;
	int		space;
	int		l_ctrl;
	int		l_shift;
	int		tab;
}					t_keys;

#endif
