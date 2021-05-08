# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/06/09 07:31:15 by nneronin          #+#    #+#              #
#    Updated: 2021/05/08 12:47:10 by nneronin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SHELL_NAME	:= $(shell uname -s)

RED				:= "\e[0;31m"
GREEN			:= "\e[0;32m"
YELLOW			:= "\e[0;33m"
BLUE			:= "\e[0;34m"
MAGENTA			:= "\e[0;35m"
CYAN			:= "\e[0;36m"
RESET			:= "\e[0m"

RAW_TEXTURES =	wood.bmp\
				spooky.bmp\
				alfred.bmp\
				rift.bmp\
				bh.bmp\
				vent.bmp\
				bars.bmp\
				space0.bmp\
				space1.bmp\
				space2.bmp\
				space3.bmp\
				space4.bmp\
				space5.bmp\
				land0.bmp\
				land1.bmp\
				land2.bmp\
				land3.bmp\
				land4.bmp\
				land5.bmp\
				shot1.bmp\
				shot2.bmp\
				shot3.bmp\
				shot4.bmp\
				shot5.bmp\
				shot6.bmp\
				shot7.bmp\
				shot8.bmp\
				shot9.bmp\
				shot10.bmp\
				shot11.bmp\
				shot12.bmp\
				shot13.bmp\
				shot14.bmp\
				shot15.bmp\
				gun1.bmp\
				gun2.bmp\
				gun3.bmp\
				gun4.bmp\
				gun5.bmp\
				gun6.bmp\
				mini1.bmp\
				mini2.bmp\
				mini3.bmp\
				mini4.bmp\
				mini5.bmp\
				mini6.bmp

RESOURCES_DIR	= ./resources
PATH_TO_BMP		= $(RESOURCES_DIR)/BMP
PATH_TO_BXPM	= $(RESOURCES_DIR)/BXPM
BMP				= $(addprefix $(PATH_TO_BMP)/,$(RAW_TEXTURES))
BXPM			= $(addprefix $(PATH_TO_BXPM)/,$(RAW_TEXTURES:.bmp=.bxpm))

RAW_SRC =		doom.c\
				put_pixels.c \
				read_map.c\
				init_textures.c\
				find_sector.c\
				utility_math.c\
				vertical_line.c\
				project_wall.c\
				wall_to_screen_xz.c\
				keys.c\
				fps.c\
				draw2.c\
				camera.c\
				draw_ceiling.c\
				draw_floor_and_ceiling.c\
				draw_floor.c\
				draw_wall.c\
				draw_portal_texture.c\
				draw_neighbor_wall.c\
				color_and_brightness.c\
				precompute_walls.c\
				precompute_skybox.c\
				find_start_sectors.c\
				draw_entity.c\
				draw_skybox.c\
				skybox_wall_vline.c\
				skybox_ceiling_vline.c\
				skybox_floor_vline.c\
				movement.c\
				minimap.c\
				line.c\
				clip_line_inside_rectangle.c\
				crosshair_position.c\
				draw_crosshair.c\
				draw_bullet_holes.c\
				draw_wsprites.c\
				init_scale.c\
				animate_wsprites.c\
				precompute_entities.c\
				orientation.c\
				ai_movement.c\
				init_entity.c\
				ai_attack.c\
				ai_rand.c\
				free.c\
				precompute_projectiles.c\
				draw_projectile.c\
				blit_entity.c\
				player_collision.c\
				object_collision.c\
				init_alfred.c\
				init_spooky.c\
				init_rift.c\
				load_bxpm.c\
				init_render.c\
				collision_detection.c\
				parse_map_sprite.c\
				parse_map_header.c\
				parse_map_sector.c\
				read_bxpm.c\
				clock.c\
				init_player.c\
				surf_to_bxpm.c\
				blit_bxpm.c\
				wave.c\
				weapon_animation.c\
				malloc_texture_pos.c\
				debug_loop.c\
				sound.c
		
NAME			= doom
CDIR			= srcs
ODIR			= obj
SRCS			= $(addprefix $(CDIR)/,$(RAW_SRC))
OBJ				= $(addprefix $(ODIR)/,$(RAW_SRC:.c=.o))
DEP				:= $(OBJ:.o=.d)

