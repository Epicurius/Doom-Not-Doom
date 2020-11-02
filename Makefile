# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/06/09 07:31:15 by nneronin          #+#    #+#              #
#    Updated: 2020/11/02 14:22:03 by nneronin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = doom
DIR_S = ./srcs
INC	=	.
SRC = ./doom.c\
	  ./player_view_fustrum.c\
	  ./vertical_line.c\
	  ./player_perspective.c\
	  ./rotate_wall_sector.c\
	  ./read_map.c\
	  ./collision_detection.c\
	  ./move_player.c\
	  ./mouse_and_keys.c\
	  ./keys.c\
	  ./fps.c\
	  ./map.c\
	  ./draw2.c\
	  ./intersect_box.c\
	  ./floor.c

SRCS = $(addprefix $(DIR_S)/,$(SRC))
OBJS = ./*.o
INCLUDES = ./lib/libft/libft.a\
		   ./lib/libpf/libpf.a
FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME):
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
