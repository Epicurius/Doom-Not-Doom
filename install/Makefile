SHELL_NAME	= $(shell uname -s)

RED			=	"\e[0;31m"
GREEN		=	"\e[0;32m"
YELLOW		=	"\e[0;33m"
BLUE		=	"\e[0;34m"
MAGENTA		=	"\e[0;35m"
CYAN		=	"\e[0;36m"
RESET		=	"\e[0m"

CFILES		=	ai_attack.c\
				get_root.c\
				ai_movement.c\
				animate_wsprite.c\
				args.c\
				blit_bxpm.c\
				camera.c\
				clock.c\
				color_and_brightness.c\
				compute_vline.c\
				crosshair_position.c\
				doom.c\
				game_mode.c\
				find_sector.c\
				fps.c\
				icon.c\
				get_entity_state.c\
				help.c\
				keys.c\
				malloc_texture_pos.c\
				minimap.c\
				movement.c\
				orientation.c\
				precompute_buy_menu.c\
				precompute_entities.c\
				precompute_projectiles.c\
				precompute_skybox.c\
				precompute_walls.c\
				precompute_weapon.c\
				project_entity.c\
				project_wall.c\
				protalloc.c\
				purge_entities.c\
				put_pixels.c\
				sound.c\
				spawn_entity.c\
				update_screen.c\
				wall_to_screen_xz.c\
				fix_map.c\
				UI/game_loading.c\
				UI/game_over.c\
				UI/game_quit.c\
				ParseMap/parse_map.c\
				ParseMap/parse_map_events1.c\
				ParseMap/parse_map_events2.c\
				ParseMap/parse_map_header.c\
				ParseMap/parse_map_sector.c\
				ParseMap/parse_map_sprite.c\
				ParseMap/validate_map1.c\
				ParseMap/validate_map2.c\
				Init/init.c\
				Init/init_entity.c\
				Init/init_game_mode.c\
				Init/init_glock.c\
				Init/init_inventory.c\
				Init/init_kar.c\
				Init/init_launcher.c\
				Init/init_minigun.c\
				Init/init_minimap.c\
				Init/init_player.c\
				Init/init_render.c\
				Init/init_scale.c\
				Init/init_sdl.c\
				Init/init_shotgun.c\
				Init/init_slope.c\
				Init/init_textures.c\
				Init/init_weapons.c\
				Init/init_surface_textures.c\
				Math/math1.c\
				Math/math2.c\
				Math/math3.c\
				Math/math4.c\
				Math/math5.c\
				Math/math6.c\
				Math/math7.c\
				Math/math8.c\
				Math/math9.c\
				Math/math10.c\
				Math/math11.c\
				Free/free1.c\
				Free/free2.c\
				Free/free3.c\
				Free/free4.c\
				Events/map_events.c\
				Events/sector_events.c\
				Events/wsprite_events.c\
				BuyMenu/bm.c\
				BuyMenu/bm_init1.c\
				BuyMenu/bm_init2.c\
				BuyMenu/bm_update1.c\
				BuyMenu/bm_update2.c\
				BuyMenu/bm_event.c\
				BuyMenu/bm_attempt.c\
				Draw/draw2.c\
				Draw/draw_bullet_holes.c\
				Draw/draw_ceiling.c\
				Draw/draw_crosshair.c\
				Draw/draw_entity.c\
				Draw/draw_floor.c\
				Draw/draw_floor_and_ceiling.c\
				Draw/draw_hud.c\
				Draw/draw_neighbor_wall.c\
				Draw/draw_portal_texture.c\
				Draw/draw_projectile.c\
				Draw/draw_skybox_plane.c\
				Draw/draw_skybox_wall.c\
				Draw/draw_skybox.c\
				Draw/draw_wall.c\
				Draw/draw_weapon.c\
				Draw/draw_wsprites.c\
				Draw/draw_hud_utils.c\
				Draw/draw_vline.c\
				Draw/draw_line.c\
				Draw/draw_circle.c\
				EntityCoords/alfred1.c\
				EntityCoords/alfred2.c\
				EntityCoords/barrel.c\
				EntityCoords/ceiling_lamp.c\
				EntityCoords/gargoyle.c\
				EntityCoords/ghost1.c\
				EntityCoords/ghost2.c\
				EntityCoords/lamp.c\
				EntityCoords/spooky1.c\
				EntityCoords/spooky2.c\
				EntityCoords/meat_hook.c\
				EntityCoords/med_kit.c\
				EntityCoords/torch.c\
				EntityCoords/rift.c\
				CollisionDetection/collision_detection.c\
				CollisionDetection/horizontal_collision.c\
				CollisionDetection/vertical_collision.c\
				CollisionDetection/object_collision.c\
				CollisionDetection/slide_collision.c\
				CollisionDetection/projectile_collision.c\
				CollisionDetection/crouch_collision.c

