# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/06/09 07:31:15 by nneronin          #+#    #+#              #
#    Updated: 2021/05/26 21:09:25 by nneronin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#https://stackoverflow.com/questions/47762070/makefile-optimization-for-quickly-compiling-a-library-as-quickly-as-possible

SHELL_NAME	:= $(shell uname -s)

RED				:= "\e[0;31m"
GREEN			:= "\e[0;32m"
YELLOW			:= "\e[0;33m"
BLUE			:= "\e[0;34m"
MAGENTA			:= "\e[0;35m"
CYAN			:= "\e[0;36m"
RESET			:= "\e[0m"

RAW_SRC =		doom.c\
				error.c\
				put_pixels.c \
				read_map.c\
				init_textures.c\
				find_sector.c\
				math.c\
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
				draw_entity.c\
				draw_skybox.c\
				skybox_wall_vline.c\
				skybox_ceiling_vline.c\
				skybox_floor_vline.c\
				movement.c\
				minimap.c\
				game_pause.c\
				game_quit.c\
				game_over.c\
				line.c\
				cohen_sutherland.c\
				crosshair_position.c\
				hud.c\
				init_inv.c\
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
				clock.c\
				init_player.c\
				blit_bxpm.c\
				draw_weapon.c\
				wave.c\
				precompute_weapon.c\
				malloc_texture_pos.c\
				debug_loop.c\
				sound.c\
				validate_map.c\
				init_weapons.c\
				icon.c\
				update_screen.c\
				init_barrel.c\
				init_lamp.c\
				init_torch.c\
				init_meat_hook.c\
				convert.c\
				random.c
		
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
LIBBXPM			:= -I $(LIB_DIR)/libbxpm $(LIB_DIR)/libbxpm/libbxpm.a

LIBS			+= $(SDL_MAIN) $(SDL_IMAGE) $(SDL_MIXER) $(SDL_TTF) $(LIBFT) $(LIBTP) $(LIBPF) $(LIBBXPM)
CFLAGS			= -Wall -Wextra -Werror -Wunused-variable -Wno-unused-result


all: framework libs resources $(ODIR) $(NAME)

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

$(LIB_DIR):
	@printf $(CYAN)"[INFO]	Cloning lib.\n"$(RESET)
	@git clone -q https://github.com/Epicurius/lib.git

libs: $(LIB_DIR)
	@make -C ./lib/libft
	@make -C ./lib/libpf
	@make -C ./lib/libtp
	@make -C ./lib/libbxpm
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
	@/bin/rm -f $(NAME)
	@printf $(CYAN)"[INFO]	Deleted SDL2 Frameworks from ~/Library/Frameworks\n"$(RESET)

framework_re: framework_del
	@cp -Rf $(SDL_DIR)/SDL2.framework ~/Library/Frameworks/
	@cp -Rf $(SDL_DIR)/SDL2_ttf.framework ~/Library/Frameworks/
	@cp -Rf $(SDL_DIR)/SDL2_image.framework ~/Library/Frameworks/
	@cp -Rf $(SDL_DIR)/SDL2_mixer.framework ~/Library/Frameworks/
	@printf $(CYAN)"[INFO]	Mooving SDL2 Frameworks to ~/Library/Frameworks\n"$(RESET)

re: fclean all

.PHONY: clean, all, re, fclean, resources, framework, framework_del, frameworks_re
