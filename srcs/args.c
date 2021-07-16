/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 13:38:47 by nneronin          #+#    #+#             */
/*   Updated: 2021/07/16 16:38:33 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	read_args2(t_settings *init, char **av, int *i)
{
	char	**arr;

	if (ft_strnequ(av[*i], "-size", 5))
	{
		arr = ft_strsplit(av[*i += 1], 'x', NULL);
		init->size = (t_point){atoi(arr[0]), atoi(arr[1])};
		free(arr);
	}
	else if (ft_strnequ(av[*i], "-mouse", 5))
	{
		arr = ft_strsplit(av[*i += 1], 'x', NULL);
		init->mouse = (t_v2){atof(arr[0]), atof(arr[1])};
		free(arr);
	}
}

static int	read_args1(t_settings *init, char **av, int *i)
{
	if (ft_strequ(av[*i], "-debug"))
		init->debug = 1;
	else if (ft_strequ(av[*i], "-laucher"))
		init->launcher = 1;
	else if (!av[*i + 1])
		return ((*i += 1));
	else if (ft_strnequ(av[*i], "-res", 4))
		init->render_resolution = atof(av[*i += 1]);
	else if (ft_strnequ(av[*i], "-diff", 5))
		init->difficulty = atoi(av[*i += 1]);
	else if (ft_strnequ(av[*i], "-fov", 4))
		init->fov = atoi(av[*i += 1]);
	else
		read_args2(init, av, i);
	return (1);
}

void	args(int ac, char **av, t_settings *init)
{
	int	i;

	i = 1;
	ft_bzero(init, sizeof(init));
	init->size = (t_point){1920, 1080};
	init->render_resolution = 1;
	init->mouse = (t_v2){MOUSE_X, MOUSE_Y};
	init->fov = FOV;
	while (++i < ac)
		read_args1(init, av, &i);
	if (init->debug)
		printf("-size %dx%d\n-res %f\n-mouse %.3fx%.3f\n-diff"
			"%d\n-fov %d\n-debif %d\n-launcher %d\n",
			init->size.x, init->size.y,
			init->render_resolution,
			init->mouse.x, init->mouse.y,
			init->difficulty,
			init->fov,
			init->debug,
			init->launcher);
}
