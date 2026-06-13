/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 10:30:33 by namatias          #+#    #+#             */
/*   Updated: 2026/06/12 22:59:34 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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
	parser->file->player_view = -1;
	parser->file->player_row = -1;
	parser->file->player_col = -1;
	parser->file->map = NULL;
	parser->file->total_row = -1;
	parser->file->total_col = -1;
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
