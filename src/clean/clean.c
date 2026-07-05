/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkitano <mkitano@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 04:27:49 by mkitano           #+#    #+#             */
/*   Updated: 2026/07/02 01:14:43 by mkitano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	clean_game(t_game *game, t_parser *parser)
{
	if (game->tex.no)
		mlx_delete_texture(game->tex.no);
	game->tex.no = NULL;
	if (game->tex.so)
		mlx_delete_texture(game->tex.so);
	game->tex.so = NULL;
	if (game->tex.we)
		mlx_delete_texture(game->tex.we);
	game->tex.we = NULL;
	if (game->tex.ea)
		mlx_delete_texture(game->tex.ea);
	game->tex.ea = NULL;
	if (game->img)
		mlx_delete_image(game->mlx, game->img);
	game->img = NULL;
	if (game->mlx)
		mlx_terminate(game->mlx);
	game->mlx = NULL;
	clean_all(parser);
}
