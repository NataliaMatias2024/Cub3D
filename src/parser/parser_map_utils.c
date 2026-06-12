/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 02:06:31 by namatias          #+#    #+#             */
/*   Updated: 2026/06/12 17:29:32 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	check_char_player(t_file *file, int row, int col);

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
