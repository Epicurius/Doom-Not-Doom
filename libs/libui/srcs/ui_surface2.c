/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_surface2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 19:24:36 by jsalmi            #+#    #+#             */
/*   Updated: 2022/01/23 11:41:33 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

void	ui_surface_print(SDL_Surface *surface)
{
	ft_printf("[%s] : \n", __FUNCTION__);
	if (!surface)
	{
		ft_printf("surface given doesn\'t exist.\n");
		return ;
	}
	ft_printf("\tw : %d\n", surface->w);
	ft_printf("\th : %d\n", surface->h);
	ft_printf("\tpitch : %d\n", surface->pitch);
	ft_printf("\tformat : \n");
	ft_printf("\t\tformat : %d %s\n", surface->format->format,
		SDL_GetPixelFormatName(surface->format->format));
	ft_printf("\t\tBitsPerPixel : %d\n", surface->format->BitsPerPixel);
	ft_printf("\t\tBytesPerPixel : %d\n", surface->format->BytesPerPixel);
	ft_printf("\t\tRmask : %.8x\n", surface->format->Rmask);
	ft_printf("\t\tGmask : %.8x\n", surface->format->Gmask);
	ft_printf("\t\tBmask : %.8x\n", surface->format->Bmask);
	ft_printf("\t\tAmask : %.8x\n", surface->format->Amask);
}

SDL_Surface	*ui_surface_image_new(char *image_path)
{
	SDL_Surface	*surface;

	surface = SDL_LoadBMP(image_path);
	if (!surface)
		ft_printf("[%s] Error loading image from path. <%s>\n",
			__FUNCTION__, image_path);
	return (surface);
}

SDL_Surface	*ui_surface_text_new(
	char *text, char *font_path, int size, Uint32 color)
{
	SDL_Surface	*surface;
	t_rgba		rgba;
	SDL_Color	col;
	TTF_Font	*font;

	font = ui_get_font(font_path, size);
	if (!font)
		return (NULL);
	rgba = hex_to_rgba(color);
	col = rgba_to_sdl_color(rgba);
	surface = TTF_RenderUTF8_Blended(font, text, col);
	return (surface);
}