NAME		=	doom
CDIR		=	srcs
ODIR		=	obj
INC			=	-I./inc
SRCS		=	$(addprefix $(CDIR)/,$(CFILES))
OBJ			=	$(addprefix $(ODIR)/,$(CFILES:.c=.o))
DEP			=	$(OBJ:.o=.d)

LIB_DIR		=	libs

LIB_INC		=	-I $(LIB_DIR)/libft \
				-I $(LIB_DIR)/libpf \
				-I $(LIB_DIR)/libtp \
				-I $(LIB_DIR)/libbxpm \
				-I $(LIB_DIR)/liblg \
				-I $(LIB_DIR)/libui

LIBS		=	-L $(LIB_DIR)/libft -lft \
				-L $(LIB_DIR)/libpf -lpf \
				-L $(LIB_DIR)/libtp -ltp \
				-L $(LIB_DIR)/liblg -llg \
				-L $(LIB_DIR)/libbxpm -lbxpm \
				-L $(LIB_DIR)/libui -lui

ifeq ($(SHELL_NAME), Darwin)

LIB_INC		+=	-I SDL2.framework/Headers -I SDL2_mixer.framework/Headers -I SDL2_ttf.framework/Headers -F ./
LIBS		+=	-framework SDL2 -framework SDL2_mixer -framework SDL2_ttf -F ./ -rpath @executable_path
CFLAGS		=	-Wall -Wextra -MMD -O3 -flto -Werror -Wfatal-errors# -g -fsanitize=address

else

LIB_INC		+=	-I ./SDL2_includes
LIBS		+=	-L . -lSDL2 -lSDL2_ttf -lSDL2_mixer
CFLAGS		=	-Wall -Wextra -MMD -Wno-unused-variable -O3 -flto #-Werror -Wfatal-errors

endif

all: $(ODIR) $(NAME)
	@printf $(GREEN)"\e[J[INFO] $(NAME) ready!\n"$(RESET)

-include $(DEP)

$(ODIR):
	@mkdir -p $@
	@mkdir -p $@/UI
	@mkdir -p $@/Init
	@mkdir -p $@/Math
	@mkdir -p $@/Free
	@mkdir -p $@/Draw
	@mkdir -p $@/Events
	@mkdir -p $@/BuyMenu
	@mkdir -p $@/ParseMap
	@mkdir -p $@/EntityCoords
	@mkdir -p $@/CollisionDetection

$(NAME): $(OBJ)
	@gcc $(CFLAGS) $(OBJ) $(LIB_INC) $(INC) $(LIBS) -pthread -o $(NAME)
ifeq ($(SHELL_NAME), Darwin)
	@Rez -a docs/icon.rsrc -o $(NAME)
	@SetFile -a C $(NAME)
endif

$(ODIR)/%.o: $(CDIR)/%.c
	@gcc -c $< -o $@ $(CFLAGS) $(LIB_INC) $(INC)
	@printf $(YELLOW)"\e[JCompiling $<\n\e[F"$(RESET)

clean:
	@printf $(CYAN)"[INFO] $(NAME) cleaned!\n"$(RESET)
	@rm -rf $(ODIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: clean, all, re, fclean
