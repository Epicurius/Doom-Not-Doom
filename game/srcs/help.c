/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Niklas Neronin <niklas.neronin@gmail.com>
 */

#include "doom.h"

/*
 *	Print help message to standard output.
 */
int	print_help_msg(void)
{
	ft_printf("{CLR:41}------------------------------"
		"------------------------------{RESET}\n");
	ft_printf(" Usage example: ./game/doom-game resources/MAPS/Demo.dnds\n");
	ft_printf("\n Args:\t-size={RED}W{RESET}x{GREEN}H{RESET},\t"
		" Set window size {RED}width{RESET} and {GREEN}height{RESET}.\n");
	ft_printf("\t-mouse={RED}X{RESET}x{GREEN}Y{RESET},\t"
		" Set Mouse sensitivity to {RED}X{RESET} and {GREEN}Y{RESET}.\n");
	ft_printf("\t-res={CYAN}x{RESET},\t\t Set render resolution to"
		" {CYAN}x{RESET}.\n");
	ft_printf("\t-diff={CYAN}x{RESET},\t Set game difficulty to {CYAN}x{RESET}"
		" (0-3).\n");
	ft_printf("\t-fov={CYAN}x{RESET},\t\t Set FOV to {CYAN}x{RESET}\n");
	ft_printf("\t-debug,\t\t Enable debug mode.\n");
	ft_printf("\t-launcher,\t On EXIT launch the launcher.\n");
	ft_printf("{CLR:41}------------------------------"
		"------------------------------{RESET}\n");
	return (1);
}
