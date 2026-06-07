/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 10:18:13 by namatias          #+#    #+#             */
/*   Updated: 2026/06/07 11:47:39 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	check_extension(char *file_name);

int	check_args(int argc, char **argv, t_parser *parser)
{
	if (argc != 2)
	{
		parser->status = 1;
		return (0);
	}
	else if (check_extension(argv[1]))
	{
		parser->status = 2;
		return (0);
	}
	return (1);
}

static int	check_extension(char *file_name)
{
	int	name_size;
	int	result;

	name_size = ft_strlen(file_name);
	if (name_size <= 4)
		result = 1;
	else
		result = ft_strncmp(file_name + (name_size - 4), ".cub", 4);
	return (result);
}
