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
		load_textures.c\
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
		zbuffer_utils.c\
		draw_entity.c\
		draw_skybox.c\
		skybox_wall_vline.c\
		skybox_ceiling_vline.c\
		skybox_floor_vline.c\
		reset_arrays.c\
		vertical_collision.c\
		horizontal_collision.c\
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
		init_entity_stats.c\
		ai_attack.c\
		ai_rand.c\
		free.c\
		precompute_projectiles.c\
		draw_projectile.c\
		blit_entity.c\
		init_player.c\
		player_collision.c\
		object_collision.c\
		init_alfred.c\
		init_spooky.c\
		load_bxpm.c

RAW_TEXTURES =	wood.xpm\
		nebula1.xpm\
		nebula2.xpm\
		nebula3.xpm\
		nebula4.xpm\
		nebula5.xpm\
		nebula6.xpm\
		spooky.xpm\
		alfred.xpm\
		bh.xpm\
		vent.xpm\

NAME = doom
CDIR = srcs
ODIR = obj
LIB_DIR = lib
SRCS = $(addprefix $(CDIR)/,$(RAW_SRC))
OBJ = $(addprefix $(ODIR)/,$(RAW_SRC:.c=.o))

PATH_TO_XPM = ./resources/xpm
PATH_TO_BXPM = ./resources/bxpm
XPM = $(addprefix $(PATH_TO_XPM)/,$(RAW_TEXTURES))
BXPM = $(addprefix $(PATH_TO_BXPM)/,$(RAW_TEXTURES:.xpm=.bxpm))

LINK_ID = 1IBh1iV3SRCg1aIaTFb0ryNg-xbjdGMvr
RESOURCES = resources

LIBS = ./lib/libft/libft.a ./lib/libpf/libpf.a ./lib/tpool/tpool.a
SDL = -I SDL2/include -L SDL2/lib -l SDL2-2.0.0 -l SDl2_ttf-2.0.0
CFLAGS = -Wall -Wextra -Werror


all: $(LIBS) $(RESOURCES) $(PATH_TO_BXPM) $(BXPM) $(ODIR) $(NAME)
	@printf $(GREEN)"Done!\n"$(RESET)

$(ODIR):
	@mkdir -p $@

$(PATH_TO_BXPM):
	@mkdir -p $@

$(NAME): $(OBJ)
	@gcc -o $@ $(OBJ) $(LIBS) $(SDL)
	@printf $(GREEN)"$@ was created.\n"$(RESET)


$(ODIR)/%.o: $(CDIR)/%.c
	@printf $(YELLOW)"Compiling $<\n"$(RESET)
	@gcc -c $< -o $@


$(PATH_TO_BXPM)/%.bxpm: $(PATH_TO_XPM)/%.xpm
	@./bxpm_converter/bxpm_convert $<
	@mv ./resources/xpm/*.bxpm ./resources/bxpm/

$(LIB_DIR):
	@git clone https://github.com/Epicurius/lib.git

$(LIBS): $(LIB_DIR)
	@make --no-print-directory -C lib/libft
	@make --no-print-directory -C lib/libpf
	@make --no-print-directory -C lib/tpool

clean:
	@/bin/rm -rf $(ODIR)

fclean: clean
	@/bin/rm -f $(NAME)

fclean_all: fclean
	@/bin/rm -rf $(PATH_TO_BXPM)

$(RESOURCES):
	@printf $(CYAN)"[INFO] Importing resources\n"$(GREEN)
	@wget -q --show-progress \
	"https://drive.google.com/uc?export=download&confirm=$$(wget --quiet $\
	--no-check-certificate 'https://drive.google.com/uc?export=download&id=$\
	$(LINK_ID)' -O- | gsed -rn $\
	's/.*confirm=([0-9A-Za-z_]+).*/\1\n/p')\
	&id=$(LINK_ID)" -O file.tar.gz $\
	@printf $(CYAN)"[INFO] Unarchiving resources\n"$(RESET)
	@tar -xf file.tar.gz
	@rm -rf file.tar.gz


re: fclean all

.PHONY: clean, all, re, fclean
