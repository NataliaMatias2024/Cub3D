/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 22:31:33 by namatias          #+#    #+#             */
/*   Updated: 2026/06/11 19:51:20 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	get_temp_map(char *line, t_parser *parser);
static int	check_map_status(t_parser *parser, char *line);

void	get_map(char *line, t_parser *parser)
{
	get_temp_map(line, parser);
}

static void	get_temp_map(char *line, t_parser *parser)
{
	t_node	*new_node;
	char	*line_copy;
		
	if (!check_map_status(parser, line))
		return ;
	parser->map_started = 1;
	line_copy = ft_strdup(line);
	if (!line_copy)
	{
		parser->status = 11;
		return ;
	}
	new_node = ft_new_node((void *)line_copy);
	if (!new_node)
	{
		free(line_copy);
		ft_destroy_dlst(&parser->temp_map, free);
		parser->status = 11;
		return ;
	}
	ft_push_node_back(parser->temp_map, new_node);
}

static int	check_map_status(t_parser *parser, char *line)
{
	if (empty_line(line))
	{
		if (parser->map_started == 1)
			parser->map_ended = 1;
		return (0);
	}
	if (parser->map_ended == 1)
	{
		parser->status = 12;
		return (0);
	}
	parser->map_started = 1;
	return (1);
}
