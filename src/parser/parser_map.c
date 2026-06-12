/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 22:31:33 by namatias          #+#    #+#             */
/*   Updated: 2026/06/12 02:00:13 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	check_map_status(t_parser *parser, char *line);
static void	fill_map_array(t_parser *parser, char **map);

void	get_map(char *line, t_parser *parser)
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

static void	fill_map_array(t_parser *parser, char **map)
{
	t_node	*aux;
	int		cols;
	int		temp;
	int		i;

	i = 0;
	cols = 0;
	aux = parser->temp_map->head;
	while (i < (int)parser->temp_map->size)
	{
		map[i] = ft_strdup((char *)aux->data);
		temp = ft_strlen(map[i]);
		if (temp > 0 && map[i][temp - 1] == '\n')
			temp--;
		if (temp > cols)
			cols = temp;
		aux = aux->next;
		i++;
	}
	map[i] = '\0';
	parser->file->total_x = cols;
	parser->file->total_y = (int)parser->temp_map->size;
	parser->file->map = map;
}

void	create_final_map(t_parser *parser)
{
	int		rows;
	char	**map;

	rows = (int)parser->temp_map->size;
	map = malloc((rows + 1) * sizeof(char *));
	if (!map)
	{
		parser->status = 11;
		return ;
	}
	fill_map_array(parser, map);
	ft_destroy_dlst(&parser->temp_map, free);
}
