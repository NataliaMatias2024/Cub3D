/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error_msg.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 21:20:32 by namatias          #+#    #+#             */
/*   Updated: 2026/06/12 22:10:34 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	print_error_map(int status);
static void	print_error_file(int status);
static void	print_error_color(int status);
static void	print_error_texture(int status);

void	print_error(int status)
{
	ft_putstr_fd("Error\n", 2);
	if (status == 1)
		ft_putstr_fd("Argument Error: Expected exactly one '.cub' file.\n", 2);
	else if (status == 2 || status == 3 || status == 10)
		print_error_file(status);
	else if (status >= 4 && status <= 6)
		print_error_texture(status);
	else if (status >= 7 && status <= 9)
		print_error_color(status);
	else if (status == 11)
		ft_putstr_fd("Memory Error: Unable to allocate memory.\n", 2);
	else if (status >= 12 && status <= 14)
		print_error_map(status);
}

static void	print_error_file(int status)
{
	ft_putstr_fd("File Error: ", 2);
	if (status == 2)
		ft_putstr_fd("Map must have a '.cub' extension.\n", 2);
	else if (status == 3)
		ft_putstr_fd("Cannot open file. Check path and permissions.\n", 2);
	else if (status == 10)
		ft_putstr_fd("Invalid identifier or unexpected character found.\n", 2);
}

static void	print_error_color(int status)
{
	ft_putstr_fd("Color Error: ", 2);
	if (status == 7)
		ft_putstr_fd("Duplicated configuration (F or C).\n", 2);
	else if (status == 8)
		ft_putstr_fd("RGB values must be strictly between 0 and 255.\n", 2);
	else if (status == 9)
	{
		ft_putstr_fd("Invalid format. ", 2);
		ft_putstr_fd("Expected 'F or C number,number,number'.\n", 2);
	}
}

static void	print_error_texture(int status)
{
	ft_putstr_fd("Texture Error: ", 2);
	if (status == 4)
		ft_putstr_fd("File must have a '.png' extension.\n", 2);
	else if (status == 5)
		ft_putstr_fd("Path contains invalid whitespace.\n", 2);
	else if (status == 6)
		ft_putstr_fd("Duplicated configuration (NO, SO, WE or EA).\n", 2);
}

static void	print_error_map(int status)
{
	ft_putstr_fd("Map Error: ", 2);
	if (status == 12)
		ft_putstr_fd("Map has an empty line or invalid characters.\n", 2);
	else if (status == 13)
		ft_putstr_fd("Invalid character or multiple/missing players.\n", 2);
	else if (status == 14)
	{
		ft_putstr_fd("Invalid format, ", 2);
		ft_putstr_fd("map should be surround by walls (1) only!\n", 2);
	}
}
