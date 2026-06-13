/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 10:55:09 by namatias          #+#    #+#             */
/*   Updated: 2026/06/12 23:53:57 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	main(int argc, char **argv)
{
	t_parser	parser;
	t_file		file;
	t_texture	texture;
	int			i;

	init_structs(&parser, &file, &texture);
	if (!check_args(argc, argv, &parser))
	{
		printf("Veeeesh deu chabu!\n");
		print_error(parser.status);
		clean_all(&parser);
		return (1);
	}
	else if (!read_file(argv[1], &parser))
	{
		printf("Ihhhhh mapa invalido!\n");
		print_error(parser.status);
		clean_all(&parser);
		return (1);
	}
	printf("Tudo certo!\nRoda a bagaceira!!!\n\n");
	printf("Status: %d\n", parser.status);
	printf("Color_ceiling: %d\n", parser.file->color_ceiling);
	printf("Color_floor: %d\n", parser.file->color_floor);
	printf("Player_row: %d\n", parser.file->player_row);
	printf("Player_col: %d\n", parser.file->player_col);
	printf("Total_row: %d\n", parser.file->total_row);
	printf("Total_col: %d\n", parser.file->total_col);
	printf("Texture NO: |%s|\n", parser.file->texture->no);
	printf("Texture SO: |%s|\n", parser.file->texture->so);
	printf("Texture WE: |%s|\n", parser.file->texture->we);
	printf("Texture EA: |%s|\n", parser.file->texture->ea);
	printf("Player View: %c\n", parser.file->player_view);
	printf("\n Imprimindo o mapa FINAL! \n");
	i = 0;
	while (i < parser.file->total_row)
	{
		printf("Linha %d - %s\n", i, parser.file->map[i]);
		i++;
	}
	clean_all(&parser);
	return (0);
}
