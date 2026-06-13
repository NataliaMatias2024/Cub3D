/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 02:06:31 by namatias          #+#    #+#             */
/*   Updated: 2026/06/12 21:21:27 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	check_char_player(t_file *file, int row, int col);
static int	flood_fill(t_file *file, char **map_copy, int row, int col);

int	check_map_info(t_file *file)
{
	int	row;
	int	col;

	row = 0;
	while (file->map[row])
	{
		col = 0;
		while (file->map[row][col])
		{
			if (!check_char_player(file, row, col))
				return (0);
			col++;
		}
		row++;
	}
	if (file->player_row == -1)
		return (0);
	return (1);
}

static int	check_char_player(t_file *file, int row, int col)
{
	char	c;

	c = file->map[row][col];
	if (c == '1' || c == '0' || c == ' ')
		return (1);
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
	{
		if (file->player_row != -1)
			return (0);
		file->player_view = c;
		file->player_row = row;
		file->player_col = col;
		return (1);
	}
	return (0);
}

char	**clone_map(t_parser *parser, t_file *file)
{
	char	**map_copy;
	int		i;

	map_copy = malloc ((file->total_row + 1) * sizeof(char *));
	if (!map_copy)
	{
		parser->status = 11;
		return (NULL);
	}
	i = 0;
	while (file->map[i] && i < file->total_row)
	{
		map_copy[i] = ft_strdup(file->map[i]);
		if (!map_copy[i])
		{
			map_copy[i] = NULL;
			free_split(map_copy);
			parser->status = 11;
			return (NULL);
		}
		i++;
	}
	map_copy[i] = NULL;
	return (map_copy);
}

int	trigger_flood_fill(t_file *file, char **map_copy)
{
	int	r;
	int	c;

	r = 0;
	while (r < file->total_row)
	{
		c = 0;
		while (c < (int)ft_strlen(map_copy[r]))
		{
			if (map_copy[r][c] == '0' || map_copy[r][c] == file->player_view)
			{
				if (!flood_fill(file, map_copy, r, c))
					return (0);
			}
			c++;
		}
		r++;
	}
	return (1);
}

static int	flood_fill(t_file *file, char **map_copy, int row, int col)
{
	int	curr_col;

	if (row < 0 || row >= file->total_row)
		return (0);
	curr_col = ft_strlen(map_copy[row]);
	if (col < 0 || col >= curr_col)
		return (0);
	if (map_copy[row][col] == ' ' || map_copy[row][col] == '\0')
		return (0);
	if (map_copy[row][col] == '1' || map_copy[row][col] == 'V')
		return (1);
	map_copy[row][col] = 'V';
	if (!flood_fill(file, map_copy, row + 1, col))
		return (0);
	if (!flood_fill(file, map_copy, row - 1, col))
		return (0);
	if (!flood_fill(file, map_copy, row, col + 1))
		return (0);
	if (!flood_fill(file, map_copy, row, col - 1))
		return (0);
	return (1);
}
