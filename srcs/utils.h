/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 12:30:18 by nneronin          #+#    #+#             */
/*   Updated: 2021/05/27 18:22:48 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

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

typedef struct		s_plane
{
	int		tx;
	double		y;
	double		correct;
	double		head;
	double		feet;
	double		scale;
}			t_plane;

typedef	struct		s_keys
{
	int		chr;
	int		fnc;
	int		w;
	int		a;
	int		s;
	int		d;
	int		t;
	int		p;
	int		r;
	int		space;
	int		ctr_l;
	int		shift_l;
	int		lmouse;
	int		tab;
	int		num;
}					t_keys;

#endif
