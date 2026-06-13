/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 22:31:33 by namatias          #+#    #+#             */
/*   Updated: 2026/06/12 21:21:29 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	fill_map_array(t_parser *parser, char **map);
static int	check_map_status(t_parser *parser, char *line);
static void	validate_map_rules(t_parser *parser, t_file *file);

void	get_map(char *line, t_parser *parser)
{
	t_node	*new_node;
	char	*line_copy;

	if (!check_map_status(parser, line))
		return ;
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
		while (temp > 0 && (map[i][temp - 1] == '\n'
			|| map[i][temp - 1] == '\r'))
		{
			map[i][temp - 1] = '\0';
			temp--;
		}
		if (temp > cols)
			cols = temp;
		aux = aux->next;
		i++;
	}
	map[i] = NULL;
	parser->file->total_row = (int)parser->temp_map->size;
	parser->file->total_col = cols;
	parser->file->map = map;
}

int	create_save_map(t_parser *parser, int fd)
{
	int		rows;
	char	**map;

	if (parser->status == 0 && parser->temp_map->size > 0)
	{
		rows = (int)parser->temp_map->size;
		map = malloc((rows + 1) * sizeof(char *));
		if (!map)
		{
			parser->status = 11;
			return (0);
		}
		fill_map_array(parser, map);
		ft_destroy_dlst(&parser->temp_map, free);
	}
	if (parser->status == 0 && parser->file->map != NULL)
		validate_map_rules(parser, parser->file);
	close(fd);
	if (parser->status != 0)
		return (0);
	return (1);
}

static void	validate_map_rules(t_parser *parser, t_file *file)
{
	char	**map_copy;

	map_copy = clone_map(parser, parser->file);
	if (!map_copy)
		return ;
	if (!check_map_info(file))
		parser->status = 13;
	else if (!trigger_flood_fill(file, map_copy))
		parser->status = 14;
	free_split(map_copy);
}
