# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/06/09 07:31:15 by nneronin          #+#    #+#              #
#    Updated: 2021/04/26 13:54:10 by nneronin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RED := "\e[0;31m"
GREEN := "\e[0;32m"
YELLOW := "\e[0;33m"
BLUE := "\e[0;34m"
MAGENTA := "\e[0;35m"
CYAN := "\e[0;36m"
RESET :="\e[0m"

RAW_SRC =	doom.c \
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
		reset_render_utils.c\
		movement.c\
		minimap.c\
		line.c\
		clip_line_inside_rectangle.c\
		crosshair_position.c\
		draw_crosshair.c\
		draw_bullet_holes.c\
		draw_wsprites.c\
		init_scale.c\
		clock_wsprite.c\
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
		load_bxpm.c\
		init_render.c\
		collision_detection.c\
		init_map_entity.c\

RAW_TEXTURES =	wood.bmp\
		spooky.bmp\
		alfred.bmp\
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

NAME = doom
CDIR = srcs
ODIR = obj
LIB_DIR = lib
SRCS = $(addprefix $(CDIR)/,$(RAW_SRC))
OBJ = $(addprefix $(ODIR)/,$(RAW_SRC:.c=.o))

PATH_TO_BMP =	./resources/BMP
PATH_TO_BXPM =	./resources/BXPM
PATH_TO_BBMP =	./resources/BBMP
BMP = $(addprefix $(PATH_TO_BMP)/,$(RAW_TEXTURES))
BXPM = $(addprefix $(PATH_TO_BXPM)/,$(RAW_TEXTURES:.bmp=.bxpm))
BBMP = $(addprefix $(PATH_TO_BBMP)/,$(RAW_TEXTURES:.bmp=.bbmp))

LINK_ID = "1rM2pmhjjHUMCA2Zvv6nrDSb5u5RWgc2g"
FILE_NAME = "file.tar.gz"
RESOURCES = resources

LIBS = ./lib/libft/libft.a ./lib/libpf/libpf.a ./lib/tpool/tpool.a
SDL = -I SDL2/include -L SDL2/lib -l SDL2 -l SDl2_ttf -l SDL2_image
CFLAGS = -Wall -Wextra -Werror -Wunused-variable


all: $(LIBS) $(RESOURCES) $(PATH_TO_BXPM) $(BXPM) $(ODIR) $(NAME)
	@printf $(GREEN)"~~~~~~~~ Doom is ready! ~~~~~~~~\n"$(RESET)

$(ODIR):
	@printf $(CYAN)"[INFO]	Creating folder obj.\n"$(RESET)
	@mkdir -p $@

$(NAME): $(OBJ)
	@printf $(CYAN)"[INFO]	Linking Project.\n"$(RESET)
	@gcc -o $@ $(OBJ) $(LIBS) $(SDL)


$(ODIR)/%.o: $(CDIR)/%.c
	@printf $(GREEN)"Compiling $<\n"$(RESET)
	@gcc -c $< -o $@


$(PATH_TO_BXPM)/%.bxpm: $(PATH_TO_BMP)/%.bmp
	@./bxpm_conv/bxpm_conv $<
	@mv ./resources/BMP/*.bxpm ./resources/BXPM/
	@mv ./resources/BMP/*.bbmp ./resources/BBMP/

$(LIB_DIR):
	@printf $(CYAN)"[INFO]	Cloning lib.\n"$(RESET)
	@git clone -q https://github.com/Epicurius/lib.git

$(LIBS): $(LIB_DIR)
	@make -C ./lib/libft
	@make -C ./lib/libpf
	@make -C ./lib/tpool
	@make -C ./bxpm_conv
	@printf $(CYAN)"[INFO]	All libs compiled.\n"$(RESET)

clean:
	@printf $(CYAN)"[INFO]	Deleted objects\n"$(RESET)
	@/bin/rm -rf $(ODIR)

fclean: clean
	@printf $(CYAN)"[INFO]	Deleted $(NAME)\n"$(RESET)
	@/bin/rm -f $(NAME)

fclean_all: fclean
	@printf $(CYAN)"[INFO]	Deleted BXPM and BBMP\n"$(RESET)
	@/bin/rm -rf $(PATH_TO_BXPM)/*.bxpm
	@/bin/rm -rf $(PATH_TO_BBMP)/*.bbmp

$(RESOURCES):
	@./google_drive.sh
	@printf $(CYAN)"[INFO] Unarchiving resources\n"$(RESET)
	@tar -xf file.tar.gz
	@rm -rf file.tar.gz

re: fclean all

.PHONY: clean, all, re, fclean
