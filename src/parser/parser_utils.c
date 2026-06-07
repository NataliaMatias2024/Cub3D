/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 10:30:33 by namatias          #+#    #+#             */
/*   Updated: 2026/06/07 14:03:11 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	print_error(int status)
{
	// Manda o "Error\n" para o fd 2 (stderr)
	ft_putstr_fd("Error\n", 2);
	if (status == 1)
	{
		ft_putstr_fd("Invalid number of arguments. ", 2);
		ft_putstr_fd("Usage: ./cub3D <map.cub>\n", 2);
	}
	else if (status == 2)
		ft_putstr_fd("Invalid file extension. Expected '.cub'.\n", 2);
	else if (status == 3)
    {
        ft_putstr_fd("File does not exist, is a directory, ", 2);
        ft_putstr_fd("or cannot be opened. ", 2);
        ft_putstr_fd("Check file permissions and its extension.\n", 2);
    }
	else if (status == 4)
		ft_putstr_fd("Invalid texture extension. Expected '.png'.\n", 2);
	else if (status == 5)
		ft_putstr_fd("Invalid texture. Expected a path without spaces.\n", 2);
	else if (status == 6)
		ft_putstr_fd("Duplicated texture. Check your map file.\n", 2);
}

void	init_structs(t_parser *parser, t_file *file, t_texture *texture)
{
	parser->file = file;
	parser->status = 0;
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
