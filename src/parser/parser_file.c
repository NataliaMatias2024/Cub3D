/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 18:05:33 by namatias          #+#    #+#             */
/*   Updated: 2026/06/12 17:28:29 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static	int	only_map_empty(t_parser *parser);
static void	load_struc(t_parser *parser, char *line);
static	int	is_valid_line(t_parser *parse, char *line);

//Le o arquivo .cub linha por linha e encaminha a linha para a funçao de parser correta
//Erros devem interromper o programa e avisar a gnl que deve encerrar e liberar memoria
int	read_file(char *map_name, t_parser *parser)
{
	int		fd;
	char	*line;

	fd = check_permission(map_name, parser);
	if (fd == -1)
		return (0);
	line = get_next_line(fd);
	while (line)
	{
		if (parser->status == 0)
			load_struc(parser, line);
		if (parser->status != 0)
		{
			stop_reading_free(fd, line);
			return (0);
		}
		free (line);
		line = get_next_line(fd);
	}
	if (create_save_map(parser, fd))
		return (1);
	return (0);
}

static void	load_struc(t_parser *parser, char *line)
{
	if (!only_map_empty(parser) && !empty_line(line))
	{
		if (!is_valid_line(parser, line))
			return ;
		get_texture(line, parser);
		if (parser->status == 0)
			get_color(line, parser);
	}
	else if (only_map_empty(parser))
		get_map(line, parser);
}

static	int	is_valid_line(t_parser *parser, char *line)
{
	int	start;

	start = 0;
	start = skip_space(line);
	if (!ft_strncmp(line + start, "NO", 2)
		|| !ft_strncmp(line + start, "SO", 2)
		|| !ft_strncmp(line + start, "WE", 2)
		|| !ft_strncmp(line + start, "EA", 2)
		|| !ft_strncmp(line + start, "F", 1)
		|| !ft_strncmp(line + start, "C", 1))
		return (1);
	parser->status = 10;
	return (0);
}

//Garante que todas as variáveis obrigatorias foram preenchidas
//antes de iniciar o parse do mapa
static	int	only_map_empty(t_parser *parser)
{
	if (parser->file->texture->no == NULL
		|| parser->file->texture->so == NULL
		|| parser->file->texture->we == NULL
		|| parser->file->texture->ea == NULL
		|| parser->file->color_ceiling == -1
		|| parser->file->color_floor == -1)
		return (0);
	return (1);
}
