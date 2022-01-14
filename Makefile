# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/26 11:13:50 by nneronin          #+#    #+#              #
#    Updated: 2022/01/14 13:30:24 by nneronin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SHELL_NAME	:= $(shell uname -s)

all:
ifeq ($(SHELL_NAME), Darwin)
	@mkdir -p ~/Library/Frameworks
ifeq ("$(wildcard ~/Library/Frameworks/SDL2*.framework)","")
	@cp -Rf ./libs/SDL_MAC/SDL2.framework ~/Library/Frameworks/
	@cp -Rf ./libs/SDL_MAC/SDL2_ttf.framework ~/Library/Frameworks/
	@cp -Rf ./libs/SDL_MAC/SDL2_image.framework ~/Library/Frameworks/
	@cp -Rf ./libs/SDL_MAC/SDL2_mixer.framework ~/Library/Frameworks/
endif
endif
	@make -C ./libs/libft -j6
	@make -C ./libs/libpf -j6
	@make -C ./libs/libbxpm -j6
	@make -C ./libs/libtp -j6
	@make -C ./libs/liblg -j6
	@make -C ./libs/libui
ifeq ($(SHELL_NAME), Darwin)
	@make -f InstallationTools/Makefile-mac -j6 || :
else
	@mingw32-make -f InstallationTools/Makefile-win
endif

clean:
	@make clean -C ./libs/libft
	@make clean -C ./libs/libpf
	@make clean -C ./libs/libbxpm
	@make clean -C ./libs/libtp
	@make clean -C ./libs/liblg
	@make clean -C ./libs/libui
ifeq ($(SHELL_NAME), Darwin)
	@make clean -f InstallationTools/Makefile-mac
else
	@mingw32-make clean -f InstallationTools/Makefile-win 
endif
	
fclean:
	@make fclean -C ./libs/libft
	@make fclean -C ./libs/libpf
	@make fclean -C ./libs/libbxpm
	@make fclean -C ./libs/libtp
	@make fclean -C ./libs/liblg
	@make fclean -C ./libs/libui
ifeq ($(SHELL_NAME), Darwin)
	@make fclean -f InstallationTools/Makefile-mac
else
	@mingw32-make fclean -f InstallationTools/Makefile-win 
endif

re: fclean all

framework_del:
	rm -rf ~/Library/Frameworks/SDL2*.framework

.PHONY: clean, all, re, fclean
