/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 10:55:09 by namatias          #+#    #+#             */
/*   Updated: 2026/06/11 18:34:38 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	main(int argc, char **argv)
{
	t_parser	parser;
	t_file		file;
	t_texture	texture;
	t_node	*print;
	size_t	i;

	init_structs(&parser, &file, &texture);
	if (!check_args(argc, argv, &parser))
	{
		printf("Veeeesh deu chabu!\n");
		print_error(parser.status);
		clean_structs(&parser);
		return (1);
	}
	else if (!read_file(argv[1], &parser))
	{
		printf("Ihhhhh mapa invalido!\n");
		print_error(parser.status);
		clean_structs(&parser);
		return (1);
	}
	printf("Tudo certo!\nRoda a bagaceira!!!\n\n");

	printf("Status: %d\n", parser.status);
	printf("Color_ceiling: %d\n", parser.file->color_ceiling);
	printf("Color_floor: %d\n", parser.file->color_floor);
	// printf("Player_x: %d\n", parser.file->player_x);
	// printf("Player_y: %d\n", parser.file->player_y);
	// printf("Total_x: %d\n", parser.file->total_x);
	// printf("Total_y: %d\n", parser.file->total_y);
	printf("Texture NO: |%s|\n", parser.file->texture->no);
	printf("Texture SO: |%s|\n", parser.file->texture->so);
	printf("Texture WE: |%s|\n", parser.file->texture->we);
	printf("Texture EA: |%s|\n", parser.file->texture->ea);
	// printf("Player View: %s\n", parser.file->player_view);
	printf("\n Imprimindo o mapa! \n");
	i = 0;
	print = parser.temp_map->head;
	while(i < parser.temp_map->size)
	{
		printf("Mapa node %d - %s", (int)i, (char *)print->data);
		print = print->next;
		i++;
	}
	clean_structs(&parser);
	ft_destroy_dlst(&parser.temp_map, free);
	return (0);
}
