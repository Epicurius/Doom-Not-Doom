/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   byte_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 13:37:46 by nneronin          #+#    #+#             */
/*   Updated: 2022/01/02 13:51:06 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bxpm.h"

int32_t	read_int32(unsigned char *str)
{
	return (str[3] << 24 | str[2] << 16 | str[1] << 8 | str[0]);
}

uint32_t	read_color32(unsigned char *str)
{
	return (str[3] << 24 | str[2] << 16 | str[1] << 8 | str[0]);
}

uint32_t	read_color24(unsigned char *str)
{
	return (255 << 24 | str[2] << 16 | str[1] << 8 | str[0] << 0);
}

uint32_t	bpp_clr(unsigned char *str, int bpp)
{
	if (bpp == 32 || bpp == 4)
		return (read_color32(str));
	else if (bpp == 24 || bpp == 3)
		return (read_color24(str));
	return (0);
}
