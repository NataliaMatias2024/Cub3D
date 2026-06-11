/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 10:30:33 by namatias          #+#    #+#             */
/*   Updated: 2026/06/11 19:40:00 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	print_error(int status)
{
	ft_putstr_fd("Error\n", 2);
	if (status == 1)
		ft_putstr_fd("Argument Error: Expected exactly one '.cub' file.\n", 2);
	else if (status == 2 || status == 3)
	{
		ft_putstr_fd("File Error: ", 2);
		if (status == 2)
			ft_putstr_fd("Map must have a '.cub' extension.\n", 2);
		else if (status == 3)
			ft_putstr_fd("Cannot open file. Check path and permissions.\n", 2);
	}
	else if (status >= 4 && status <= 6)
	{
		ft_putstr_fd("Texture Error: ", 2);
		if (status == 4)
			ft_putstr_fd("File must have a '.png' extension.\n", 2);
		else if (status == 5)
			ft_putstr_fd("Path contains invalid whitespace.\n", 2);
		else if (status == 6)
			ft_putstr_fd("Duplicated configuration (NO, SO, WE or EA).\n", 2);
	}
	else if (status >= 7 && status <= 9)
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
	else if (status == 10)
		ft_putstr_fd("File Error: Invalid identifier or unexpected character found.\n", 2);
	else if (status == 11)
		ft_putstr_fd("Memory Error: Unable to allocate memory.\n", 2);
	else if (status == 12)
		ft_putstr_fd("Map Error: Map has an empty line or invalid characters.\n", 2);
}

void	init_structs(t_parser *parser, t_file *file, t_texture *texture)
{
	parser->file = file;
	parser->status = 0;
	parser->map_started = 0;
	parser->map_ended = 0;
	parser->temp_map = ft_dlist_initi();
	file->texture = texture;
	parser->file->texture->no = NULL;
	parser->file->texture->so = NULL;
	parser->file->texture->we = NULL;
	parser->file->texture->ea = NULL;
	parser->file->color_ceiling = -1;
	parser->file->color_floor = -1;
	parser->file->player_view = NULL;
	parser->file->player_x = -1;
	parser->file->player_y = -1;
	parser->file->total_x = -1;
	parser->file->total_y = -1;
}

int	empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!ft_isspace(line[i]) && line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

int	skip_space(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (ft_isspace(line[i]))
			i++;
		else
			return (i);
	}
	return (0);
}

int	check_permission(char *file, t_parser *parser)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		parser->status = 3;
		return (-1);
	}
	return (fd);
}
