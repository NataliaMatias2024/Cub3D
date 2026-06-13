/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 18:53:35 by namatias          #+#    #+#             */
/*   Updated: 2026/06/12 23:59:21 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	clean_texture(t_file *file);

void	clean_all(t_parser *parser)
{
	clean_texture(parser->file);
	if (parser->file->map != NULL)
	{
		free_split(parser->file->map);
		parser->file->map = NULL;
	}
	if (parser->temp_map != NULL)
	{
		ft_destroy_dlst(&parser->temp_map, free);
	}
}

static void	clean_texture(t_file *file)
{
	if (file->texture->no != NULL)
	{
		free (file->texture->no);
		file->texture->no = NULL;
	}
	if (file->texture->so != NULL)
	{
		free (file->texture->so);
		file->texture->so = NULL;
	}
	if (file->texture->we != NULL)
	{
		free (file->texture->we);
		file->texture->we = NULL;
	}
	if (file->texture->ea != NULL)
	{
		free (file->texture->ea);
		file->texture->ea = NULL;
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
