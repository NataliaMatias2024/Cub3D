/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 10:18:13 by namatias          #+#    #+#             */
/*   Updated: 2026/06/04 22:58:57 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	check_extension(char *file_name);
static int	check_arg_is_valid(char *file_name);

int	check_args(int argc, char **argv, t_parser *parser)
{
	if (argc != 2)
	{
		parser->status = 1;
		printf("status: %d\n", parser->status);
		return (0);
	}
	else if (check_extension(argv[1]))
	{
		parser->status = 2;
		printf("status: %d\n", parser->status);
		return (0);
	}
	else if (!check_arg_is_valid(argv[1]))
	{
		parser->status = 3;
		printf("status: %d\n", parser->status);
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

static int	check_arg_is_valid(char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		return (0);
	close (fd);
	return (1);
}