SDL_DIR			:= ./SDL
SDL_MAIN		:= -I $(SDL_DIR)/SDL2.framework/Headers -framework SDL2 -F $(SDL_DIR)
SDL_IMAGE		:= -I $(SDL_DIR)/SDL2_image.framework/Headers -framework SDL2_image -F $(SDL_DIR)
SDL_MIXER		:= -I $(SDL_DIR)/SDL2_mixer.framework/Headers -framework SDL2_mixer -F $(SDL_DIR)
SDL_TTF			:= -I $(SDL_DIR)/SDL2_ttf.framework/Headers -framework SDL2_ttf -F $(SDL_DIR)

LIB_DIR			:= ./lib
LIBFT			:= -I $(LIB_DIR)/libft $(LIB_DIR)/libft/libft.a
LIBPF			:= -I $(LIB_DIR)/libpf $(LIB_DIR)/libpf/libpf.a
LIBTP			:= -I $(LIB_DIR)/libtp $(LIB_DIR)/libtp/libtp.a

LIBS			+= $(SDL_MAIN) $(SDL_IMAGE) $(SDL_MIXER) $(SDL_TTF) $(LIBFT) $(LIBTP) $(LIBPF)
CFLAGS			= -Wall -Wextra -Werror -Wunused-variable -Wno-unused-result


all: framework libs resources $(PATH_TO_BXPM) $(BXPM) $(ODIR) $(NAME)

-include $(DEP)

$(ODIR):
	@printf $(CYAN)"[INFO]	Creating folder obj.\n"$(RESET)
	@mkdir -p $@

$(NAME): $(OBJ)
	@printf $(CYAN)"[INFO]	Linking Project.\n"$(RESET)
	@gcc -o $(NAME) $(LIBS) $(OBJ) $(CFLAGS) 

$(ODIR)/%.o: $(CDIR)/%.c
	@printf $(GREEN)"Compiling $<\n"$(RESET)
	@gcc $(LIBS) $(CFLAGS) -w -c $< -o $@

$(PATH_TO_BXPM)/%.bxpm: $(PATH_TO_BMP)/%.bmp
	@./bmp_to_bxpm/converter $<
	@mv ./resources/BMP/*.bxpm ./resources/BXPM/

$(LIB_DIR):
	@printf $(CYAN)"[INFO]	Cloning lib.\n"$(RESET)
	@git clone -q https://github.com/Epicurius/lib.git

libs: $(LIB_DIR)
	@make -C ./lib/libft
	@make -C ./lib/libpf
	@make -C ./lib/libtp
	@make -C ./bmp_to_bxpm
	@printf $(CYAN)"[INFO]	All libs compiled.\n"$(RESET)

clean:
	@printf $(CYAN)"[INFO]	Deleted objects\n"$(RESET)
	@/bin/rm -rf $(ODIR)

fclean: clean
	@printf $(CYAN)"[INFO]	Deleted $(NAME)\n"$(RESET)
	@/bin/rm -f $(NAME)

resources: $(RESOURCES)
	@./google_drive.sh
	@tar -xf file.tar.gz
	@rm -rf file.tar.gz

framework:
ifeq ($(SHELL_NAME), Darwin)
	@mkdir -p ~/Library/Frameworks	
ifeq ("$(wildcard ~/Library/Frameworks/SDL2*.framework)","")
	@cp -Rf $(SDL_DIR)/SDL2.framework ~/Library/Frameworks/
	@cp -Rf $(SDL_DIR)/SDL2_ttf.framework ~/Library/Frameworks/
	@cp -Rf $(SDL_DIR)/SDL2_image.framework ~/Library/Frameworks/
	@cp -Rf $(SDL_DIR)/SDL2_mixer.framework ~/Library/Frameworks/
	@printf $(CYAN)"[INFO]	Moving Frameworks\n"$(RESET)
else
	@printf $(CYAN)"[INFO]	Frameworks Exists\n"$(RESET)
endif
endif

framework_del:
	@rm -rf ~/Library/Frameworks/SDL2*.framework
	@printf $(CYAN)"[INFO]	Deleted SDL2 Frameworks from ~/Library/Frameworks\n"$(RESET)

framework_re: framework_del
	@cp -Rf $(SDL_DIR)/SDL2.framework ~/Library/Frameworks/
	@cp -Rf $(SDL_DIR)/SDL2_ttf.framework ~/Library/Frameworks/
	@cp -Rf $(SDL_DIR)/SDL2_image.framework ~/Library/Frameworks/
	@cp -Rf $(SDL_DIR)/SDL2_mixer.framework ~/Library/Frameworks/
	@printf $(CYAN)"[INFO]	Mooving SDL2 Frameworks to ~/Library/Frameworks\n"$(RESET)

re: framework_re fclean all

.PHONY: clean, all, re, fclean, resources, framework, framework_del, frameworks_re
