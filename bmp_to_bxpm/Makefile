# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/25 13:39:16 by nneronin          #+#    #+#              #
#    Updated: 2021/06/19 18:02:50 by nneronin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RED				:= "\e[0;31m"
GREEN			:= "\e[0;32m"
YELLOW			:= "\e[0;33m"
BLUE			:= "\e[0;34m"
MAGENTA			:= "\e[0;35m"
CYAN			:= "\e[0;36m"
RESET			:= "\e[0m"

RAW_TEXTURES =	DoomScore.bmp\
				alfred.bmp\
				bars.bmp\
				bh.bmp\
				game_over.bmp\
				game_loading.bmp\
				glock-0.bmp\
				glock-1.bmp\
				glock-2.bmp\
				glock-3.bmp\
				glock-4.bmp\
				glock-5.bmp\
				kar-0.bmp\
				kar-1.bmp\
				kar-10.bmp\
				kar-11.bmp\
				kar-12.bmp\
				kar-13.bmp\
				kar-14.bmp\
				kar-15.bmp\
				kar-16.bmp\
				kar-17.bmp\
				kar-18.bmp\
				kar-19.bmp\
				kar-2.bmp\
				kar-20.bmp\
				kar-21.bmp\
				kar-22.bmp\
				kar-23.bmp\
				kar-24.bmp\
				kar-25.bmp\
				kar-26.bmp\
				kar-27.bmp\
				kar-28.bmp\
				kar-29.bmp\
				kar-3.bmp\
				kar-30.bmp\
				kar-31.bmp\
				kar-32.bmp\
				kar-33.bmp\
				kar-34.bmp\
				kar-35.bmp\
				kar-36.bmp\
				kar-37.bmp\
				kar-4.bmp\
				kar-5.bmp\
				kar-6.bmp\
				kar-7.bmp\
				kar-8.bmp\
				kar-9.bmp\
				land0.bmp\
				land1.bmp\
				land2.bmp\
				land3.bmp\
				land4.bmp\
				land5.bmp\
				minigun-0.bmp\
				minigun-1.bmp\
				minigun-2.bmp\
				minigun-3.bmp\
				minigun-4.bmp\
				minigun-5.bmp\
				objects.bmp\
				pause.bmp\
				quit.bmp\
				rift.bmp\
				shotgun-0.bmp\
				shotgun-1.bmp\
				shotgun-2.bmp\
				shotgun-3.bmp\
				shotgun-4.bmp\
				shotgun-5.bmp\
				shotgun-6.bmp\
				shotgun-7.bmp\
				shotgun-8.bmp\
				shotgun-9.bmp\
				shotgun-10.bmp\
				shotgun-11.bmp\
				shotgun-12.bmp\
				shotgun-13.bmp\
				space0.bmp\
				space1.bmp\
				space2.bmp\
				space3.bmp\
				space4.bmp\
				space5.bmp\
				spooky.bmp\
				pump-0.bmp\
				pump-1.bmp\
				pump-2.bmp\
				pump-3.bmp\
				pump-4.bmp\
				pump-5.bmp\
				pump-6.bmp\
				pump-7.bmp\
				pump-8.bmp\
				vent.bmp\
				lava.bmp\
				metal_wall.bmp\
				tile_floor.bmp\
				door.bmp\
				console.bmp\
				green_wall.bmp\
				radar.bmp\
				steel.bmp\
				wall_panel.bmp\
				metal_tile2.bmp\
				wood.bmp

RESOURCES_DIR	= ../resources
PATH_TO_BMP		= $(RESOURCES_DIR)/BMP
PATH_TO_BXPM	= $(RESOURCES_DIR)/BXPM
BMP				= $(addprefix $(PATH_TO_BMP)/,$(RAW_TEXTURES))
BXPM			= $(addprefix $(PATH_TO_BXPM)/,$(RAW_TEXTURES:.bmp=.bxpm))

NAME = converter

SRC =	converter.c

OBJ = $(SRCS:.c=.o)

INCLUDES = ../lib/libft/libft.a ../lib/libpf/libpf.a ../libbxpm/libbxpm.a

FLAGS = -Wall -Wextra -Werror

all: $(NAME)
	@printf $(CYAN)"[INFO]	$(NAME) ready!\n"$(RESET)

$(NAME): $(SRC)
	@gcc -o $(NAME) $(SRC) $(INCLUDES)
	@printf $(GREEN)"Compiling $(NAME)\n"$(RESET)

check: $(PATH_TO_BXPM) $(BXPM)

$(PATH_TO_BXPM)/%.bxpm: $(PATH_TO_BMP)/%.bmp
	@./converter $<
	@mv ../resources/BMP/*.bxpm ../resources/BXPM/

clean:
	/bin/rm -f $(OBJ)
	@printf $(CYAN)"[INFO]	$(NAME) cleaned\n"$(RESET)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

.PHONY: clean, all, re, fclean, check
