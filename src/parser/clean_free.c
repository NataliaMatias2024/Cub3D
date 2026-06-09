/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 18:53:35 by namatias          #+#    #+#             */
/*   Updated: 2026/06/08 22:08:07 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	clean_structs(t_parser *parser)
{
	if (parser->file->texture->no != NULL)
	{
		free (parser->file->texture->no);
		parser->file->texture->no = NULL;
	}
	if (parser->file->texture->so != NULL)
	{
		free (parser->file->texture->so);
		parser->file->texture->so = NULL;
	}
	if (parser->file->texture->we != NULL)
	{
		free (parser->file->texture->we);
		parser->file->texture->we = NULL;
	}
	if (parser->file->texture->ea != NULL)
	{
		free (parser->file->texture->ea);
		parser->file->texture->ea = NULL;
	}
	if (parser->file->player_view != NULL)
	{
		free (parser->file->player_view);
		parser->file->player_view = NULL;
	}
}

void	free_split(char **splited)
{
	int	i;

	i = 0;
	while (splited[i])
	{
		free(splited[i]);
		i++;
	}
	free (splited);
}

void	stop_reading_free(int fd, char *line)
{
	free(line);
	get_next_line(-1);
	close (fd);
}
