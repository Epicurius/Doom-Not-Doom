# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/09 10:30:08 by nneronin          #+#    #+#              #
#    Updated: 2022/01/23 11:40:41 by nneronin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SHELL_NAME	:= $(shell uname -s)

RED		:= "\e[0;31m"
GREEN	:= "\e[0;32m"
YELLOW	:= "\e[0;33m"
BLUE	:= "\e[0;34m"
MAGENTA	:= "\e[0;35m"
CYAN	:= "\e[0;36m"
RESET	:= "\e[0m"

RAW =	ui_button.c\
		ui_button2.c\
		ui_button_get.c\
		ui_checkbox.c\
		ui_checkbox2.c\
		ui_dropdown.c\
		ui_dropdown2.c\
		ui_dropdown_event.c\
		ui_dropdown_get.c\
		ui_dropdown_get2.c\
		ui_element.c\
		ui_element2.c\
		ui_element3.c\
		ui_element4.c\
		ui_element5.c\
		ui_element6.c\
		ui_element_edit.c\
		ui_element_render.c\
		ui_family.c\
		ui_font.c\
		ui_help.c\
		ui_help2.c\
		ui_help3.c\
		ui_help4.c\
		ui_help5.c\
		ui_init.c\
		ui_input.c\
		ui_input2.c\
		ui_input_event.c\
		ui_input_event2.c\
		ui_input_event_help.c\
		ui_input_get.c\
		ui_input_help.c\
		ui_label.c\
		ui_label2.c\
		ui_label3.c\
		ui_label4.c\
		ui_layout.c\
		ui_layout2.c\
		ui_layout_get.c\
		ui_layout_help.c\
		ui_layout_help2.c\
		ui_line.c\
		ui_list.c\
		ui_list2.c\
		ui_menu.c\
		ui_menu_get.c\
		ui_radio.c\
		ui_radio2.c\
		ui_recipe.c\
		ui_recipe_fill_from_args.c\
		ui_recipe_fill_from_args2.c\
		ui_recipe_fill_from_args3.c\
		ui_recipe_fill_from_recipe.c\
		ui_recipe_fill_from_recipe2.c\
		ui_scrollbar.c\
		ui_scrollbar2.c\
		ui_scrollbar_get.c\
		ui_slider.c\
		ui_slider2.c\
		ui_slider_get.c\
		ui_surface.c\
		ui_surface2.c\
		ui_surface_draw.c\
		ui_text_align.c\
		ui_texture.c\
		ui_texture2.c\
		ui_vec.c\
		ui_vec2.c\
		ui_vec2i.c\
		ui_vec4.c\
		ui_vec_both.c\
		ui_vec_both2.c\
		ui_window_from.c\
		ui_window.c\
		ui_window2.c\
		ui_window3.c\
		ui_window_edit.c\
		ui_window_event.c\
		ui_get_root.c

NAME = libui.a
ODIR = obj
CDIR = srcs
SRCS = $(addprefix $(CDIR)/, $(RAW))
OBJS = $(addprefix $(ODIR)/,$(RAW:.c=.o))
JOHNNY = $(SRCS:.c=.d)
CFLAGS = #-Wall -Wextra -MMD

ifeq ($(SHELL_NAME), Darwin)
INC =	-I . \
		-I ../libft \
		-I ../libpf \
		-I ../../SDL2.framework/Headers \
		-I ../../SDL2_ttf.framework/Headers \
		-F ../../
else
INC =	-I . \
		-I ../libft \
		-I ../libpf \
		-I ../../SDL2_includes
endif

all: $(NAME)
	@printf $(GREEN)"\e[J[INFO] $(NAME) ready!\n"$(RESET)

$(ODIR):
	@mkdir -p ./obj

-include $(JOHNNY)

$(ODIR)/%.o: $(CDIR)/%.c
	@printf $(YELLOW)"\e[JCompiling $<\n\e[F"$(RESET)
	@gcc -c $< -o $@ $(INC) $(CFLAGS)

$(NAME): $(ODIR) $(OBJS)
	@ar rc $(NAME) $(OBJS)
	@ranlib $(NAME)

clean:
	@printf $(CYAN)"[INFO] $(NAME) cleaned!\n"$(RESET)
	@rm -rf $(ODIR)

fclean: clean
	@rm $(NAME)

re: fclean all

.PHONY: fclean all clean re $(NAME)
