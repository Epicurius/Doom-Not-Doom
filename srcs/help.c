/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 14:42:34 by nneronin          #+#    #+#             */
/*   Updated: 2021/07/15 10:54:57 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	print_help_msg(void)
{
	ft_printf("{CLR:41}------------------------------"
			"------------------------------{RESET}\n");
	ft_printf(" Usage example: ./doom ./resources/MAPS/skybox.txt\n");
	ft_printf("\n Args:\t-size {RED}W{RESET}x{GREEN}H{RESET},"
			" Set window size {RED}width{RESET} and {GREEN}height{RESET}.\n");
	ft_printf("\t-mouse {RED}X{RESET}x{GREEN}Y{RESET},"
			" Set Mouse sensitivity to {RED}X{RESET} and {GREEN}Y{RESET}.\n");
	ft_printf("\t-res {CYAN}x{RESET}, Set render resolution to"
			" {CYAN}x{RESET}.\n");
	ft_printf("\t-diff {CYAN}x{RESET}, Set game difficulty to {CYAN}x{RESET}"
			" (0-3).\n");
	ft_printf("\t-fov {CYAN}x{RESET}, Set FOV to {CYAN}x{RESET}\n");
	ft_printf("\t-debug, Enable debug mode.\n");
	ft_printf("\t-launcher, On EXIT launch the launcher.\n");
	ft_printf("{CLR:41}------------------------------"
			"------------------------------{RESET}\n");
	exit(1);
}
