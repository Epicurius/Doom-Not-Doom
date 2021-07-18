/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 13:38:47 by nneronin          #+#    #+#             */
/*   Updated: 2021/07/18 14:25:52 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	read_args2(t_settings *init, char **av, int i)
{
	char	**arr;

	if (ft_strnequ(av[i], "-size=", 6))
	{
		arr = ft_strsplit(av[i] + 6, 'x', NULL);
		init->size = (t_point){atoi(arr[0]), atoi(arr[1])};
		free(arr);
	}
	else if (ft_strnequ(av[i], "-mouse=", 7))
	{
		arr = ft_strsplit(av[i] + 7, 'x', NULL);
		init->mouse = (t_v2){atof(arr[0]), atof(arr[1])};
		free(arr);
	}
}

static int	read_args1(t_settings *init, char **av, int i)
{
	char	**arr;
	
	if (ft_strequ(av[i], "-debug"))
		init->debug = 1;
	else if (ft_strequ(av[i], "-launcher"))
		init->launcher = 1;
	else if (ft_strnequ(av[i], "-res=", 5))
		init->render_resolution = atof(av[i] + 5);
	else if (ft_strnequ(av[i], "-diff=", 6))
		init->difficulty = atoi(av[i] + 6);
	else if (ft_strnequ(av[i], "-fov=", 5))
		init->fov = atoi(av[i] + 5);
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
		read_args1(init, av, i);
	if (init->debug)
		printf("%s\n-size %dx%d\n-res %f\n-mouse %.3fx%.3f\n-diff"
			"%d\n-fov %d\n-debug %d\n-launcher %d\n",
			av[1],
			init->size.x, init->size.y,
			init->render_resolution,
			init->mouse.x, init->mouse.y,
			init->difficulty,
			init->fov,
			init->debug,
			init->launcher);
}
