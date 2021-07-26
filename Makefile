# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/06/09 07:31:15 by nneronin          #+#    #+#              #
#    Updated: 2021/07/26 10:46:37 by nneronin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SHELL_NAME	:= $(shell uname -s)

RED			:=	"\e[0;31m"
GREEN		:=	"\x1b[38;5;119m"
ORANGE		:=	"\x1b[38;5;208m"
YELLOW		:=	"\e[0;33m"
BLUE		:=	"\e[0;34m"
MAGENTA		:=	"\e[0;35m"
CYAN		:=	"\e[0;36m"
UNDERLINE	:=	"\x1b[4m"
RESET		:=	"\e[0m"

RAW_SRC		=	ai_attack.c\
				ai_movement.c\
				animate_wsprite.c\
				args.c\
				blit_bxpm.c\
				blit_entity.c\
				buy_menu.c\
				camera.c\
				clock.c\
				collision_detection.c\
				color_and_brightness.c\
				compute_vline.c\
				crosshair_position.c\
				doom.c\
				draw2.c\
				draw_bullet_holes.c\
				draw_ceiling.c\
				draw_crosshair.c\
				draw_entity.c\
				draw_floor.c\
				draw_floor_and_ceiling.c\
				draw_hud.c\
				draw_neighbor_wall.c\
				draw_portal_texture.c\
				draw_projectile.c\
				draw_skybox.c\
				draw_wall.c\
				draw_weapon.c\
				draw_wsprites.c\
				endless.c\
				error.c\
				find_sector.c\
				fps.c\
				free.c\
				free1.c\
				free2.c\
				free3.c\
				game_loading.c\
				game_over.c\
				game_pause.c\
				game_quit.c\
				get_entity_state.c\
				help.c\
				hud_utils.c\
				icon.c\
				init.c\
				init_alfred.c\
				init_barrel.c\
				init_entity.c\
				init_game_mode.c\
				init_glock.c\
				init_inventory.c\
				init_kar.c\
				init_lamp.c\
				init_meat_hook.c\
				init_minigun.c\
				init_minimap.c\
				init_player.c\
				init_pump.c\
				init_render.c\
				init_rift.c\
				init_scale.c\
				init_sdl.c\
				init_shotgun.c\
				init_slope.c\
				init_spooky.c\
				init_textures.c\
				init_torch.c\
				init_weapons.c\
				keys.c\
				line.c\
				malloc_texture_pos.c\
				map_events.c\
				math1.c\
				math2.c\
				math3.c\
				math4.c\
				math5.c\
				math6.c\
				math7.c\
				math8.c\
				minimap.c\
				movement.c\
				object_collision.c\
				orientation.c\
				parse_map_events.c\
				parse_map_header.c\
				parse_map_sector.c\
				parse_map_sprite.c\
				player_collision.c\
				precompute_buy_menu.c\
				precompute_entities.c\
				precompute_projectiles.c\
				precompute_skybox.c\
				precompute_walls.c\
				precompute_weapon.c\
				project_entity.c\
				project_wall.c\
				put_pixels.c\
				random.c\
				read_map.c\
				reload_map.c\
				skybox_ceiling_vline.c\
				skybox_floor_vline.c\
				skybox_wall_vline.c\
				sound.c\
				spawn_entity.c\
				update_screen.c\
				validate_map1.c\
				validate_map2.c\
				vertical_line.c\
				wall_to_screen_xz.c
		
NAME		=	doom
CDIR		=	srcs
ODIR		=	obj
INC			=	./inc 
SRCS		=	$(addprefix $(CDIR)/,$(RAW_SRC))
OBJ			=	$(addprefix $(ODIR)/,$(RAW_SRC:.c=.o))
DEP			:=	$(OBJ:.o=.d)

SDL_DIR		:= ./SDL
SDL_MAIN	:= -I $(SDL_DIR)/SDL2.framework/Headers -framework SDL2 -F $(SDL_DIR)
SDL_IMAGE	:= -I $(SDL_DIR)/SDL2_image.framework/Headers -framework SDL2_image -F $(SDL_DIR)
SDL_MIXER	:= -I $(SDL_DIR)/SDL2_mixer.framework/Headers -framework SDL2_mixer -F $(SDL_DIR)
SDL_TTF		:= -I $(SDL_DIR)/SDL2_ttf.framework/Headers -framework SDL2_ttf -F $(SDL_DIR)

LIB_DIR		:=	../libDoom
LIBFT		:= -I $(LIB_DIR)/libft $(LIB_DIR)/libft/libft.a
LIBPF		:= -I $(LIB_DIR)/libpf $(LIB_DIR)/libpf/libpf.a
LIBTP		:= -I $(LIB_DIR)/libtp $(LIB_DIR)/libtp/libtp.a
LIBGFX		:= -I $(LIB_DIR)/libgfx $(LIB_DIR)/libgfx/libgfx.a
LIBBXPM		:= -I $(LIB_DIR)/libbxpm $(LIB_DIR)/libbxpm/libbxpm.a
LIBUI		:= -I $(LIB_DIR)/better_libui $(LIB_DIR)/better_libui/libui.a

LIBS		+=	-I $(INC) $(SDL_MAIN) $(SDL_IMAGE) $(SDL_MIXER) $(SDL_TTF)\
				$(LIBFT) $(LIBTP) $(LIBPF) $(LIBBXPM) $(LIBUI) $(LIBGFX)

CFLAGS		=	-Wall -Wextra -Werror -Wfatal-errors

PATH_H		=	./inc/path.h

RESOURCES	=	./resources

all: framework $(RESOURCES) $(PATH_H) $(ODIR) $(NAME)

-include $(DEP)
#-04
$(ODIR):
	@printf $(CYAN)"[INFO]	Creating folder obj.\n"$(RESET)
	@mkdir -p $@

$(NAME): $(OBJ)
	@gcc $(CFLAGS) $(LIBS) $(OBJ) -o $(NAME)
	@printf $(ORANGE)$(UNDERLINE)"\e[F\e[JDoom is ready\n"$(RESET)

$(ODIR)/%.o: $(CDIR)/%.c
	@gcc -c $< -o $@ $(CFLAGS) $(LIBS) -w
	@printf $(GREEN)"\e[F\e[JCompiling $<\n"$(RESET)

#$(LIB_DIR):
#	@printf $(CYAN)"[INFO]	Cloning lib.\n"$(RESET)
#	@git clone -q https://github.com/Epicurius/lib.git

# libs: $(LIB_DIR)
#	@make -C ./lib/libft
#	@make -C ./lib/libpf
#	@make -C ./lib/libtp
#	@make -C ./libbxpm
#	@make -C ./bmp_to_bxpm
#	@printf $(CYAN)"[INFO]	All libs compiled.\n"$(RESET)

clean:
	@printf $(CYAN)"[INFO]	Deleted objects\n"$(RESET)
	@rm -rf $(ODIR)

fclean: clean
	@printf $(CYAN)"[INFO]	Deleted $(NAME)\n"$(RESET)
	@rm -f $(NAME)

$(RESOURCES):
	@./google_drive.sh
	@tar -xf file.tar.gz
	@rm -rf file.tar.gz

$(PATH_H):
	@printf $(CYAN)"[INFO]	Creating path.h\n"$(RESET)
	@gcc -o find_path ./Get_Path/path.c
	@./find_path
	@mv path.h ./inc/
	@rm -f find_path

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
