/*
 * https://github.com/Epicurius/Doom-Not-Doom
 * 
 * Created: 2021/07/14 13:38:47 nneronin
 * Updated: 2022/01/18 13:10:46 Niklas Neronin
 */

#include "doom.h"

/*
 *	Check if the argument is window size(int,int)
 *	or mouse sensitivity(float,float).
 */
static void	read_args2(t_settings *init, char **av, int i)
{
	char	**arr;

	if (ft_strnequ(av[i], "-size=", 6))
	{
		arr = stringsplit(av[i] + 6, 'x', NULL);
		init->size = (t_point){ft_atoi(arr[0]), ft_atoi(arr[1])};
		free(arr);
	}
	else if (ft_strnequ(av[i], "-mouse=", 7))
	{
		arr = stringsplit(av[i] + 7, 'x', NULL);
		init->mouse = (t_v2){ft_atof(arr[0]), ft_atof(arr[1])};
		free(arr);
	}
}

/*
 *	Check is the argument is debug(bool), launcher(bool),
 *	render resolution(float), game difficulty(int) or FOV(int).	
 */
static int	read_args1(t_settings *init, char **av, int i)
{
	if (ft_strequ(av[i], "-debug"))
		init->debug = TRUE;
	else if (ft_strequ(av[i], "-launcher"))
		init->launcher = TRUE;
	else if (ft_strnequ(av[i], "-res=", 5))
		init->rres = ft_atof(av[i] + 5);
	else if (ft_strnequ(av[i], "-diff=", 6))
		init->difficulty = ft_atoi(av[i] + 6);
	else if (ft_strnequ(av[i], "-fov=", 5))
		init->fov = ft_atoi(av[i] + 5);
	else
		read_args2(init, av, i);
	return (1);
}

/*
 *	Give settings there presets, and changes them depending
 *	on the give arguments.
 */
void	args(int ac, char **av, t_settings *init)
{
	int	i;

	i = TRUE;
	ft_bzero(init, sizeof(t_settings));
	init->size = (t_point){1920, 1080};
	init->rres = 1.0f;
	init->mouse = (t_v2){MOUSE_X, MOUSE_Y};
	init->fov = FOV;
	while (++i < ac)
		read_args1(init, av, i);
	if (init->debug)
		LG_WARN("%s\nScreen Size\t\t%dx%d\nRender Resolution\t%.2f\n"
			"Mouse Sensitivity\t%.3fx%.3f\nGame Difficulty\t\t"
			"%d\nFOV\t\t\t%d\nDebug Mode\t\t%d\nLauncher\t\t%d",
			av[1], init->size.x, init->size.y, init->rres,
			init->mouse.x, init->mouse.y, init->difficulty,
			init->fov, init->debug, init->launcher);
}
