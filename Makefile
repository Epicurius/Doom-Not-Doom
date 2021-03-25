# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/06/09 07:31:15 by nneronin          #+#    #+#              #
#    Updated: 2020/11/24 12:13:57 by nneronin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = doom
DIR_S = ./srcs
SRC =	./doom.c\
	./read_map.c\
	./find_sector.c\
	./utility_math.c\
	./vertical_line.c\
	./project_wall.c\
	./wall_to_screen_xz.c\
	./keys.c\
	./fps.c\
	./draw2.c\
	./camera.c\
	./draw_ceiling.c\
	./draw_floor_and_ceiling.c\
	./draw_floor.c\
	./draw_wall.c\
	./draw_portal_texture.c\
	./draw_neighbor_wall.c\
	./color_and_brightness.c\
	./precompute_walls.c\
	./precompute_skybox.c\
	./find_start_sectors.c\
	./zbuffer_utils.c\
	./draw_entity.c\
	./load_textures.c\
	./draw_skybox.c\
	./skybox_wall_vline.c\
	./skybox_ceiling_vline.c\
	./skybox_floor_vline.c\
	./reset_arrays.c\
	./vertical_collision.c\
	./horizontal_collision.c\
	./movement.c\
	./minimap.c\
	./line.c\
	./clip_line_inside_rectangle.c\
	./crosshair_position.c\
	./draw_crosshair.c\
	./draw_bullet_holes.c\
	./draw_wsprites.c\
	./init_scale.c\
	./clock_wsprite.c\
	./animate_wsprites.c\
	./precompute_entities.c\
	./orientation.c\
	./melee_ai.c\
	./init_alfred.c\

SRCS = $(addprefix $(DIR_S)/,$(SRC))
OBJS = ./*.o
INCLUDES = ./lib/libft/libft.a\
		./lib/libpf/libpf.a\
		./lib/tpool/tpool.a

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(SRCS)
	@gcc -o $(NAME) $(SRCS) $(INCLUDES) -I SDL2/include -L SDL2/lib -l SDL2-2.0.0 -l SDl2_ttf-2.0.0 -l SDL2_image-2.0.0
	@echo "$(NAME) was created."
clean:
	/bin/rm -f $(OBJS)
	#make -C ./libft/ clean
fclean: clean
	/bin/rm -f $(NAME)
	#make -C ./libft/ fclean

re: fclean all

.PHONY: clean, all, re, fclean
