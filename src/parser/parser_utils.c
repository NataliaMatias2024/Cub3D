/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 10:30:33 by namatias          #+#    #+#             */
/*   Updated: 2026/06/06 02:03:41 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	print_error(int status)
{
	printf("Error\n");
	if (status > 0 && status <= 3)
	{
		printf("┌────────────────────────────────────────┐\n");
		printf("| 42school                               |\n");
		printf("|                                        |\n");
		printf("|-------------[ Invalid Map ]------------|\n");
		printf("| To execute correctly, use the command: |\n");
		printf("|----------------------------------------|\n");
		printf("| ./cub3D ./maps/NAME_MAP.cub            |\n");
		printf("|                                        |\n");
		printf("| PS: Make sure the file exists and that |\n");
		printf("| the extension is correct (.cub).   	 |\n");
		printf("└────────────────────────────────────────┘\n");
	}
	else if (status == 4)
	{
		printf("Invalid file descriptor. ");
		printf("Make sure you have the right permission to this file\n");
	}
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
	while(line[i])
	{
		if(!ft_isspace(line[i]) && line[i] != '\n')
			return (1);
		i++;			
	}
	return (0);
}

int	skip_space(char *line)
{
	int	i;

	i = 0;
	while(line[i])
	{
		if(ft_isspace(line[i]))
			i++;
		else
			return (i);
	}
	return (0);
}
