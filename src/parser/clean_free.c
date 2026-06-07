/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 18:53:35 by namatias          #+#    #+#             */
/*   Updated: 2026/06/07 19:08:34 by namatias         ###   ########.fr       */
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
