# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/25 13:39:16 by nneronin          #+#    #+#              #
#    Updated: 2021/08/04 12:58:25by nneronin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RED				:=	"\e[0;31m"
GREEN			:=	"\e[0;32m"
YELLOW			:=	"\e[0;33m"
BLUE			:=	"\e[0;34m"
MAGENTA			:=	"\e[0;35m"
CYAN			:=	"\e[0;36m"
RESET			:=	"\e[0m"

GAME			=	alfred.bmp\
					bars.bmp\
					bullet_hole.bmp\
					clock.bmp\
					cog.bmp\
					compwall.bmp\
					console.bmp\
					door.bmp\
					fiber_wall.bmp\
					ghost.bmp\
					green_wall.bmp\
					lava.bmp\
					metal_tile2.bmp\
					metal_wall.bmp\
					objects.bmp\
					radar.bmp\
					rift.bmp\
					rock.bmp\
					spooky.bmp\
					steel_tile1.bmp\
					steel_tile2.bmp\
					steel_tlight.bmp\
					terminal.bmp\
					tile_floor.bmp\
					vent.bmp\
					wall_button.bmp\
					wires.bmp

SKYBOX			=	cosmos-0.bmp\
					cosmos-1.bmp\
					cosmos-2.bmp\
					cosmos-3.bmp\
					cosmos-4.bmp\
					cosmos-5.bmp\
					land-0.bmp\
					land-1.bmp\
					land-2.bmp\
					land-3.bmp\
					land-4.bmp\
					land-5.bmp\
					space-0.bmp\
					space-1.bmp\
					space-2.bmp\
					space-3.bmp\
					space-4.bmp\
					space-5.bmp

WEAPON			=	glock-0.bmp\
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
					launcher-0.bmp\
					launcher-1.bmp\
					launcher-10.bmp\
					launcher-11.bmp\
					launcher-12.bmp\
					launcher-13.bmp\
					launcher-2.bmp\
					launcher-3.bmp\
					launcher-4.bmp\
					launcher-5.bmp\
					launcher-6.bmp\
					launcher-7.bmp\
					launcher-8.bmp\
					launcher-9.bmp\
					minigun-0.bmp\
					minigun-1.bmp\
					minigun-2.bmp\
					minigun-3.bmp\
					minigun-4.bmp\
					minigun-5.bmp\
					shotgun-0.bmp\
					shotgun-1.bmp\
					shotgun-10.bmp\
					shotgun-11.bmp\
					shotgun-12.bmp\
					shotgun-13.bmp\
					shotgun-2.bmp\
					shotgun-3.bmp\
					shotgun-4.bmp\
					shotgun-5.bmp\
					shotgun-6.bmp\
					shotgun-7.bmp\
					shotgun-8.bmp\
					shotgun-9.bmp
				
TEXT			=	game_over.bmp\
					loading.bmp\
					pause.bmp\
					quit.bmp

ICON			=	ammo_patrons.bmp\
					armour_shield.bmp\
					cash_dosh.bmp\
					health_heart.bmp\
					mag_ammo.bmp

RESOURCES_DIR	=	../resources
PATH_TO_BXPM	=	$(RESOURCES_DIR)/BXPM
PATH_TO_BMP		=	$(RESOURCES_DIR)/GAME

BMP				= 	$(addprefix $(RESOURCES_DIR)/GAME/,$(GAME)) \
					$(addprefix $(RESOURCES_DIR)/SKYBOX/,$(SKYBOX)) \
					$(addprefix $(RESOURCES_DIR)/WEAPONS/,$(WEAPON)) \
					$(addprefix $(RESOURCES_DIR)/TEXT/,$(TEXT)) \
					$(addprefix $(RESOURCES_DIR)/ICON/,$(ICON))

BXPM			= 	$(addprefix $(RESOURCES_DIR)/BXPM/,$(GAME:.bmp=.bxpm)) \
					$(addprefix $(RESOURCES_DIR)/BXPM/,$(SKYBOX:.bmp=.bxpm)) \
					$(addprefix $(RESOURCES_DIR)/BXPM/,$(WEAPON:.bmp=.bxpm)) \
					$(addprefix $(RESOURCES_DIR)/BXPM/,$(TEXT:.bmp=.bxpm)) \
					$(addprefix $(RESOURCES_DIR)/BXPM/,$(ICON:.bmp=.bxpm))

NAME = converter

SRC =	converter.c

OBJ = $(SRCS:.c=.o)

INCLUDES = 	-I ../../libs/libft ../../libs/libft/libft.a\
			-I ../../libs/libpf ../../libs/libpf/libpf.a\
			-I ../../libs/libbxpm ../../libs/libbxpm/libbxpm.a

FLAGS = -Wall -Wextra -Werror

all: $(NAME)
	@printf $(CYAN)"[INFO]	$(NAME) is up to date!\n"$(RESET)

$(NAME): $(SRC)
	@gcc -o $(NAME) $(SRC) $(INCLUDES)
	@printf $(GREEN)"Compiling $(NAME)\n"$(RESET)

check: $(PATH_TO_BXPM) $(BXPM)

$(PATH_TO_BXPM)/%.bxpm: $(PATH_TO_BMP)/%.bmp
	@./converter $<
	@mv ../resources/GAME/*.bxpm ../resources/BXPM
$(PATH_TO_BXPM)/%.bxpm: $(RESOURCES_DIR)/SKYBOX/%.bmp
	@./converter $<
	@mv ../resources/SKYBOX/*.bxpm ../resources/BXPM
$(PATH_TO_BXPM)/%.bxpm: $(RESOURCES_DIR)/WEAPONS/%.bmp
	@./converter $<
	@mv ../resources/WEAPONS/*.bxpm ../resources/BXPM
$(PATH_TO_BXPM)/%.bxpm: $(RESOURCES_DIR)/TEXT/%.bmp
	@./converter $<
	@mv ../resources/TEXT/*.bxpm ../resources/BXPM
$(PATH_TO_BXPM)/%.bxpm: $(RESOURCES_DIR)/ICON/%.bmp
	@./converter $<
	@mv ../resources/ICON/*.bxpm ../resources/BXPM

clean:
	@rm -f $(OBJ)
	@printf $(CYAN)"[INFO]	$(NAME) cleaned\n"$(RESET)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: clean, all, re, fclean, check
