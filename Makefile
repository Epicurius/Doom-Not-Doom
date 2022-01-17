# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/26 11:13:50 by nneronin          #+#    #+#              #
#    Updated: 2022/01/17 11:25:23 by nneronin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SHELL_NAME	:= $(shell uname -s)

#MAKE = mingw32-make
MAKE = make

RESOURCES	= resources

all: $(RESOURCES)
	echo $(SHELL_NAME)
	@$(MAKE) -C ./libs/libft -j6
	@$(MAKE) -C ./libs/libpf -j6
	@$(MAKE) -C ./libs/libbxpm -j6
	@$(MAKE) -C ./libs/libtp -j6
	@$(MAKE) -C ./libs/liblg -j6
	@$(MAKE) -C ./libs/libui -j6 
	@$(MAKE) -f install/Makefile -j6

clean:
	@$(MAKE) clean -C ./libs/libft
	@$(MAKE) clean -C ./libs/libpf
	@$(MAKE) clean -C ./libs/libbxpm
	@$(MAKE) clean -C ./libs/libtp
	@$(MAKE) clean -C ./libs/liblg
	@$(MAKE) clean -C ./libs/libui
	@$(MAKE) clean -f install/Makefile
	
fclean:
	@$(MAKE) fclean -C ./libs/libft
	@$(MAKE) fclean -C ./libs/libpf
	@$(MAKE) fclean -C ./libs/libbxpm
	@$(MAKE) fclean -C ./libs/libtp
	@$(MAKE) fclean -C ./libs/liblg
	@$(MAKE) fclean -C ./libs/libui
	@$(MAKE) fclean -f install/Makefile

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
