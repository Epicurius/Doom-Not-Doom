# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/26 11:13:50 by nneronin          #+#    #+#              #
#    Updated: 2022/01/16 18:33:03 by nneronin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SHELL_NAME	:= $(shell uname -s)

RESOURCES	= resources

all: $(RESOURCES)
	@make -C ./libs/libft -j6
	@make -C ./libs/libpf -j6
	@make -C ./libs/libbxpm -j6
	@make -C ./libs/libtp -j6
	@make -C ./libs/liblg -j6
	@make -C ./libs/libui -j6 
	@make -f install/Makefile -j6

clean:
	@make clean -C ./libs/libft
	@make clean -C ./libs/libpf
	@make clean -C ./libs/libbxpm
	@make clean -C ./libs/libtp
	@make clean -C ./libs/liblg
	@make clean -C ./libs/libui
	@make clean -f install/Makefile
	
fclean:
	@make fclean -C ./libs/libft
	@make fclean -C ./libs/libpf
	@make fclean -C ./libs/libbxpm
	@make fclean -C ./libs/libtp
	@make fclean -C ./libs/liblg
	@make fclean -C ./libs/libui
	@make fclean -f install/Makefile

re: fclean all

$(RESOURCES):
	@./install/DownloadResources.sh || (exit)
	@unzip -qq resources.zip
	@rm -rf resources.zip
	@rm doom*

delete_resources:
	rm -rf SDL2.framework
	rm -rf SDL2_ttf.framework
	rm -rf SDL2_image.framework
	rm -rf SDL2_mixer.framework
	rm -rf resources
	
install_framework:
	@mkdir -p ~/Library/Frameworks
ifeq ("$(wildcard ~/Library/Frameworks/SDL2*.framework)","")
	cp -Rf ./libs/SDL_MAC/SDL2.framework ~/Library/Frameworks/
	cp -Rf ./libs/SDL_MAC/SDL2_ttf.framework ~/Library/Frameworks/
	cp -Rf ./libs/SDL_MAC/SDL2_image.framework ~/Library/Frameworks/
	cp -Rf ./libs/SDL_MAC/SDL2_mixer.framework ~/Library/Frameworks/
endif

delete_framework:
	rm -rf ~/Library/Frameworks/SDL2.framework
	rm -rf ~/Library/Frameworks/SDL2_ttf.framework
	rm -rf ~/Library/Frameworks/SDL2_image.framework
	rm -rf ~/Library/Frameworks/SDL2_mixer.framework

.PHONY: clean, all, re, fclean
