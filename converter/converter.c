/*
 * https://github.com/Epicurius/Doom-Not-Doom
 * 
 * Created: 2021/04/25 13:37:21 nneronin
 * Updated: 2022/01/02 15:24:08 nneronin
 */

#include "libft.h"
#include "libpf.h"
#include "bxpm.h"

static inline int	get_path(char *path, char **name)
{
	int	len;

	len = ft_strlen(path) - 4;
	if (!ft_strequ(&path[len], ".bmp"))
		return (0);
	*name = ft_sprintf("%.*s.bxpm", len, path);
	return (1);
}

static inline void	free_converter(t_bmp *bmp, t_bxpm *bxpm, char *name)
{
	free(bxpm->clr);
	free(bxpm->pix);
	free(bmp->data);
	free(name);
	name = NULL;
	ft_memset(bxpm, 0, sizeof(t_bxpm));
	ft_memset(bmp, 0, sizeof(t_bmp));
}

static inline int	create_bxpm(char *path, t_bmp *bmp, t_bxpm *bxpm)
{
	char	*name;

	if (!get_path(path, &name))
		return (0);
	ft_printf("Reading\t\t%s ", path);
	if (!read_bmp(bmp, path))
		return (ft_printf("{RED}Error!{RESET}\n"));
	ft_printf("{GREEN}Done!{RESET}\n");
	ft_printf("Converting\t%s ", path);
	if (!bmp_to_bxpm(bmp, bxpm))
		return (ft_printf("{RED}Error!{RESET}\n"));
	ft_printf("{GREEN}Done!{RESET}\n");
	ft_printf("Writing\t\t%s ", name);
	if (!write_bxpm(bxpm, name))
		return (ft_printf("{RED}Error!{RESET}\n"));
	ft_printf("{GREEN}Done!{RESET}\n");
	ft_printf("{GREEN}Created\t\t%s.{RESET}\n", name);
	free_converter(bmp, bxpm, name);
	return (0);
}

int	main(int ac, char **av)
{
	int		i;
	char	*name;
	t_bmp	bmp;
	t_bxpm	bxpm;

	i = 0;
	if (ac == 1)
		return (0);
	while (++i < ac)
	{
		if (create_bxpm(av[i], &bmp, &bxpm))
			return (0);
	}
	return (1);
}
