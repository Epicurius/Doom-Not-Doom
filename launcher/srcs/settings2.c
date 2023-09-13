/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Authors: Jony Salmi <jony.salmi@gmail.com>
 *          Niklas Neronin <niklas.neronin@gmail.com>
 */

#include "launcher.h"

void	set_setting(char **farr, t_settings *settings)
{
	if (!farr[0] || !farr[1])
		return ;
	if (ft_strequ(farr[0], "fov"))
		settings->fov = ft_atoi(farr[1]);
	else if (ft_strequ(farr[0], "mouse_x"))
		settings->mouse_x = ft_atoi(farr[1]);
	else if (ft_strequ(farr[0], "mouse_y"))
		settings->mouse_y = ft_atoi(farr[1]);
	else if (ft_strequ(farr[0], "texture_scale"))
		settings->texture_scale = ft_atoi(farr[1]);
	else if (ft_strequ(farr[0], "developer"))
		settings->developer = ft_atoi(farr[1]);
	else if (ft_strequ(farr[0], "width"))
		settings->width = ft_atoi(farr[1]);
	else if (ft_strequ(farr[0], "height"))
		settings->height = ft_atoi(farr[1]);
	else if (ft_strequ(farr[0], "difficulty"))
		settings->difficulty = ft_atoi(farr[1]);
}

void	get_settings_from_file(char *file, t_settings *settings)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return ;
	while (get_next_line(fd, &line))
		set_setting(ft_strsplit(line, ' '), settings);
	free(line);
	close(fd);
}

void	set_settings_to_file(char *file, t_settings *settings)
{
	int		fd;

	fd = open(file, O_CREAT | O_RDWR);
	if (fd < 0)
		return ;
	ft_dprintf(fd,
			"fov %d\n"
			"mouse_x %d\n"
			"mouse_y %d\n"
			"texture_scale %d\n"
			"developer %d\n"
			"width %d\n"
			"height %d\n"
			"difficulty %d\n",
			settings->fov,
			settings->mouse_x,
			settings->mouse_y,
			settings->texture_scale,
			settings->developer,
			settings->width,
			settings->height,
			settings->difficulty);
	close(fd);
}