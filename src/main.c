/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkitano <mkitano@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 19:06:28 by mkitano           #+#    #+#             */
/*   Updated: 2026/06/18 19:06:28 by mkitano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	main(int argc, char **argv)
{
	t_parser	parser;
	t_file		file;
	t_texture	texture;
	t_game		game;

	init_structs(&parser, &file, &texture);
	if (!check_args(argc, argv, &parser) || !read_file(argv[1], &parser))
	{
		print_error(parser.status);
		clean_all(&parser);
		return (1);
	}
	ft_bzero(&game, sizeof(t_game));
	if (init_game(&game, &file) > 0 || init_win(&game) > 0)
	{
		clean_game(&game, &parser);
		return (1);
	}
	mlx_key_hook(game.mlx, &key_hook, &game);
	mlx_loop_hook(game.mlx, &game_loop, &game);
	mlx_loop(game.mlx);
	clean_game(&game, &parser);
	return (0);
}
