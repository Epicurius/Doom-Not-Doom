SHELL_NAME	= $(shell uname -s)
CPU = $(firstword $(subst -, ,$(shell gcc -dumpmachine)))

ifeq ($(CPU), mingw32)
 	MAKE = mingw32-make
else ifeq ($(CPU), x86_64)
	MAKE = mingw32-make
else
	MAKE = make
endif

RESOURCES	= resources

all: $(RESOURCES)
	@echo "SYSTEM: "$(SHELL_NAME) "CPU: " $(CPU)
	@$(MAKE) -C ./libs/libft -j6
	@$(MAKE) -C ./libs/libpf -j6
	@$(MAKE) -C ./libs/libbxpm -j6
	@$(MAKE) -C ./libs/libtp -j6
	@$(MAKE) -C ./libs/liblg -j6
	@$(MAKE) -C ./libs/libui -j6 
	@$(MAKE) -C ./game -j6

clean:
	@$(MAKE) clean -C ./libs/libft
	@$(MAKE) clean -C ./libs/libpf
	@$(MAKE) clean -C ./libs/libbxpm
	@$(MAKE) clean -C ./libs/libtp
	@$(MAKE) clean -C ./libs/liblg
	@$(MAKE) clean -C ./libs/libui
	@$(MAKE) clean -C ./game
	
fclean:
	@$(MAKE) fclean -C ./libs/libft
	@$(MAKE) fclean -C ./libs/libpf
	@$(MAKE) fclean -C ./libs/libbxpm
	@$(MAKE) fclean -C ./libs/libtp
	@$(MAKE) fclean -C ./libs/liblg
	@$(MAKE) fclean -C ./libs/libui
	@$(MAKE) fclean -C ./game

re: fclean all

$(RESOURCES):
	@./install/DownloadResources.sh || (exit)
	@unzip -qq resources.zip
	@rm -rf resources.zip
#	@rm doom*

delete_resources:
	rm -rf SDL2.framework
	rm -rf SDL2_ttf.framework
	rm -rf SDL2_image.framework
	rm -rf SDL2_mixer.framework
	rm -rf resources
	
install_framework:
	@mkdir -p ~/Library/Frameworks
	cp -Rf ./libs/SDL_MAC/SDL2.framework ~/Library/Frameworks/
	cp -Rf ./libs/SDL_MAC/SDL2_ttf.framework ~/Library/Frameworks/
	cp -Rf ./libs/SDL_MAC/SDL2_image.framework ~/Library/Frameworks/
	cp -Rf ./libs/SDL_MAC/SDL2_mixer.framework ~/Library/Frameworks/

delete_framework:
	rm -rf ~/Library/Frameworks/SDL2.framework
	rm -rf ~/Library/Frameworks/SDL2_ttf.framework
	rm -rf ~/Library/Frameworks/SDL2_image.framework
	rm -rf ~/Library/Frameworks/SDL2_mixer.framework

.PHONY: clean, all, re, fclean
